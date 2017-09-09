
#include "wiz_vector_item_type.h"

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	item_type* tempArr;
	size_t i;

	tempArr = malloc(sizeof(item_type) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(item_type) * capacity);
}
void FORM(free_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

item_type* FORM(get_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, size_t idx, item_type* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec, item_type* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, item_type) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	vec->num--;
}
item_type* FORM(back_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	return vec->num;
}

void FORM(decrease_size_wiz_vector_, item_type) (FORM(wiz_vector_, item_type)* vec)
{
	if (vec->num > 0) {
		vec->num--;
	}
}

