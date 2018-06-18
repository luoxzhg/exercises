#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <cassert>
#include "Customer.h"

class Queue
{
public:
    typedef Customer Item;
    struct Node
    {
        Node() = default;
        Node(const Item& it, Node* p): item(it), next(p){}
        Item item;
        struct Node *next;
    };
    public:
        Queue(int Size = 10)
            :front(nullptr), rear(nullptr), itemCnt(0), qSize(Size) {}
        ~Queue();
        
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;
        
        bool isempty()const {return itemCnt == 0;}
        bool isfull()const {return itemCnt == qSize;}
        bool size()const {return itemCnt;}
        
        bool enqueue(const Item &);
        bool dequeue(Item &);
        bool dequeue();
        
        Item &first() {assert(itemCnt!=0); return front->item;}
        const Item&first()const {assert(itemCnt!=0); return front->item;}

    protected:
    
    private:
        void  freefront() 
        {Node *temp = front; front = front->next; delete temp;}
        void  decrease()
        {--itemCnt; if (itemCnt == 0) rear = front;}
        
    private:
        Node *front;
        Node *rear;
        int itemCnt;
        const int qSize;
};



#endif // QUEUE_H_INCLUDED
