#pragma once
#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include "mylib.h"
typedef struct tagNode
{
    struct tagNode* next;
    int value;
}Node, *SList;

// ����
inline SList SListCreate(void) { SList temp = NULL; return temp; }
inline void  SListInit(SList *proot) { *proot = NULL; }

inline Node*  SListPop(SList *proot) { Node *temp = *proot; *proot = temp->next; return temp; }
void   SListPush(Node*);

void   SListPush_front(SList *proot, int newValue);

// �鲢��*proot2ΪNULL�����Ϊ*proot1
SList  SListMerge(SList *proot1, SList *proot2);

void  SListDestroy(SList *);

void  SListSort(SList *rootp);



#endif // SLIST_H_INCLUDED
