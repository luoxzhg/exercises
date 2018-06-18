// include文件
#include "slist.h"
// ----------------------------------------

// 实现
void  SListPush_front(SList *proot, int newValue)
{
    Node *newnode = (Node *)malloc(sizeof(int));
    newnode->value = newValue;

    newnode->next = *proot;
    *proot = newnode;
}

void  SListSort(SList *rootp)
{
    SList temp = *rootp;
    if (temp == NULL || temp->next == NULL)  // 只有一个节点是返回
        return;

    Node *p1 = temp;
    Node *p2 = temp;
    while ((p2 = p2->next) != NULL && (p2 = p2->next) != NULL)
    {
        p1 = p1->next;
    }
    temp = p1->next; // p1->next 不能为NULL
    p1->next = NULL;

    SListSort(rootp);
    SListSort(&temp);

    SListMerge(rootp, &temp);
}
SList  SListMerge(SList *proot1, SList *proot2)
{
    Node *p1 = *proot1;
    Node *p2 = *proot2;
    *proot2 = NULL;      // 归并后*proot2为NULL，结果为*proot1

    // 选择第一个节点
    if (p1 == NULL )
        return *proot1 = p2;
    if (p2 == NULL )
        return p1;
    if ( p1->value < p2->value )
    {
        *proot1 = p1;
        p1 = p1->next;
    }
    else
    {
        *proot1 = p2;
        p2 = p2->next;
    }
    // 归并其余节点
    Node *temp = *proot1;
    for (; p1 != NULL && p2 != NULL; temp = temp->next)
    {
        if (p1->value < p2->value)
        {
            temp->next = p1;
            p1 = p1->next;
        }
        else
        {
            temp->next = p2;
            p2 = p2->next;
        }
    }

    temp->next = (p1 != NULL ? p1 : p2);

    return *proot1;
}
