#ifndef OAK_SINGLE_THREAD_EXECUTOR_H
#define OAK_SINGLE_THREAD_EXECUTOR_H
#include <thread>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <atomic>

namespace oak {
class ITask {
public:
    virtual void run() = 0;
    virtual int getDebugId() = 0;
};

typedef std::shared_ptr<ITask> SPTask;

class SingleThreadExecutor {
public:
    SingleThreadExecutor(int maxTaskCount);
    ~SingleThreadExecutor();
    void post(SPTask task);
    void shutdown();
private:
    void loop();
private:
    std::atomic<bool> mRunning;
    int mMaxTaskCount;
    std::thread mThread;
    std::deque<SPTask> mTaskQueue;
    std::condition_variable mCondVar;
    std::mutex mMutex;
};

}


#endif // OAK_SINGLE_THREAD_EXECUTOR_H