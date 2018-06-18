#pragma once
#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H

#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue
{
public:
    threadsafe_queue() : head(new node), tail(head.get()) {}

    threadsafe_queue(const threadsafe_queue&) = delete;
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;

    std::shared_ptr<T> try_pop();

    void  push(T new_value);

protected:
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::unique_ptr<node>  head;
    node *tail;
    std::mutex  head_mutex;
    std::mutex  tail_mutex;
    std::condition_variable cond_var;

    node *get_tail()
    {
        std::lock_guard<std::mutex> lg(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head()
    {
    std::unique_lock<std::mutex> lg(head_mutex);
    if (head.get() == get_tail()
        && !cond_var.wait_for(lg,
                            std::chrono::milliseconds(0),
                            [=]{ return head.get() != get_tail();} )
        )
        return nullptr;

    auto result = std::move(head);
    head = std::move(result->next);
    return result;
    }
};


template<typename T> void
threadsafe_queue<T>::push(T new_value)
{
    // 将分配工作放在临界区之前，以便增加并发性能
    auto pnew = std::make_shared<T>(std::move(new_value));
    auto new_dummy = std::make_unique<node>();   // 新的尾结点

    {
        std::lock_guard<std::mutex> lg(tail_mutex);
        tail->data = std::move(pnew);
        tail->next = std::move(new_dummy);
        tail = (tail->next).get();
    }
    std::unique_lock<std::mutex> ulg(head_mutex, std::try_to_lock);
    if (ulg.owns_lock())
        cond_var.notify_one();
}

template<typename T> std::shared_ptr<T>
threadsafe_queue<T>::try_pop()
{
    auto old_head = pop_head();
    return old_head ? std::move(old_head->data) : nullptr;
}

extern template class threadsafe_queue<bool>;
extern template class threadsafe_queue<char>;
extern template class threadsafe_queue<int>;
extern template class threadsafe_queue<unsigned int>;
extern template class threadsafe_queue<long>;
extern template class threadsafe_queue<unsigned long>;
#endif // THREADSAFE_QUEUE_H
