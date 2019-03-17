#ifndef _LEX_H_
#define _LEX_H_

#include <sys/types.h>


#define TOK_NUM         1  // a number 
#define TOK_MULT        2  // *
#define TOK_DIV         3  // /
#define TOK_ADD         4  // +
#define TOK_SUB         5  // - 
#define TOK_EXP         6  // ^
#define TOK_NL          7  // \n
#define TOK_QUIT        8  // user entered quit
#define TOK_EOF         9  // user typed ctrl + d
#define TOK_ERR        10  // an error 

int get_tok(char *word, size_t max_len);



#endif
