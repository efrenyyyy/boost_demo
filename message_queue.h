#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"
#include <deque>
class MessageQueue
{
public:
    MessageQueue(int capacity);
    ~MessageQueue();

    void push(int);
    int pop();

protected:
private:
    std::deque<int>                     queue_;
    boost::mutex                        mutex_;
    boost::condition_variable           cond_;
    int                                 capacity_;
};
#endif
