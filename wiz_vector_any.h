
#ifndef WIZ_VECTOR_ANY_H
#define WIZ_VECTOR_ANY_H

#define FORM(A, B) A##B

#include <stdlib.h>


struct FORM(wiz_vector_, any)
{
	void** vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, any) FORM(wiz_vector_, any);

void FORM(init_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, const size_t capacity);
void FORM(free_wiz_vector_, any) (FORM(wiz_vector_, any)* vec);
void* FORM(get_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, size_t idx);
void FORM(set_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, size_t idx, void* pval);

void FORM(push_back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec, void* pval);
void FORM(pop_back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec);
void* FORM(back_wiz_vector_, any) (FORM(wiz_vector_, any)* vec);

int FORM(empty_wiz_vector_, any) (FORM(wiz_vector_, any)* vec);
size_t FORM(size_wiz_vector_, any) (FORM(wiz_vector_, any)* vec);


#endif
