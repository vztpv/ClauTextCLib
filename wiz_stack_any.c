
#include "wiz_stack_any.h"

#define FORM(A, B) A##B

// static?
void FORM(expand_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	size_t i;
	FORM(wiz_vector_, any) temp;

	FORM(init_wiz_vector_, any)(&temp, (stack->count) * 2);

	for (i = 0; i < stack->count; ++i) {
		temp.vec[i] = get_wiz_vector_any(&(stack->stack), i);
	}

	FORM(free_wiz_vector_, any)(&(stack->stack)); // cf) ~.swap(~);
	temp.num = stack->count;
	stack->stack = temp;
}
// static?
int FORM(is_full_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	return stack->count == stack->stack.capacity;
}

void FORM(init_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, size_t capacity)
{
	init_wiz_vector_any(&(stack->stack), capacity);
	stack->count = 0;
}
void FORM(free_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	free_wiz_vector_any(&(stack->stack));
}

void FORM(push_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, void* val)
{
	if (FORM(is_full_wiz_stack_, any)(stack))
	{
		FORM(expand_wiz_stack_, any)(stack);
	}
	FORM(push_back_wiz_vector_, any)(&(stack->stack), val);
	stack->count++;
}
void FORM(pop_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	pop_back_wiz_vector_any(&(stack->stack));
	stack->count--;
}

void* FORM(top_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	return get_wiz_vector_any(&(stack->stack), stack->count - 1);
}

int FORM(empty_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	return 0 == stack->count;
}

size_t FORM(size_wiz_stack_, any)(FORM(wiz_stack_, any)* stack)
{
	return stack->count;
}

void* FORM(get_wiz_stack_, any)(FORM(wiz_stack_, any)* stack, size_t idx) // by index
{
	return get_wiz_vector_any(&(stack->stack), idx);
}

