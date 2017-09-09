
#ifndef WIZ_VECTOR_EVENT_INFO_H
#define WIZ_VECTOR_EVENT_INFO_H

#include <stdlib.h>
#include "wiz_load_data.h"

#define FORM(A, B) A##B

struct FORM(wiz_vector_, event_info)
{
	event_info* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, event_info) FORM(wiz_vector_, event_info);

void FORM(init_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, const size_t capacity);
void FORM(free_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);
event_info* FORM(get_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, size_t idx);
void FORM(set_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, size_t idx, event_info* pval);

void FORM(push_back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, event_info* pval);
void FORM(pop_back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);
event_info* FORM(back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);

int FORM(empty_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);
size_t FORM(size_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);

// todo
// reverse
void FORM(reverse_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec);

#endif
