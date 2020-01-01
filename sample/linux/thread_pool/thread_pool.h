#ifndef _OAK_THREAD_POOL_
#define _OAK_THREAD_POOL_
#include <pthread.h>
#include <queue>
#include <list>
using std::queue;
using std::list;

namespace OAK
{
    class Task
    {
    public:
        virtual int Perform() {
            return 0;
        }
    };

    class ThreadPool 
    {
        public:
            ThreadPool();
            ~ThreadPool();
            int     Create(int maxThreads);
            int     Post(Task* pTask);
            int     Run();
            int     Stop();
        public:
            void*   Work();
        private:
            queue<Task*>        m_tasks;
            list<pthread_t>     m_threads;
            pthread_mutex_t     m_taskQueueMutex;
            pthread_cond_t      m_taskQueueCond;

            int                 m_needCancel;
            pthread_mutex_t     m_needCancelMutex;
    };

}


#endif // _OAK_THREAD_POOL_
