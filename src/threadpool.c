#include "threadpool.h"

ThreadPool*
thread_pool_init(size_t num_threads)
{
    ThreadPool* pool = malloc(sizeof(ThreadPool));
    if(!pool) {
        perror("Memory allocation failed for thread pool");
        return NULL;
    }

    if (mtx_init(&pool->lock, mtx_plain) != thrd_success) {
        perror("Mutex initialization failed");
        free(pool);

        return NULL;
    }

    if (cnd_init(&pool->condition) != thrd_success) {
        perror("Condition variable initialization failed");
        mtx_destroy(&pool->lock);

        free(pool);
        return NULL;
    }

    pool->task_queue = NULL;
    pool->num_threads = num_threads > 0 ? num_threads : DEFAULT_THREAD_POOL_SIZE;
    pool->shutdown = false;

    pool->threads = malloc(pool->num_threads * sizeof(thrd_t));
    if (!pool->threads) {
        perror("Memory allocation failed for thread pool threads");

        mtx_destroy(&pool->lock);
        cnd_destroy(&pool->condition);
        free(pool);

        return NULL;
    }

    for (size_t i = 0; i < pool->num_threads; ++i) {
        if (thrd_create(&pool->threads[i], thread_function, pool) != thrd_success) {
            perror("Thread creation failed");

            thread_pool_destroy(pool);
            return NULL;
        }
    }

    return pool;
}

void
thread_pool_destroy(ThreadPool* pool)
{
    if (!pool)
        return;

    mtx_lock(&pool->lock);
    pool->shutdown = true;
    mtx_unlock(&pool->lock);

    cnd_broadcast(&pool->condition);

    for (size_t i = 0; i < pool->num_threads; ++i) {
        thrd_join(pool->threads[i], NULL);
			printf("Thread destroyed\n");
    }

    free(pool->threads);
    mtx_destroy(&pool->lock);
    cnd_destroy(&pool->condition);

    free(pool);
}

bool
thread_pool_enqueue(ThreadPool* pool, void (*function)(void*), void* arg)
{
    if (!pool || !function)
        return false;

    Task* new_task = malloc(sizeof(Task));
    if (!new_task) {
        perror("Memory allocation failed for new task");
        return false;
    }

    new_task->function = function;
    new_task->arg = arg;
    new_task->next = NULL;

    mtx_lock(&pool->lock);

    if (pool->task_queue == NULL)
        pool->task_queue = new_task;
    else {
        Task* last_task = pool->task_queue;
        while (last_task->next != NULL)
            last_task = last_task->next;

        last_task->next = new_task;
    }

    cnd_signal(&pool->condition);
    mtx_unlock(&pool->lock);

    return true;
}

int
thread_function(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (true) {
        mtx_lock(&pool->lock);

        while (!pool->task_queue && !pool->shutdown)
            cnd_wait(&pool->condition, &pool->lock);


        if (pool->shutdown) {
            mtx_unlock(&pool->lock);
            return thrd_success;
        }

        Task* task = pool->task_queue;
        if (task) {
            pool->task_queue = task->next;
        }

        mtx_unlock(&pool->lock);

        if (task) {
            task->function(task->arg);
            free(task);
        }
    }
}

