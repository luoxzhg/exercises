#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <assert.h>
#include <cstddef>
// 缓冲区
#define MAXSIZ  1024

// 输入显示文本所用的函数
void  InsertCharToBuffer(int ch, PTSTR szBuffer, int nCurIndex, int cCnts);
void  DeleteCharFromBuffer(PTSTR szBuffer, int nCurIndex, int cCnts);

