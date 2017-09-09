
#include "wiz_vector_pair_user_type_ptr_and_int.h"


#include <stdio.h>

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	pair_user_type_ptr_and_int* tempArr;
	size_t i;

	tempArr = malloc(sizeof(pair_user_type_ptr_and_int) * vec->capacity * 2);

	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity = vec->capacity * 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(pair_user_type_ptr_and_int) * capacity);


	if (NULL == vec->vec) {
		printf("vec->vec is NULL\n"); // chk for debug?
	}
}
void FORM(free_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

pair_user_type_ptr_and_int* FORM(get_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, size_t idx, pair_user_type_ptr_and_int* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec, pair_user_type_ptr_and_int* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, pair_user_type_ptr_and_int) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	vec->num--;
}
pair_user_type_ptr_and_int* FORM(back_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, pair_user_type_ptr_and_int) (FORM(wiz_vector_, pair_user_type_ptr_and_int)* vec)
{
	return vec->num;
}
