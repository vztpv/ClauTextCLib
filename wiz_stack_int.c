
#include "wiz_stack_int.h"

#define FORM(A, B) A##B

// static?
void FORM(expand_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	size_t i;
	FORM(wiz_vector_, int) temp;

	FORM(init_wiz_vector_, int)(&temp, (stack->count) * 2);

	for (i = 0; i < stack->count; ++i) {
		temp.vec[i] = *get_wiz_vector_int(&(stack->stack), i);
	}

	FORM(free_wiz_vector_, int)(&(stack->stack)); // cf) ~.swap(~);
	temp.num = stack->count;
	stack->stack = temp;
}
// static?
int FORM(is_full_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	return stack->count == stack->stack.capacity;
}

void FORM(init_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, size_t capacity)
{
	init_wiz_vector_int(&(stack->stack), capacity);
	stack->count = 0;
}
void FORM(free_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	free_wiz_vector_int(&(stack->stack));
}

void FORM(push_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, int* val)
{
	if (FORM(is_full_wiz_stack_, int)(stack))
	{
		FORM(expand_wiz_stack_, int)(stack);
	}
	FORM(push_back_wiz_vector_, int)(&(stack->stack), val);
	stack->count++;
}
void FORM(pop_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	pop_back_wiz_vector_int(&(stack->stack));
	stack->count--;
}

int* FORM(top_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	return get_wiz_vector_int(&(stack->stack), stack->count - 1);
}

int FORM(empty_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	return 0 == stack->count;
}

size_t FORM(size_wiz_stack_, int)(FORM(wiz_stack_, int)* stack)
{
	return stack->count;
}

int* FORM(get_wiz_stack_, int)(FORM(wiz_stack_, int)* stack, size_t idx) // by index
{
	return get_wiz_vector_int(&(stack->stack), idx);
}

