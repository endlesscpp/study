#include "single_thread_executor.h"
#include <chrono>
using namespace oak;

class MyTask : public ITask {
    public:
    MyTask(int idx) {
        mIdx = idx;
    }

    ~MyTask() {
        printf("Task::dtor, id = %d\n", mIdx);
    }

    virtual int getDebugId() override {
        return mIdx;
    }

    virtual void run() override {
        printf("run, idx = %d\n", mIdx);
    }

private:
    int mIdx;
};

int main(int argc, char** argv) {
    oak::SingleThreadExecutor engine(0);
    for (int i = 0; i < 100; i++) {
        SPTask task = std::make_shared<MyTask>(i);
        engine.post(task);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    engine.shutdown();

    return 0;
}