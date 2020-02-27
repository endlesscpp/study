#include "single_thread_executor.h"

namespace oak
{
SingleThreadExecutor::SingleThreadExecutor(int maxTaskCount) {
    mRunning = true;
    mMaxTaskCount = maxTaskCount;
    mThread = std::thread(&SingleThreadExecutor::loop, this);
}

SingleThreadExecutor::~SingleThreadExecutor() {
    if (mRunning) {
        shutdown();
    }
}

void SingleThreadExecutor::post(SPTask task) {
    if (!mRunning) {
        return;
    }
    
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (mMaxTaskCount > 0 && (int)mTaskQueue.size() >= mMaxTaskCount) {
            mTaskQueue.pop_front();
        }
        mTaskQueue.push_back(task);
    }
    mCondVar.notify_all();
}

void SingleThreadExecutor::loop() {
    while (true) {
        SPTask task = nullptr;
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mCondVar.wait(lock, [this] {return !mRunning || !this->mTaskQueue.empty();});
            if (!mRunning) {
                break;
            }
            task = mTaskQueue.front();
            mTaskQueue.pop_front();
        } 

        task->run();
    }
}

void SingleThreadExecutor::shutdown() {
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mRunning = false;
    }
    mCondVar.notify_all();

    if (mThread.joinable()) {
        mThread.join();
    }
    mTaskQueue.clear();
}

}
