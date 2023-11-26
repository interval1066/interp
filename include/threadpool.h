#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>

#define DEFAULT_THREAD_POOL_SIZE 5

typedef struct ThreadPool ThreadPool;
typedef struct Task Task;

struct Task {
    void (*function)(void* arg);
    void* arg;
    Task* next;
};

struct ThreadPool {
    mtx_t lock;
    cnd_t condition;

    Task* task_queue;
    thrd_t* threads;
    size_t num_threads;

    bool shutdown;
};

// Function to initialize a thread pool
ThreadPool* thread_pool_init(size_t num_threads);

// Function to destroy a thread pool
void thread_pool_destroy(ThreadPool* pool);

// Function to add a task to the thread pool
bool thread_pool_enqueue(ThreadPool* pool, void (*function)(void*), void* arg);

// Function executed by each thread in the pool
int thread_function(void* arg);

