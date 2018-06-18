// include�ļ�
#include "Queue.h"

// using ����


//-----------------------------------------

// ȫ�ֱ���


//-----------------------------------------

// ����ԭ������
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
    rear = pnew;   // ����ƶ�����βָ��
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

