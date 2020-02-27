#include <stdio.h>
#include <unistd.h>

#include "thread_pool.h"
using namespace OAK;

class MyTask: public Task
{
public:
    MyTask(int base) {
        m_base = base;
        m_i = 0;
    }
public:
    int Perform() {
        for (int i = 0; i<10; i++) {
            printf("base = %d, i = %d\n", m_base, m_i);
            m_i++;
            sleep(1);
        }

        return 0;
    }
private:
    int m_base;
    int m_i;
};

int main()
{
    ThreadPool pool;
    pool.Create(2);
    pool.Post(new MyTask(1));
    pool.Post(new MyTask(2));

    sleep(20);
    pool.Stop();

    return 0;
}


