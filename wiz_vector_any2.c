
#include "wiz_vector_any2.h"

#include "wiz_load_data_user_type.h"
#define FORM(A, B) A##B


void FORM(expand_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
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
void FORM(init_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, const size_t capacity)
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
void FORM(free_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	if (vec->vec != NULL) {
		size_t i;
		for (i = 0; i < vec->num; ++i) {
			if (NULL != vec->vec[i]) {
				free_user_type_in_user_type(vec->vec[i]);
				free(vec->vec[i]);
				vec->vec[i] = NULL;
			}
		}
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

void shallow_free_wiz_vector_any2(wiz_vector_any2* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}


void* FORM(get_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, size_t idx)
{
	return (vec->vec[idx]);
}
void FORM(set_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, size_t idx, void* pval)
{
	if (vec->vec[idx] != NULL) {
		free_user_type_in_user_type(vec->vec[idx]);
		free(vec->vec[idx]);
		vec->vec[idx] = NULL;
	}

	vec->vec[idx] = malloc(sizeof(user_type));
	init_from_other_user_type_in_user_type(vec->vec[idx], pval);
}

void shallow_push_back_wiz_vector_any2(wiz_vector_any2* vec, void* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, any2) (vec);
	}

	if (pval == NULL) {
		vec->vec[vec->num] = NULL;
	}
	else {
		vec->vec[vec->num] = pval;
	}

	vec->num++;
}
void FORM(push_back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, void* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, any2) (vec);
	}

	if (pval == NULL) {
		vec->vec[vec->num] = NULL;
	}
	else {
		vec->vec[vec->num] = malloc(sizeof(user_type));
		init_from_other_user_type_in_user_type(vec->vec[vec->num], pval);
	}

	vec->num++;
}
void FORM(pop_back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	if (NULL != vec->vec[vec->num])
	{
		free_user_type_in_user_type(vec->vec[vec->num]);

		free(vec->vec[vec->num]);
	}
	vec->vec[vec->num] = NULL;
	vec->num--;
}
void* FORM(back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	return vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	return vec->num;
}

void FORM(decrease_size_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec)
{
	if (vec->num > 0) {
		vec->num--;
	}
}

