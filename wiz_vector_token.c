
#include "wiz_vector_token.h"
#include <stdio.h>

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	token* tempArr;
	size_t i;

	tempArr = malloc(sizeof(token) * vec->capacity * 2);

	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity = vec->capacity * 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(token) * capacity);
	

	if (NULL == vec->vec) {
		printf("vec->vec is NULL\n"); // chk for debug?
	}
}
void FORM(free_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

token* FORM(get_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, size_t idx, token* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, token* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, token) (vec);
	}
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	vec->num--;
}
token* FORM(back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, token) (FORM(wiz_vector_, token)* vec)
{
	return vec->num;
}

