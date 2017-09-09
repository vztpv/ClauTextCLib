
#ifndef WIZ_VECTOR_ANY2_H
#define WIZ_VECTOR_ANY2_H

#define FORM(A, B) A##B

#include <stdlib.h>


struct FORM(wiz_vector_, any2)
{
	void** vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, any2) FORM(wiz_vector_, any2);

void FORM(init_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, const size_t capacity);
void FORM(free_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);

void shallow_push_back_wiz_vector_any2(wiz_vector_any2* vec, void* pval);
void shallow_free_wiz_vector_any2(wiz_vector_any2* vec);

void* FORM(get_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, size_t idx);
void FORM(set_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, size_t idx, void* pval);

void FORM(push_back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec, void* pval);

void FORM(pop_back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);
void* FORM(back_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);

int FORM(empty_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);
size_t FORM(size_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);

void FORM(decrease_size_wiz_vector_, any2) (FORM(wiz_vector_, any2)* vec);

#endif
