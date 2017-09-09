
#include "wiz_vector_double.h"

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	double* tempArr;
	size_t i;

	tempArr = malloc(sizeof(double) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(double) * capacity);
}
void FORM(free_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

double* FORM(get_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, size_t idx, double* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, double* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, double) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	vec->num--;
}
double* FORM(back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, double) (FORM(wiz_vector_, double)* vec)
{
	return vec->num;
}
