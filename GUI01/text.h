#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <assert.h>
#include <cstddef>
// ������
#define MAXSIZ  1024

// ������ʾ�ı����õĺ���
void  InsertCharToBuffer(int ch, PTSTR szBuffer, int nCurIndex, int cCnts);
void  DeleteCharFromBuffer(PTSTR szBuffer, int nCurIndex, int cCnts);

