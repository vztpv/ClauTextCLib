

#ifndef WIZ_STACK_SIZE_T_H
#define WIZ_STACK_SIZE_T_H

#include <stdlib.h>
#include "wiz_vector_size_t.h"

#define FORM(A, B) A##B


struct FORM(wiz_stack_, size_t)
{
	FORM(wiz_vector_, size_t) stack;
	size_t count;
};

typedef struct FORM(wiz_stack_, size_t) FORM(wiz_stack_, size_t);


void FORM(init_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t capacity);
void FORM(free_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack);

void FORM(push_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t* val);
void FORM(pop_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack);

size_t* FORM(top_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack);

int FORM(empty_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack);

size_t FORM(size_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack);

size_t* FORM(get_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t idx); // by index

#endif

