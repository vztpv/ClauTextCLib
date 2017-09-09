

#ifndef WIZ_STACK_EVENT_INFO_H
#define WIZ_STACK_EVENT_INFO_H

#include "wiz_load_data.h"
#include "wiz_vector_event_info.h"
#define FORM(A, B) A##B


struct FORM(wiz_stack_, event_info)
{
	FORM(wiz_vector_, event_info) stack;
	size_t count;
};

typedef struct FORM(wiz_stack_, event_info) FORM(wiz_stack_, event_info);


void FORM(init_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, size_t capacity);
void FORM(free_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack);

void FORM(push_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, event_info* val);

void FORM(pop_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack);

event_info* FORM(top_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack);

int FORM(empty_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack);

size_t FORM(size_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack);

event_info* FORM(get_wiz_stack_, event_info)(FORM(wiz_stack_, event_info)* stack, size_t idx); // by index

#endif

