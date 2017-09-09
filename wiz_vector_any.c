
#include "wiz_vector_any.h"

#define FORM(A, B) A##B


void FORM(expand_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	void** tempArr;
	size_t i;

	tempArr = malloc(sizeof(void*) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	for (i = vec->capacity; i < vec->capacity * 2; ++i) {
		tempArr[i] = NULL;
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}
void FORM(init_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(void*) * capacity);
	{
		size_t i;
		for (i = 0; i < capacity; ++i) {
			vec->vec[i] = NULL;
		}
	}
}
void FORM(free_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

void* FORM(get_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, size_t idx)
{
	return (vec->vec[idx]);
}
void FORM(set_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, size_t idx, void* pval)
{
	vec->vec[idx] = pval;
}

void FORM(push_back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, void* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, any) (vec);
	}

	vec->vec[vec->num] = pval;

	vec->num++;
}
void FORM(pop_back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	vec->num--;
}
void* FORM(back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	return vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, any) (FORM(wiz_vector_, any)* vec)
{
	return vec->num;
}
