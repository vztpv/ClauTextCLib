
#ifndef WIZ_VECTOR_WIZ_STRING_H
#define WIZ_VECTOR_WIZ_STRING_H

#include <stdlib.h>
#include "wiz_string.h"

#define FORM(A, B) A##B

struct FORM(wiz_vector_, wiz_string)
{
	wiz_string* vec;
	size_t capacity;
	size_t num;
};

typedef struct FORM(wiz_vector_, wiz_string) FORM(wiz_vector_, wiz_string);

void FORM(init_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec, const size_t capacity);
void FORM(free_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);
wiz_string* FORM(get_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec, size_t idx);
void FORM(set_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec, size_t idx, wiz_string* pval);

void FORM(push_back_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec, wiz_string* pval);
void FORM(pop_back_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);
wiz_string* FORM(back_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);

int FORM(empty_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);
size_t FORM(size_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);

// todo
// reverse
void FORM(reverse_wiz_vector_, wiz_string) (FORM(wiz_vector_, wiz_string)* vec);
void FORM(push_back_cstr_wiz_vector_, wiz_string)(FORM(wiz_vector_, wiz_string)* vec, const char* cstr);

#endif
