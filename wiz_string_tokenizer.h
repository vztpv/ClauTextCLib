
#ifndef WIZ_STRING_TOKENIZER_H
#define WIZ_STRING_TOKENIZER_H

#include "wiz_string.h"
#include "wiz_vector_wiz_string.h"
#include "wiz_string_builder.h"

#define FORM(A, B) A##B


struct wiz_string_tokenizer {
	wiz_vector_wiz_string str;
	size_t count;
	int exist;
	int option;
};

typedef struct wiz_string_tokenizer wiz_string_tokenizer;

// assumtion : separators are sorted by length?, long -> short
void init_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer, wiz_string* str, wiz_vector_wiz_string* separator, 
	wiz_string_builder* builder, int option);

void free_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer);

int count_tokens_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer);

wiz_string* next_token_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer);

int has_more_tokens_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer);

int is_find_exist_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer);


#endif
