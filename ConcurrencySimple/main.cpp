#include <iostream>
#include <cassert>
#include <atomic>
#include <thread>
#include "threadsafe_queue.h"
#include "parallel_quick_sort.h"
using namespace std;

threadsafe_queue<int> q;
int main()
{
    std::list<int> lst {3, 7, 1, 8, 6, 5, 9, 2, 10, 1, 8, 9, 21, 33, 13, 21, 22, 25, 12,14,16,17,19,22,25,66,34,67,43,99,32};
    for (auto n : lst)
        cout << n << ' ';
    cout << endl;
    //lst = parallel_quick_sort(lst);
    lst.sort();
    for (auto n : lst)
        cout << n << ' ';
    cout << endl;
//    auto f1 = []{
//               int i = 0;
//               while (i++ < 10)
//                   q.push(i);
//            };
//    thread  t1(f1),
//            t2([]{
//                while (auto p = q.try_pop())
//                {
//                    cout << *p << endl;
//                }
//            }),
//            t3(f1);
//    t1.join();
//    t2.join();
//    t3.join();
}
