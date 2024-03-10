#pragma once

#include <windows.h>

#define MAX_THREADS 10

typedef struct {
    // Add any data members you need for your specific task
    // ...

    // Add synchronization objects if needed
    CRITICAL_SECTION lock;
} TaskData;

typedef struct {
    HANDLE hThread;
    TaskData* pData;
} ThreadPoolThread;

