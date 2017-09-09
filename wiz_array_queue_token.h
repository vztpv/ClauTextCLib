
#ifndef WIZ_ARRAY_QUEUE_TOKEN_H
#define WIZ_ARRAY_QUEUE_TOKEN_H

#include "wiz_vector_token.h"


#define FORM(A, B) A##B

struct FORM(wiz_array_queue_, token)
{
	FORM(wiz_vector_, token) que;
	size_t start;
	size_t num;
};
	
typedef struct FORM(wiz_array_queue_, token) FORM(wiz_array_queue_, token);

void FORM(init_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
void FORM(free_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);

void  FORM(push_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que, token* val);
token*  FORM(pop_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
token*  FORM(pop_back_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
token*  FORM(back_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
token*  FORM(front_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);

token*  FORM(get_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que, const size_t idx);

int  FORM(is_full_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
int  FORM(isEmpty_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
size_t  FORM(size_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
int  FORM(empty_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
size_t  FORM(get_num_max_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);
size_t  FORM(get_num_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que);


void FORM(erase_in_wiz_array_queue_, token)(FORM(wiz_array_queue_, token)* token_vec, size_t idx);

#endif
