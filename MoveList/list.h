#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

// �ض��ڳ��������ʵ��
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


/// �����������ĺ���ԭ��

/** \brief ����һ����Ч��item
 *
 * \param 
 * \param 
 * \return 
 *
 */     
bool  GetItem(Item *pitem, FILE *pfile);


/** 
 * \brief ��ʼ��һ���б�
 * \param plistָ��һ��δ��ʼ�����б�
 * \param 
 * \return 
 */     
void InitializeList(List *plist);

/** \brief ȷ��һ���б��Ƿ�Ϊ��
 *
 * \param  plistָ��һ����Ч���б�
 * \param 
 * \return ���б�Ϊ�գ��򷵻�true�����򷵻� false
 */     
bool IsListEmpty(const List *plist);

/** \brief ȷ���б��Ƿ�����
 *
 * \param plistָ��һ����Ч���б�
 * \param 
 * \return ���б��������򷵻�true�����򷵻�false
 */     
bool IsListFull(const List *plist);

void  DisplayItem(FILE *pfile, const Item *pitem);

/** \brief  ȷ���б�����Ŀ�ĸ���
 *
 * \param plistָ��һ����Ч���б�
 * \param 
 * \return 
 *
 */     
int  CountItem(const List *plist);

/** \brief ���б�β���������Ŀ
 *
 * \param  plistָ��һ��δ�����б�
 * \param 
 * \return  ����ӳɹ��򷵻�true�����򷵻�false
 *
 */     
bool  AddItem(List *plist, Item item);

/** \brief ��һ���ص�����������ÿһ����Ŀ
 *
 * \param plistָ��һ����Ч���б�
 * \param  pfunָ��һ�����ʵĺ���
 * \return  
 *
 */     
void  TraverseList(const List *plist, void (*pfun)(const Item *pItem));

/** \brief ����һ����Ч���б����ͷ������ڴ�
 *
 * \param  plistָ��һ����Ч���б�
 * \param 
 * \return 
 *
 */      
void  DestroyList(List *plist);

#endif // LIST_H_INCLUDED
