#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include <stdbool.h>

/******************************************************************
** read_word: read words from intput and stores it in \param word.
**            Makes word empty if no word could be read because of EOF. 
**            Truncates  the word if its length exceeds \param max_len.
**            \return the length of the readed word.
*******************************************************************/
int read_word(char *word, int max_len);

#endif // WORD_H_INCLUDED
