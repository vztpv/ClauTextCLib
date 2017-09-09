
#ifndef WIZ_STACK_WIZ_STRING_H
#define WIZ_STACK_WIZ_STRING_H

#include <stdlib.h>
#include "wiz_string.h"
#include "wiz_vector_wiz_string.h"

#define FORM(A, B) A##B


struct FORM(wiz_stack_, wiz_string)
{
	FORM(wiz_vector_, wiz_string) stack;
	size_t count;
};

typedef struct FORM(wiz_stack_, wiz_string) FORM(wiz_stack_, wiz_string);


void FORM(init_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, size_t capacity);
void FORM(free_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack);

void FORM(push_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, wiz_string* val);
void FORM(push_cstr_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, char* val);

void FORM(pop_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack);

wiz_string* FORM(top_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack);

int FORM(empty_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack);

size_t FORM(size_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack);

wiz_string* FORM(get_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, size_t idx); // by index

#endif

