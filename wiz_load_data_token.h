
#ifndef WIZ_LOAD_DATA_TOKEN_H
#define WIZ_LOAD_DATA_TOKEN_H


#include "wiz_string.h"


struct token
{
	wiz_string str;
	int isComment;
};

typedef struct token token;


#endif
