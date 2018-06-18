// include文件
#include "Queue.h"

// using 声明


//-----------------------------------------

// 全局变量


//-----------------------------------------

// 函数原型声明
// ----------------------------------------

Queue::~Queue()
{
    while (!isempty())
    {
        freefront();
    }
}

bool Queue::enqueue(const Item &item)
{
    if (isfull())
    {
        return false;
    }

    Node *pnew = new Node(item, nullptr);
    //    if (isempty())
    //        front =  pnew;
    //    else
    //        rear->next = pnew;
    (isempty() ? front : rear->next) = pnew;
    rear = pnew;   // 最后移动队列尾指针
    ++itemCnt;
    return true;
}



bool Queue::dequeue()
{
    if (isempty())
    {
        return false;
    }
    freefront();
    decrease();
    return true;
}
bool Queue::dequeue(Item &item)
{
    if (isempty())
    {
        return false;
    }
    
    item = front->item;

    freefront();
    decrease();
    return true;
}

