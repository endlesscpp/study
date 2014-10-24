#include "thread_pool.h"
#include <stdio.h>

namespace OAK
{

static void* Worker(void* arg)
{
    OAK::ThreadPool* pThis = (OAK::ThreadPool*)(arg);
    return pThis->Work();
}


ThreadPool::ThreadPool()
{
    m_needCancel = 0;
}

ThreadPool::~ThreadPool()
{
}

int ThreadPool::Create(int maxThreads)
{
    m_needCancel = 0;
    int ret = pthread_mutex_init(&m_needCancelMutex, NULL);
    if (ret != 0)
        return ret;
    
    ret = pthread_mutex_init(&m_taskQueueMutex, NULL);
    if (ret != 0)
        return ret;

    ret = pthread_cond_init(&m_taskQueueCond, NULL);
    if (ret != 0)
        return ret;

    m_threads.clear();
    
    for (int i = 0; i < maxThreads; i++) {
        pthread_t thread;
        ret = pthread_create(&thread, NULL, Worker, this);
        if (ret != 0)
            return ret;
        m_threads.push_back(thread);
    }

    return 0;
}

int ThreadPool::Post(Task* pTask)
{
    int ret = pthread_mutex_lock(&m_taskQueueMutex);
    if (ret != 0)
        return ret;

    // TODO: who is in charge of delete this Task?
    m_tasks.push(pTask);

    ret = pthread_mutex_unlock(&m_taskQueueMutex);
    if (ret != 0)
        return ret;

    ret = pthread_cond_signal(&m_taskQueueCond);

    return ret;
}

int ThreadPool::Run()
{
    return 0;
}

int ThreadPool::Stop()
{
    pthread_mutex_lock(&m_needCancelMutex);
    m_needCancel = 1;
    pthread_mutex_unlock(&m_needCancelMutex);
    pthread_cond_broadcast(&m_taskQueueCond);

#if DEBUG
    printf("join begin\n");
#endif
    int ret = 0;
    for (list<pthread_t>::iterator it = m_threads.begin();
            it != m_threads.end();
            ++it) {
        pthread_join(*it, NULL);
    }
#if DEBUG
    printf("join finished\n");
#endif

    m_threads.clear();

    // destory the mutex
    pthread_mutex_destroy(&m_needCancelMutex);
    pthread_mutex_destroy(&m_taskQueueMutex);
    pthread_cond_destroy(&m_taskQueueCond);

    // clean the tasks in the queue
    while (!m_tasks.empty()) {
        Task* p = m_tasks.front();
        m_tasks.pop();
        delete p;
    }

    return 0;
}

void* ThreadPool::Work()
{
    int ret = 0;

    while (true) {
    
    ret = pthread_mutex_lock(&m_taskQueueMutex);
    if (ret != 0)
        break;
    
    int needCancel = 0;
    while (m_tasks.empty()) {
        pthread_cond_wait(&m_taskQueueCond, &m_taskQueueMutex);

        // check if need to cancel
        pthread_mutex_lock(&m_needCancelMutex);
        needCancel = m_needCancel;
        pthread_mutex_unlock(&m_needCancelMutex);

        if (needCancel != 0)
            break;
    }

    if (needCancel != 0) {
        pthread_mutex_unlock(&m_taskQueueMutex);
        break;
    }

    Task* pTask = m_tasks.front();
    m_tasks.pop();

    ret = pthread_mutex_unlock(&m_taskQueueMutex);
    if (ret != 0)
        break;

    pTask->Perform();
    delete pTask;
    pTask = NULL;
    }

    return (void*)(ret);
}

} // namespace OAK
