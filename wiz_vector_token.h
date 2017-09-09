
#ifndef WIZ_VECTOR_token
#define WIZ_VECTOR_token

#include "wiz_load_data_token.h"
#include <stdlib.h>

#define FORM(A, B) A##B

struct FORM(wiz_vector_, token)
{
	token* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, token) FORM(wiz_vector_, token);

void FORM(init_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, const size_t capacity);
void FORM(free_wiz_vector_, token) (FORM(wiz_vector_, token)* vec);
token* FORM(get_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, size_t idx);
void FORM(set_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, size_t idx, token* pval);

void FORM(push_back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec, token* pval);
void FORM(pop_back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec);
token* FORM(back_wiz_vector_, token) (FORM(wiz_vector_, token)* vec);

int FORM(empty_wiz_vector_, token) (FORM(wiz_vector_, token)* vec);
size_t FORM(size_wiz_vector_, token) (FORM(wiz_vector_, token)* vec);

#endif
