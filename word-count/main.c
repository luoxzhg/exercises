#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(void)
{
    printf("Hello world!\n");
    bool inWord = false;
    unsigned int cntLines = 0, cntWords = 0, cntChars = 0;

    FILE *pf = fopen("input.txt", "r");
    if (pf == NULL)
        exit(EXIT_FAILURE);

    int ch;
    char prech; // prech ���ڼ�����һ���ַ��Ƿ���'\n'�������Ƿ��cntLines��һ
    while (EOF != (ch = getc(pf))) {
        ++cntChars;
        prech = ch;
        if (ch == '\n') {
            ++cntLines;
        }

        if (!inWord && !isspace(ch)) {
            inWord = true;
            ++cntWords;
        }
        else if (inWord && isspace(ch)) {
            inWord = false;
        }
    }

    if (cntChars != 0 && prech != '\n')
        ++cntLines;

    printf("%d lines, %d words, %d characters",
           cntLines, cntWords, cntChars);
    return 0;
}
