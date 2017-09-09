

#include "wiz_vector_event_info.h"

#define FORM(A, B) A##B

void FORM(expand_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	event_info* tempArr;
	size_t i;

	tempArr = malloc(sizeof(event_info) * vec->capacity * 2);
	for (i = 0; i < vec->capacity; ++i) {
		tempArr[i] = vec->vec[i];
	}
	vec->capacity *= 2;
	free(vec->vec);
	vec->vec = tempArr;
}

void FORM(init_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, const size_t capacity)
{
	vec->num = 0;
	vec->capacity = capacity;
	vec->vec = malloc(sizeof(event_info) * capacity);
}
void FORM(free_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	if (vec->vec != NULL) {
		free(vec->vec);
		vec->vec = NULL;
		vec->num = 0;
	}
}

event_info* FORM(get_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, size_t idx)
{
	return &vec->vec[idx];
}
void FORM(set_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, size_t idx, event_info* pval)
{
	vec->vec[idx] = *pval;
}

void FORM(push_back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec, event_info* pval)
{
	if (vec->capacity == vec->num) {
		FORM(expand_wiz_vector_, event_info) (vec);
	}

	//init_event_info(&(vec->vec[vec->num]), get_cstr_event_info(pval), size_event_info(pval));
	vec->vec[vec->num] = *pval;
	vec->num++;
}
void FORM(pop_back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	vec->num--;
}
event_info* FORM(back_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	return &vec->vec[vec->num - 1];
}

// boolean
int FORM(empty_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	return 0 == vec->num;
}

size_t FORM(size_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	return vec->num;
}

void FORM(reverse_wiz_vector_, event_info) (FORM(wiz_vector_, event_info)* vec)
{
	size_t i;
	event_info temp;

	for (i = 0; i < vec->num / 2; ++i) {
		temp = vec->vec[i];
		vec->vec[i] = vec->vec[vec->num - 1 - i];
		vec->vec[vec->num - 1 - i] = temp;
	}
}

