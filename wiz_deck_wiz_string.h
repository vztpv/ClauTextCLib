
#ifndef WIZ_DECK_WIZ_STRING_H
#define WIZ_DECK_WIZ_STRING_H

#include <stdlib.h>
#include "wiz_string.h"
#include "wiz_vector_wiz_string.h"

#define FORM(A, B) A##B

struct FORM(wiz_deck_, wiz_string)
{
	FORM(wiz_vector_, wiz_string) deck;
	size_t start;
	size_t num;
};

typedef struct FORM(wiz_deck_, wiz_string) FORM(wiz_deck_, wiz_string);


void FORM(init_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
void FORM(free_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);

void  FORM(push_back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, wiz_string* val);
void  FORM(push_front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, wiz_string* val);
wiz_string*  FORM(pop_front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
wiz_string*  FORM(pop_back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
wiz_string*  FORM(back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
wiz_string*  FORM(front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);

wiz_string*  FORM(get_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, const size_t idx);

int  FORM(is_full_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
size_t  FORM(size_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
int  FORM(empty_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);
size_t  FORM(get_num_max_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck);


#endif
