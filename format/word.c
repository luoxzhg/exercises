#include <stdio.h>
#include <ctype.h>
#include "word.h"

int  read_word(char *word, int max_len)
{
	int ch, pos = 0;
	// eat white space
	while (isspace(ch = read_char()))
		;
	
	while (ch != EOF && !isspace(ch) && pos < max_len) {
		word[pos++] = ch;
		ch = read_char();
	}
	
	if (ch != EOF && !isspace(ch) && pos == max_len) {
		word[pos-1] = '*';
		
		while ((ch = getchar()) != EOF && !isspace(ch))
			;
	}
	word[pos] = '\0';
	return pos;
}
