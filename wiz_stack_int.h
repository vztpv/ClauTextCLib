
#ifndef WIZ_STACK_INT_H
#define WIZ_STACK_INT_H

#include <stdlib.h>
#include "wiz_vector_int.h"

#define FORM(A, B) A##B


struct FORM(wiz_stack_, int)
{
	FORM(wiz_vector_, int) stack;
	size_t count;
};

typedef struct FORM(wiz_stack_, int) FORM(wiz_stack_, int);


void FORM(init_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, size_t capacity);
void FORM(free_wiz_stack_, int)(FORM(wiz_stack_, int)* stack);

void FORM(push_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, int* val);
void FORM(pop_wiz_stack_, int)(FORM(wiz_stack_, int)* stack);

int* FORM(top_wiz_stack_, int)(FORM(wiz_stack_, int)* stack);

int FORM(empty_wiz_stack_, int)(FORM(wiz_stack_, int)* stack);

size_t FORM(size_wiz_stack_, int)(FORM(wiz_stack_, int)* stack);

int* FORM(get_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, size_t idx); // by index

#endif

