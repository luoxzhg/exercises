#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "mylib.h"
#include "SingleList.h"


typedef struct tagSingleListNode {
    ElemType  element;
    struct tagSingleListNode *next;
} SingleListNode;

inline static void CopyElem(ElemType *dest, const ElemType *src)
{
    assert(src != NULL);
    *dest = *src;
}

inline static SingleListNode *CreateNode(const ElemType *pvalue)
{
    SingleListNode *p = New(SingleListNode, 1);
    CopyElem(&p->element, pvalue);
    return p;
}

void  InitSingleList(SingleList *plist)
{
    assert(plist);
    *plist = NULL;
}

bool  IsSingleListEmpty(const SingleList *plist)
{
    assert(plist);
    return NULL == *plist;
}

bool  IsSingleListFull(const SingleList *useless)
{
    assert(useless);
    SingleListNode *p = New(SingleListNode, 1);
    // p 的值不会被 free 改变
    free(p);
    return NULL == p;
}

size_t  SingleListSize(const SingleList *plist)
{
    assert(plist);
    size_t  cnt = 0;
    SingleListNode *p = *plist;

    while (p) {
        ++cnt;
        p = p->next;
    }

    return cnt;
}

void  AppendToSingleList(SingleList *plist, const ElemType *pvalue)
{
    assert(plist && pvalue);
    SingleListNode *p = CreateNode(pvalue);

    //    if (NULL == *plist)
    //        *plist = p;
    //    else {
    //        SingleListNode *pCur = *plist;
    //
    //        while (pCur && pCur->next)
    //            pCur = pCur->next;
    //
    //        pCur->next = p;
    //    }
    //! 将每个后续子链表作为链表,
    //! plist 指向头指针, 或节点的 next 指针
    while (*plist)
        plist = &(*plist)->next;

    p->next = NULL;
    *plist = p;
}

void  InsertToStringList(SingleList *plist, const ElemType *pvalue)
{
    assert(plist && pvalue);
    SingleListNode *p = New(SingleListNode, 1);

    p->next = *plist;
    *plist = p;
}

void  TraverseSingleList(const SingleList *plist, void(*pfun)(const ElemType *))
{
    assert(plist && pfun);
    //! p 指向待处理的节点
    SingleListNode *p = *plist;

    while (p) {
        (*pfun)(&p->element);
        p = p->next;
    }
}

void  EmptySingleList(SingleList *plist)
{
    assert(plist);
    SingleListNode *p;

    while ((p = *plist)) {
        *plist = p->next;
        free(p);
    }
}

