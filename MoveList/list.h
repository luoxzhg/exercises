#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

// 特定于程序的属性实现
#define MSIZE  81
typedef struct tagItem
{
    char  name[MSIZE] ;
    int   rating;
} Item;

typedef struct tagNode
{
    Item item;
    struct tagNode *next;
} Node, *List;


/// 操作函数集的函数原型

/** \brief 读入一个有效的item
 *
 * \param 
 * \param 
 * \return 
 *
 */     
bool  GetItem(Item *pitem, FILE *pfile);


/** 
 * \brief 初始化一个列表
 * \param plist指向一个未初始化的列表
 * \param 
 * \return 
 */     
void InitializeList(List *plist);

/** \brief 确定一个列表是否为空
 *
 * \param  plist指向一个有效的列表
 * \param 
 * \return 若列表为空，则返回true；否则返回 false
 */     
bool IsListEmpty(const List *plist);

/** \brief 确定列表是否已满
 *
 * \param plist指向一个有效的列表
 * \param 
 * \return 若列表已满，则返回true，否则返回false
 */     
bool IsListFull(const List *plist);

void  DisplayItem(FILE *pfile, const Item *pitem);

/** \brief  确定列表中项目的个数
 *
 * \param plist指向一个有效的列表
 * \param 
 * \return 
 *
 */     
int  CountItem(const List *plist);

/** \brief 在列表尾部添加新项目
 *
 * \param  plist指向一个未满的列表
 * \param 
 * \return  若添加成功则返回true，否则返回false
 *
 */     
bool  AddItem(List *plist, Item item);

/** \brief 把一个回调函数作用于每一个项目
 *
 * \param plist指向一个有效的列表
 * \param  pfun指向一个合适的函数
 * \return  
 *
 */     
void  TraverseList(const List *plist, void (*pfun)(const Item *pItem));

/** \brief 销毁一个有效的列表，并释放所有内存
 *
 * \param  plist指向一个有效的列表
 * \param 
 * \return 
 *
 */      
void  DestroyList(List *plist);

#endif // LIST_H_INCLUDED
