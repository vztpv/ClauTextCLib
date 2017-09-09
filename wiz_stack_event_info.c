

#include "wiz_stack_event_info.h"


#define FORM(A, B) A##B

// static?
void FORM(expand_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	size_t i;
	FORM(wiz_vector_, event_info) temp;

	FORM(init_wiz_vector_, event_info)(&temp, (stack->count) * 2);

	for (i = 0; i < stack->count; ++i) {
		temp.vec[i] = *get_wiz_vector_event_info(&(stack->stack), i);
	}

	FORM(free_wiz_vector_, event_info)(&(stack->stack)); // cf) ~.swap(~);
	temp.num = stack->count;
	stack->stack = temp;
}
// static?
int FORM(is_full_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	return stack->count == stack->stack.capacity;
}

void FORM(init_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, size_t capacity)
{
	init_wiz_vector_event_info(&(stack->stack), capacity);
	stack->count = 0;
}
void FORM(free_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	free_wiz_vector_event_info(&(stack->stack));
	stack->count = 0;
}

void FORM(push_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, event_info* val)
{
	if (FORM(is_full_wiz_stack_, event_info)(stack))
	{
		FORM(expand_wiz_stack_, event_info)(stack);
	}
	FORM(push_back_wiz_vector_, event_info)(&(stack->stack), val);
	stack->count++;
}

void FORM(pop_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	pop_back_wiz_vector_event_info(&(stack->stack));
	stack->count--;
}

event_info* FORM(top_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	return get_wiz_vector_event_info(&(stack->stack), stack->count - 1);
}

int FORM(empty_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	return 0 == stack->count;
}

size_t FORM(size_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack)
{
	return stack->count;
}

event_info* FORM(get_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, size_t idx) // by index
{
	return get_wiz_vector_event_info(&(stack->stack), idx);
}





