#include <stdio.h>
#include <stdlib.h>
#include "list.h"

inline void OutputItem(const  Item*);
void OutputItem(const Item* pitem)
{
    DisplayItem(stdout, pitem);
}
int main(void)
{
    printf("Hello world!\n");
    
    Item  item;
    // 初始化列表
    List  movies;
    InitializeList(&movies);
    
    printf("Enter the first  movie title: \n");
    while (!IsListFull(&movies) && GetItem( &item, stdin))
    {
        AddItem(&movies, item);
    }
    
    if (IsListFull(&movies))
    {
        fprintf(stderr, "No memory avalible!\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        fprintf(stdout, "read finished!\n");
    }
    
    if (!IsListEmpty(&movies))
        TraverseList(&movies, OutputItem);
    
    DestroyList(&movies);
    return 0;
}
