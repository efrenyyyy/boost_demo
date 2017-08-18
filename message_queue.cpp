#include "queue.h"
#include "boost/bind.hpp"

MessageQueue::MessageQueue(int capacity)
    :capacity_(capacity)
{

}

MessageQueue::~MessageQueue()
{

}

void MessageQueue::push(int mem)
{
    boost::mutex::scoped_lock lock(mutex_);
    if (queue_.size() == capacity_)
    {
        cond_.wait(lock);
    }
    queue_.push_back(mem);
    cond_.notify_one();
}

int MessageQueue::pop()
{
    boost::mutex::scoped_lock lock(mutex_);
    int ret;
    if (queue_.size() == 0)
    {
        cond_.wait(lock);
    }
    ret = queue_.front();
    queue_.pop_front();
    cond_.notify_one();
    return ret;
}

void thread_callback(MessageQueue *q, int tid)
{
    int t = time(NULL);

    while (1)
    {
        q->push(t);
        boost::this_thread::sleep(boost::posix_time::millisec(t%10));
        printf("tid:%d, msg:%d\n", tid, q->pop());
    }
}

int main(int argc, char **argv)
{
    boost::thread *thread_pool[32];
    boost::int32_t count = 0;
    MessageQueue    q(6);

    while (count < 32)
    {
        thread_pool[count] = new boost::thread(boost::bind(&thread_callback, &q, count));
        count ++;
    }
    getchar();
    return 0;
}