#ifndef SFALLOC_H_INCLUDED
#define SFALLOC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define sfalloc(type, count)   ((type)*)myalloc__((count) * sizeof(type))


inline  void *myalloc__(size_t  size)
{
    void *pnew;
    if (NULL == (pnew=malloc(size)))
    {
        fprintf(stderr, "bad alloc!\n");
        exit(EXIT_FAILURE);
    }
    return pnew;
}


#define  malloc   myalloc__
#endif // SFALLOC_H_INCLUDED
