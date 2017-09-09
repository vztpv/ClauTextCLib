
#ifndef WIZ_VECTOR_SIZE_T_H
#define WIZ_VECTOR_SIZE_T_H

#include <stdlib.h>

#define FORM(A, B) A##B

struct FORM(wiz_vector_, size_t)
{
	size_t* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, size_t) FORM(wiz_vector_, size_t);

void FORM(init_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, const size_t capacity);
void FORM(free_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec);
size_t* FORM(get_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t idx);
void FORM(set_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t idx, size_t* pval);

void FORM(push_back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec, size_t* pval);
void FORM(pop_back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec);
size_t* FORM(back_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec);

int FORM(empty_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec);
size_t FORM(size_wiz_vector_, size_t) (FORM(wiz_vector_, size_t)* vec);
#endif
