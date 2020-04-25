#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unistd.h>

class HeartbeatThread
{
public:
    ~HeartbeatThread()
    {
        stop();
    }

public:
    void start()
    {
        mRunning = true;
        mThread = std::thread(&HeartbeatThread::threadEntry, this);
        mThread.detach();
    }
    void stop()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (!mRunning) {
            return;
        }
        mRunning = false;
        mCondVar.notify_all();
    }

private:
    void threadEntry()
    {
        int cnt = 0;
        while (true) {
            printf("In thread, cnt = %d\n", cnt);
            std::unique_lock<std::mutex> lock(mMutex);
            mCondVar.wait_for(lock, std::chrono::seconds(1),
                              [this] { return !this->mRunning; });
            if (!mRunning) {
                printf("thread quit...\n");
                break;
            }
            cnt++;
        }
    }

private:
    std::thread             mThread;
    bool                    mRunning = false;
    std::mutex              mMutex;
    std::condition_variable mCondVar;
};

static HeartbeatThread th;

int main()
{
    printf("print q quit...\n");
    th.start();

    while (true) {
        char ch = getchar();
        if (ch == 'q' || ch == 'Q') {
            th.stop();
            break;
        }
    }
    printf("finished...\n");
    return 0;
}
