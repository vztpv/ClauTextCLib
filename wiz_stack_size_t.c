
#include "wiz_stack_size_t.h"

#define FORM(A, B) A##B

// static?
void FORM(expand_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	size_t i;
	FORM(wiz_vector_, size_t) temp;

	FORM(init_wiz_vector_, size_t)(&temp, (stack->count) * 2);

	for (i = 0; i < stack->count; ++i) {
		temp.vec[i] = *get_wiz_vector_size_t(&(stack->stack), i);
	}

	FORM(free_wiz_vector_, size_t)(&(stack->stack)); // cf) ~.swap(~);
	temp.num = stack->count;
	stack->stack = temp;
}
// static?
int FORM(is_full_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	return stack->count == stack->stack.capacity;
}

void FORM(init_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t capacity)
{
	init_wiz_vector_size_t(&(stack->stack), capacity);
	stack->count = 0;
}
void FORM(free_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	free_wiz_vector_size_t(&(stack->stack));
}

void FORM(push_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t* val)
{
	if (FORM(is_full_wiz_stack_, size_t)(stack))
	{
		FORM(expand_wiz_stack_, size_t)(stack);
	}
	FORM(push_back_wiz_vector_, size_t)(&(stack->stack), val);
	stack->count++;
}
void FORM(pop_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	pop_back_wiz_vector_size_t(&(stack->stack));
	stack->count--;
}

size_t* FORM(top_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	return get_wiz_vector_size_t(&(stack->stack), stack->count - 1);
}

int FORM(empty_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	return 0 == stack->count;
}

size_t FORM(size_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack)
{
	return stack->count;
}

size_t* FORM(get_wiz_stack_, size_t)(FORM(wiz_stack_, size_t)* stack, size_t idx) // by index
{
	return get_wiz_vector_size_t(&(stack->stack), idx);
}

