#pragma once
#ifndef PARALLEL_QUICK_SORT_H_INCLUDED
#define PARALLEL_QUICK_SORT_H_INCLUDED

#include <algorithm>
#include <list>
#include <vector>
#include <atomic>
#include <future>
#include <thread>
#include "threadsafe_queue.h"


template<typename T>
struct sorter
{
    struct chunk_to_sort
    {
        std::list<T> _data;
        std::promise<std::list<T>> _promise;
    };

    threadsafe_queue<chunk_to_sort> chunks;
    std::vector<std::thread> threads;
    unsigned const max_thread_count;
    std::atomic<bool> end_of_data;

    sorter() : max_thread_count(std::thread::hardware_concurrency() - 1),
            end_of_data(false)
    {    }

    ~sorter()
    {
        end_of_data = true;
        for (auto& th : threads)
            th.join();
    }

    void try_to_sort()
    {
        std::shared_ptr<chunk_to_sort>  pchunk = chunks.try_pop();
        if (pchunk)
            sort_chunk(pchunk);

    }

    void sort_chunk(std::shared_ptr<chunk_to_sort> const& pchunk)
    {
        pchunk->_promise.set_value(do_sort(pchunk->_data));
    }

    std::list<T> do_sort(std::list<T>& data_to_sort)
    {
        if (data_to_sort.empty())
            return data_to_sort;

        std::list<T> result;
        result.splice(result.begin(), data_to_sort, data_to_sort.begin());
        T& pivot = *result.begin();
        auto p_divide
            = std::partition(data_to_sort.begin(), data_to_sort.end(),
                [&](T const& val) { return val < pivot; });

        chunk_to_sort  new_lower_chunk;
        new_lower_chunk._data.splice(new_lower_chunk._data.begin(),
            data_to_sort, data_to_sort.begin(), p_divide);

        std::future<std::list<T>> new_lower
            = new_lower_chunk._promise.get_future();

        if (new_lower_chunk._data.size() > 1)
            chunks.push(std::move(new_lower_chunk));
        else
            new_lower_chunk._promise.set_value(new_lower_chunk._data);

        if (threads.size() < max_thread_count)
            threads.emplace_back(&sorter<T>::thread_sort, this);

        if (data_to_sort.size() > 1)
            data_to_sort = do_sort(data_to_sort);

        result.splice(result.end(), data_to_sort);

        while (new_lower.wait_for(std::chrono::seconds(0))
            != std::future_status::ready)
        {
            try_to_sort();
        }

        result.splice(result.begin(), new_lower.get());
        return result;
    }

    void thread_sort()
    {
        while (!end_of_data)
        {
            try_to_sort();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if (input.empty())
        return input;

    sorter<T> s;
    return s.do_sort(input);
}
#endif // PARALLEL_QUICK_SORT_H_INCLUDED
