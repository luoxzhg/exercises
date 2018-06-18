// include文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"





void  eatline(FILE *pfile)
{
    int ch;
    while ((ch = getc(pfile)) != EOF && ch != '\n')
    {
        continue;
    }
}

static void CopyToNode(Node *pnode, const Item *item)
{
    pnode->item = *item;
}
// 操作接口实现
void InitializeList(List *plist)
{
    *plist = NULL;
}

bool IsListEmpty(const List *plist)
{
    return *plist == NULL ? true : false;
}


bool IsListFull(const List *plist)
{
    Node *pnode = (Node*)malloc(sizeof(Node));
    if (pnode == NULL)
        return true;
    
    free(pnode);
    return false;
}


int CountItem(const List *plist)
{
    Node *pnode = *plist;
    int cnt = 0;
    while (pnode != NULL)
    {
        pnode = pnode->next;
        ++cnt;
    }
    return cnt;
}


bool GetItem(Item *pitem, FILE *pfile)
{
    fprintf(stdout, "Enter the title of the movies: \n");
    if (NULL == fgets(pitem->name, MSIZE, pfile))
    {
        return false;
    }
    if (pitem->name[0] == '\n') // 空行结束
    {
        return false;
    }
    
    // 如果一行输入过多，则只保留前面的，后面以省略号结束。
    char *pLF;
    if (NULL == (pLF = strchr(pitem->name, '\n')))
    {
        fprintf(stderr, "ERROR: the name of the movies is too long!, "
                "so we only use the front!\n");
        int length = MSIZE - 1;  // name[length] 为字符串结尾空字符
        for (int pos = length - 1; pos >= length - 3; --pos)
            pitem->name[pos] = '.';
        
        eatline(pfile);
    }
    else 
        *pLF = '\0';

    fprintf(stdout, "Enter the rating of the movies< 1-10 >: \n");
    if (1 != fscanf(pfile, "%d", &pitem->rating))
    {
        return false;
    }
    
    eatline(pfile);

    return true;
}


bool  AddItem(List *plist, Item item)
{
    if (IsListFull(plist))
    {
        return false;
    }
    Node *pnode = (Node *)malloc(sizeof(Node));
    CopyToNode(pnode, &item);
    pnode->next = NULL;

    // 迭代到末尾
    List *pcur = plist;
    while (*pcur != NULL)
    {
        pcur = &(*pcur)->next;
    }
    *pcur = pnode;
    return true;
}

void  TraverseList(const List *plist, void (*pfun)(const Item*))
{
    Node *pcur = *plist;
    while (pcur != NULL)
    {
        (*pfun)(&pcur->item);
        pcur = pcur->next;
    }
}

void  DestroyList(List *plist)
{
    Node *pnode ;
    while ((pnode = *plist) != NULL)
    {
        *plist = pnode->next;
        free(pnode);
    }
}

void DisplayItem(FILE *pfile, const Item *pitem)
{
    fprintf(pfile, "Movie: %s, Rating: %d\n", pitem->name, pitem->rating);
}