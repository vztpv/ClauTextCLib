
#define _CRT_SECURE_NO_WARNINGS
#include "wiz_string.h"
#include <string.h>
//#include "wiz_string_builder.h"

// cstr cf) "" and NULL
void init_wiz_string(wiz_string* str, const char* cstr, int n)
{
	// debug..
	//if (strlen(cstr) != n) {
	//	printf("Error");
	//}
	str->moved = 0;

	if (0 == n) {
		str->len = 0;
		str->str = "";
		str->buffer[0] = '\0';
	}
	else {
		if (n > wiz_string_buffer_size) {
			str->str = malloc(sizeof(char)*(n + 1));
			strncpy(str->str, cstr, n + 1);
			str->len = n;
		}
		else {
			str->str = "";
			strncpy(str->buffer, cstr, n + 1);
			str->len = n;
		}
	}
}
void free_wiz_string(wiz_string* str)
{
	if (0 != str->len) {
		if (str->len > wiz_string_buffer_size && 0 == str->moved) {
			free(str->str);	
			
			str->str = "";
			str->buffer[0] = '\0';
			str->len = 0;
			str->moved = -1;
		}
		else if (0 == str->moved) {
			str->buffer[0] = '\0';
			str->str = "";
			str->len = 0;
			str->moved = -2;
		}
	}
}
char* get_cstr_wiz_string(wiz_string* str)
{
	if (str->len > wiz_string_buffer_size) { return str->str; }
	return str->buffer;
}
size_t size_wiz_string(wiz_string* str) {
	return str->len;
}
int empty_wiz_string(wiz_string* str)
{
	return 0 == str->len;
}
wiz_string concat_wiz_string(wiz_string* str1, wiz_string* str2)
{
	wiz_string temp;

	temp.len = str1->len + str2->len;
	temp.moved = 0;

	if (temp.len == 0) {
		temp.buffer[0] = '\0';
		temp.str = "";
	}
	else {
		if (temp.len > wiz_string_buffer_size) {
			temp.str = malloc(sizeof(char)*(temp.len + 1));
			strncpy(temp.str, get_cstr_wiz_string(str1), str1->len + 1);
			strncpy(temp.str + str1->len, get_cstr_wiz_string(str2), str2->len + 1);
		}
		else {
			strncpy(temp.buffer, get_cstr_wiz_string(str1), str1->len + 1);
			strncpy(temp.buffer + str1->len, get_cstr_wiz_string(str2), str2->len + 1);
		}
	}
	return temp;
}
wiz_string substr_wiz_string(wiz_string* str, size_t begin, size_t end)
{
	wiz_string temp;

	temp.len = (end - 1) - begin + 1;
	temp.moved = 0;

	if (temp.len > wiz_string_buffer_size) {
		temp.str = malloc(sizeof(char) * (temp.len + 1));

		strncpy(temp.str, get_cstr_wiz_string(str) + begin, end - begin);
		temp.str[end - begin] = '\0';
	}
	else {
		strncpy(temp.buffer, get_cstr_wiz_string(str) + begin, end - begin);
		temp.buffer[end - begin] = '\0';
	}
	return temp;
}
void assign_wiz_string(wiz_string* str1, wiz_string* str2)
{
	// str1 != str2 
	if (str1->len != str2->len || 1 == str1->moved) {
		free_wiz_string(str1);
		str1->len = str2->len;
		if (str2->len > wiz_string_buffer_size) {
			str1->str = malloc(sizeof(char)*(str2->len + 1));
		}
	}
	str1->moved = 0;
	strncpy(get_cstr_wiz_string(str1), get_cstr_wiz_string(str2), str2->len + 1);
}
// concat_and_assign_wiz_string  A = A + B
void concat_and_assign_wiz_string(wiz_string* str1, wiz_string* str2)
{
	const int len = str1->len + str2->len;
	wiz_string temp;
	temp.moved = 0;

	if (empty_wiz_string(str1)) {
		assign_wiz_string(str1, str2);
	}
	else {
		temp.len = str1->len + str2->len;
		if (temp.len > wiz_string_buffer_size) {
			temp.str = malloc(sizeof(char)*(temp.len + 1));
		}
		strncpy(get_cstr_wiz_string(&temp), get_cstr_wiz_string(str1), str1->len + 1);
		strncpy(get_cstr_wiz_string(&temp) + str1->len, get_cstr_wiz_string(str2), str2->len + 1);

		free_wiz_string(str1);

		*str1 = temp;
	}
}

// substr_and_assign_wiz_string  A = A.substring();
void substr_and_assign_wiz_string(wiz_string* str, size_t begin, size_t end)
{
	wiz_string temp;
	char x = str->str[end - 1];
	temp.len = (end - 1) - begin + 1;
	temp.moved = 0;

	if (temp.len > wiz_string_buffer_size) {
		temp.str = malloc(sizeof(char) * (temp.len + 1));
	}
	strncpy(get_cstr_wiz_string(&temp), get_cstr_wiz_string(str) + begin, end - begin + 1);

	//
	free_wiz_string(str);

	*str = temp;
}

// erase(shift, num--)_wiz_string
void erase_wiz_string(wiz_string* str, size_t idx)
{
	size_t i;

	for (i = idx; i < str->len - 1; ++i) {
		get_cstr_wiz_string(str)[i] = get_cstr_wiz_string(str)[i + 1];
	}
	get_cstr_wiz_string(str)[str->len - 1] = '\0';
	str->len--;

	if (str->len == wiz_string_buffer_size) {
		strncpy(str->buffer, str->str, wiz_string_buffer_size + 1);
		free(str->str);
	}
}
// starts_with_wiz_string
int starts_with_wiz_string(wiz_string* str, wiz_string* start_str)
{
	int result = 1;
	size_t i;

	if (str->len < start_str->len) {
		return 0;
	}

	//printf("size is %d\n", start_str->len);
	for (i = 0; i < start_str->len; ++i) {
		if (get_cstr_wiz_string(str)[i] == get_cstr_wiz_string(start_str)[i]) {
			//
		}
		else {
			result = 0;
			break;
		}
	}
	//printf("end\n");
	return result;
}
// ends_with_wiz_string
int lasts_with_wiz_string(wiz_string* str, wiz_string* last_str)
{
	int result = 1;
	int i, j;

	if (str->len < last_str->len) {
		return 0;
	}

	j = last_str->len - 1;
	for (i = str->len - 1; i >= 0 && j >= 0; --i) {
		if (get_cstr_wiz_string(str)[i] == get_cstr_wiz_string(last_str)[j]) {
			--j;
		}
		else {
			result = 0;
			break;
		}
	}

	return result;
}
// equal_wiz_string
int equal_wiz_string(wiz_string* str1, wiz_string* str2)
{
	if (str1->len != str2->len) { return 0; }
	return 0 == strcmp(get_cstr_wiz_string(str1), get_cstr_wiz_string(str2));
}

char back_wiz_string(wiz_string* str)
{
	return get_cstr_wiz_string(str)[str->len - 1];
}
char front_wiz_string(wiz_string* str)
{
	return get_cstr_wiz_string(str)[0];
}

void reverse_wiz_string(wiz_string* str)
{
	char ch;
	size_t i;

	for (i = 0; i < str->len / 2; ++i) {
		ch = get_cstr_wiz_string(str)[i];
		get_cstr_wiz_string(str)[i] = get_cstr_wiz_string(str)[str->len - 1 - i];
		get_cstr_wiz_string(str)[str->len - 1 - i] = ch;
	}
}
