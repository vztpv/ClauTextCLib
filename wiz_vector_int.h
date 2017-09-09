
#ifndef WIZ_VECTOR_INT_H
#define WIZ_VECTOR_INT_H

#include <stdlib.h>

#define FORM(A, B) A##B

struct FORM(wiz_vector_, int)
{
	int* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, int) FORM(wiz_vector_, int);

void FORM(init_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, const size_t capacity);
void FORM(free_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);
int* FORM(get_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, size_t idx);
void FORM(set_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, size_t idx, int* pval); // const int*?

void FORM(push_back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec, int* pval);
void FORM(pop_back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);
int* FORM(back_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);

int FORM(empty_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);
size_t FORM(size_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);

void FORM(decrease_size_wiz_vector_, int) (FORM(wiz_vector_, int)* vec);

#endif
