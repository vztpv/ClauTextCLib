
#ifndef WIZ_STACK_WIZ_ANY_H
#define WIZ_STACK_WIZ_ANY_H

#include <stdlib.h>
#include "wiz_vector_any.h"

#define FORM(A, B) A##B


struct FORM(wiz_stack_, any)
{
	FORM(wiz_vector_, any) stack;
	size_t count;
};

typedef struct FORM(wiz_stack_, any) FORM(wiz_stack_, any);


void FORM(init_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, size_t capacity);
void FORM(free_wiz_stack_, any)(FORM(wiz_stack_, any)* stack);

void FORM(push_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, void* val);
void FORM(pop_wiz_stack_, any)(FORM(wiz_stack_, any)* stack);

void* FORM(top_wiz_stack_, any)(FORM(wiz_stack_, any)* stack);

int FORM(empty_wiz_stack_, any)(FORM(wiz_stack_, any)* stack);

size_t FORM(size_wiz_stack_, any)(FORM(wiz_stack_, any)* stack);

void* FORM(get_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, size_t idx); // by index

#endif

