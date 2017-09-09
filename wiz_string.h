
#ifndef WIZ_STRING_H
#define WIZ_STRING_H

#include <string.h>
#include <stdlib.h>

#define wiz_string_buffer_size 15

struct wiz_string
{
	char buffer[wiz_string_buffer_size + 1];
	char* str;
	size_t len;
	// int chk; // for DEBUG?
	// size_t capacity; // ?
	int moved; // if 1 == moved, then do not free data!
};

typedef struct wiz_string wiz_string;

// cstr cf) "" and NULL
void init_wiz_string(wiz_string* str, const char* cstr, int n);

void free_wiz_string(wiz_string* str);

char* get_cstr_wiz_string(wiz_string* str);

size_t size_wiz_string(wiz_string* str);

int empty_wiz_string(wiz_string* str);

wiz_string concat_wiz_string(wiz_string* str1, wiz_string* str2);

wiz_string substr_wiz_string(wiz_string* str, size_t begin, size_t end);

void assign_wiz_string(wiz_string* str1, wiz_string* str2);

// concat_and_assign_wiz_string  A = A + B
void concat_and_assign_wiz_string(wiz_string* str1, wiz_string* str2);

// substr_and_assign_wiz_string  A = A.substring();
void substr_and_assign_wiz_string(wiz_string* str, size_t begin, size_t end);

char back_wiz_string(wiz_string* str);

char front_wiz_string(wiz_string* str);

// erase(shift, num--)_wiz_string
void erase_wiz_string(wiz_string* str, size_t idx);
// starts_with_wiz_string
int starts_with_wiz_string(wiz_string* str, wiz_string* start_str);
// ends_with_wiz_string
int lasts_with_wiz_string(wiz_string* str, wiz_string* last_string);
// equal_wiz_string
int equal_wiz_string(wiz_string* str1, wiz_string* str2);

void reverse_wiz_string(wiz_string* str);

#endif

