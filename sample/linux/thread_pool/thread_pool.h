#ifndef _OAK_THREAD_POOL_
#define _OAK_THREAD_POOL_
#include <list>
#include <pthread.h>
#include <queue>
using std::list;
using std::queue;

namespace OAK
{
class Task
{
public:
    virtual ~Task() {}
    virtual int Perform()
    {
        return 0;
    }
};

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();
    int Create(int maxThreads);
    int Post(Task* pTask);
    int Start();
    int Stop();

public:
    void* Work();

private:
    queue<Task*>    m_tasks;
    list<pthread_t> m_threads;
    pthread_mutex_t m_taskQueueMutex;
    pthread_cond_t  m_taskQueueCond;

    int             m_needCancel;
    pthread_mutex_t m_needCancelMutex;
};

} // namespace OAK

#endif // _OAK_THREAD_POOL_
