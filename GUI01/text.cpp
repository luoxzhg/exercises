#include "text.h"



void InsertCharToBuffer(int ch, PTSTR szBuffer, int nCurIndex, int cCnts)
{
    PTSTR pCurrent = szBuffer + nCurIndex;
    memmove(pCurrent+1, pCurrent, (cCnts-nCurIndex + 1)*sizeof(TCHAR));
    *pCurrent = ch;
}

void DeleteCharFromBuffer(PTSTR szBuffer, int nCurIndex, int cCnts)
{
    PTSTR pCurrent = szBuffer + nCurIndex;
    memmove(pCurrent-1, pCurrent, (cCnts - nCurIndex + 1)*sizeof(TCHAR));
}
