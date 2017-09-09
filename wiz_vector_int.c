
#include "wiz_vector_int.h"

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, int) (FORM(wiz_vector_, int)* vec) 
{
	int* tempArr;
	size_t i;
	
	tempArr = malloc(sizeof(int) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(int) * capacity);
}
void FORM(free_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

int* FORM(get_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, size_t idx, int* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, int* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, int) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	vec->num--;
}
int* FORM(back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	return vec->num;
}

void FORM(decrease_size_wiz_vector_, int) (FORM(wiz_vector_, int)* vec)
{
	if (vec->num > 0) {
		vec->num--;
	}
}