
#ifndef WIZ_VECTOR_ITEM_TYPE_H
#define WIZ_VECTOR_ITEM_TYPE_H

#include <stdlib.h>
#include "wiz_load_data_item_type.h"

#define FORM(A, B) A##B

struct FORM(wiz_vector_, item_type)
{
	item_type* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, item_type) FORM(wiz_vector_, item_type);

void FORM(init_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, const size_t capacity);
void FORM(free_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);
item_type* FORM(get_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, size_t idx);
void FORM(set_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, size_t idx, item_type* pval);

void FORM(push_back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, item_type* pval);
void FORM(pop_back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);
item_type* FORM(back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);

int FORM(empty_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);
size_t FORM(size_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);

void FORM(decrease_size_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec);

#endif
