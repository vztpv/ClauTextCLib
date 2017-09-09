
#include "wiz_vector_size_t.h"

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	size_t* tempArr;
	size_t i;

	tempArr = malloc(sizeof(size_t) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(size_t) * capacity);
}
void FORM(free_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

size_t* FORM(get_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t idx, size_t* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, size_t) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	vec->num--;
}
size_t* FORM(back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec)
{
	return vec->num;
}
