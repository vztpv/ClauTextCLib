
#ifndef WIZ_DECK_PAIR_USER_TYPE_PTR_AND_INT_H
#define WIZ_DECK_PAIR_USER_TYPE_PTR_AND_INT_H

#include <stdlib.h>
#include "wiz_vector_pair_user_type_ptr_and_int.h"
#include "pair.h"

#define FORM(A, B) A##B

struct FORM(wiz_deck_, pair_user_type_ptr_and_int)
{
	FORM(wiz_vector_, pair_user_type_ptr_and_int) deck;
	size_t start;
	size_t num;
};

typedef struct FORM(wiz_deck_, pair_user_type_ptr_and_int) FORM(wiz_deck_, pair_user_type_ptr_and_int);


void FORM(init_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
void FORM(free_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);

void  FORM(push_back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, pair_user_type_ptr_and_int* val);
void  FORM(push_front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, pair_user_type_ptr_and_int* val);
pair_user_type_ptr_and_int*  FORM(pop_front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
pair_user_type_ptr_and_int*  FORM(pop_back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
pair_user_type_ptr_and_int*  FORM(back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
pair_user_type_ptr_and_int*  FORM(front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);

pair_user_type_ptr_and_int*  FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, const size_t idx);

int  FORM(is_full_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
size_t  FORM(size_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
int  FORM(empty_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);
size_t  FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck);




#endif
