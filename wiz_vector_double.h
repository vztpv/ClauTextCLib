
#ifndef WIZ_VECTOR_DOUBLE_H
#define WIZ_VECTOR_DOUBLE_H

#include <stdlib.h>

#define FORM(A, B) A##B

struct FORM(wiz_vector_, double)
{
	double* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, double) FORM(wiz_vector_, double);

void FORM(init_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, const size_t capacity);
void FORM(free_wiz_vector_, double) (FORM(wiz_vector_, double)* vec);
double* FORM(get_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, size_t idx);
void FORM(set_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, size_t idx, double* pval);

void FORM(push_back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec, double* pval);
void FORM(pop_back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec);
double* FORM(back_wiz_vector_, double) (FORM(wiz_vector_, double)* vec);

int FORM(empty_wiz_vector_, double) (FORM(wiz_vector_, double)* vec);
size_t FORM(size_wiz_vector_, double) (FORM(wiz_vector_, double)* vec);
#endif
