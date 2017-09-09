
#ifndef WIZ_VECTOR_PAIR_USER_TYPE_PTR_AND_INT_H
#define WIZ_VECTOR_PAIR_USER_TYPE_PTR_AND_INT_H


#include "pair.h"

#include <stdlib.h>

#define FORM(A, B) A##B

struct FORM(wiz_vector_, pair_user_type_ptr_and_int)
{
	pair_user_type_ptr_and_int* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, pair_user_type_ptr_and_int) FORM(wiz_vector_, pair_user_type_ptr_and_int);

void FORM(init_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, const size_t capacity);
void FORM(free_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec);
pair_user_type_ptr_and_int* FORM(get_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, size_t idx);
void FORM(set_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, size_t idx, pair_user_type_ptr_and_int* pval);

void FORM(push_back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, pair_user_type_ptr_and_int* pval);
void FORM(pop_back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec);
pair_user_type_ptr_and_int* FORM(back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec);

int FORM(empty_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec);
size_t FORM(size_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec);



#endif
