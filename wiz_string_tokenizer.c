

#include "wiz_string_tokenizer.h"


// assumtion : separators are sorted by length?, long -> short
void init_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer, wiz_string* str, wiz_vector_wiz_string* separator, wiz_string_builder* builder, int option)
{
	int left = 0;
	int right = 0;
	int state = 0;
	size_t i, j, k;

	tokenizer->count = 0; 
	tokenizer->option = option;
	tokenizer->exist = 0;
	init_wiz_vector_wiz_string(&(tokenizer->str), 1);

	clear_wiz_string_builder(builder);
	append_wiz_string_builder(builder, get_cstr_wiz_string(str), size_wiz_string(str));

	for (i = 0; i < size_wiz_string(str); ++i) {
		int _select = -1;
		int pass = 0;
		right = i;

		if (1 == option && 0 == state && '\"' == get_cstr_wiz_string(str)[i]) {
			if (i == 0) {
				state = 1;
				continue;
			}
			else if (i > 0 && '\\' == get_cstr_wiz_string(str)[i - 1]) {
				// printf("ERROR for Init on StringTokenizer\n"); // error!
				exit(-1);
			}
			else if (i > 0) {
				state = 1;
				continue;
			}
		}
		else if (1 == option && 1 == state && '\"' == get_cstr_wiz_string(str)[i]) {
			if ('\\' == get_cstr_wiz_string(str)[i - 1]) {
				continue;
			}
			else {
				state = 0;
			}
		}
		else if (1 == option && 1 == state) {
			continue;
		}


		for (j = 0; j < size_wiz_vector_wiz_string(separator); ++j) {
			for (k = 0; k < size_wiz_string(get_wiz_vector_wiz_string(separator, j)) && i + k < size_wiz_string(str); ++k) {
				if (get_cstr_wiz_string(str)[i + k] == get_cstr_wiz_string(get_wiz_vector_wiz_string(separator, j))[k]) {
					pass = 1;
				}
				else {
					pass = 0;
					break;
				}
			}
			if (pass) { _select = j; break; }
		}

		if (pass) {
			tokenizer->exist = 1;

			if (right - left >= 0) {
				wiz_string temp;
				init_wiz_string(&temp, divide_wiz_string_builder(builder, right - left), right - left);

				if (right - left > 0) {
					push_back_wiz_vector_wiz_string(&(tokenizer->str), &temp);
					left_shift_wiz_string_builder(builder, right - left + 1);
				}
				else {
					left_shift_wiz_string_builder(builder, 1);
					free_wiz_string(&temp);
				}
			}

			i = i + size_wiz_string(get_wiz_vector_wiz_string(separator, _select)) - 1;

			left = i + 1;
			right = left;
		}
		else if (!pass && i == size_wiz_string(str) - 1) {
			if (right - left + 1 > 0) {
				wiz_string temp;
				init_wiz_string(&temp, divide_wiz_string_builder(builder, right - left + 1), right - left + 1);

				push_back_wiz_vector_wiz_string(&(tokenizer->str), &temp);
				
				left_shift_wiz_string_builder(builder, right - left + 2);
			}
			else {
				// _getch(); // removal to  clautext (C++ version)
			}
		}
	}
}
void free_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer)
{
	tokenizer->count = 0;
	tokenizer->option = -1;
	tokenizer->exist = 0;

	free_wiz_vector_wiz_string(&(tokenizer->str));
}

int count_tokens_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer)
{
	return size_wiz_vector_wiz_string(&(tokenizer->str));
}

wiz_string* next_token_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer)
{ 
	if (has_more_tokens_wiz_string_tokenizer(tokenizer)) {
		tokenizer->count++;
		return get_wiz_vector_wiz_string(&(tokenizer->str), tokenizer->count - 1);
	}
	return NULL;
}

int has_more_tokens_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer)
{ 
	return tokenizer->count < size_wiz_vector_wiz_string(&(tokenizer->str));
}

int is_find_exist_wiz_string_tokenizer(wiz_string_tokenizer* tokenizer)
{ 
	return tokenizer->exist;
}

