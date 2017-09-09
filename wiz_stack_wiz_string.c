
#include "wiz_stack_wiz_string.h"

#define FORM(A, B) A##B

// static?
void FORM(expand_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	size_t i;
	FORM(wiz_vector_, wiz_string) temp;

	FORM(init_wiz_vector_, wiz_string)(&temp, (stack->count) * 2);

	for (i = 0; i < stack->count; ++i) {
		temp.vec[i] = *get_wiz_vector_wiz_string(&(stack->stack), i);
	}

	FORM(free_wiz_vector_, wiz_string)(&(stack->stack)); // cf) ~.swap(~);
	temp.num = stack->count;
	stack->stack = temp;
}
// static?
int FORM(is_full_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	return stack->count == stack->stack.capacity;
}

void FORM(init_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, size_t capacity)
{
	init_wiz_vector_wiz_string(&(stack->stack), capacity);
	stack->count = 0;
}
void FORM(free_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	free_wiz_vector_wiz_string(&(stack->stack));
	stack->count = 0;
}

void FORM(push_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, wiz_string* val)
{ 
	if (FORM(is_full_wiz_stack_, wiz_string)(stack))
	{
		FORM(expand_wiz_stack_, wiz_string)(stack);
	}
	FORM(push_back_wiz_vector_, wiz_string)(&(stack->stack), val);
	stack->count++;
}

void FORM(push_cstr_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, char* val)
{
	if (FORM(is_full_wiz_stack_, wiz_string)(stack))
	{
		FORM(expand_wiz_stack_, wiz_string)(stack);
	}
	FORM(push_back_cstr_wiz_vector_, wiz_string)(&(stack->stack), val);
	stack->count++;
}

void FORM(pop_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	pop_back_wiz_vector_wiz_string(&(stack->stack));
	stack->count--;
}

wiz_string* FORM(top_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	return get_wiz_vector_wiz_string(&(stack->stack), stack->count - 1); 
}

int FORM(empty_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	return 0 == stack->count;
}

size_t FORM(size_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack)
{
	return stack->count;
}

wiz_string* FORM(get_wiz_stack_, wiz_string)(FORM(wiz_stack_, wiz_string)* stack, size_t idx) // by index
{
	return get_wiz_vector_wiz_string(&(stack->stack), idx);
}

