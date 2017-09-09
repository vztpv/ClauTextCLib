

#include <stdio.h>
#include <string.h>

#include "utility.h"
//#include "wiz_string_builder.h"
//#include "wiz_string_tokenizer.h"


wiz_string wiz_fgets(FILE* file)
{
	wiz_string_builder builder;
	int num = 0;
	wiz_string result;
	int ch=0;

	init_wiz_string_builder(&builder, 1024, "", 0);


	while((ch = fgetc(file)) != '\n') {
		append_char_wiz_string_builder(&builder, ch);
	}
	
	result = make_wiz_string_from_cstr(str_wiz_string_builder(&builder, NULL));
	
	free_wiz_string_builder(&builder);

	return result;
}

wiz_string make_wiz_string_from_cstr(const char* cstr)
{
	return make_wiz_string(cstr, strlen(cstr));
}

wiz_string make_wiz_string(const char* cstr, const size_t size)
{
	wiz_string temp;


	init_wiz_string(&temp, cstr, size);

	return temp;
}
wiz_string make_wiz_string_from_char(const char ch)
{
	wiz_string temp;

	init_wiz_string(&temp, "A", 1);

	get_cstr_wiz_string(&temp)[0] = ch;

	return temp;
}

wiz_string make_empty_wiz_string()
{
	return make_wiz_string("", 0);
}
 

int is_integer(wiz_string* _str) {
	int state = 0;
	size_t i;
	wiz_string temp = make_wiz_string_from_other_wiz_string(_str);
	wiz_string* str = &temp;

	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		free_wiz_string(&temp);
		temp = substr_wiz_string(str, 1, size_wiz_string(str) - 1);
	}
	
	for (i = 0; i < size_wiz_string(str); ++i) {
		switch (state)
		{
		case 0:
			if ('+' == get_cstr_wiz_string(str)[i] || '-' == get_cstr_wiz_string(str)[i]) {
				state = 0;
			}
			else if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9')
			{
				state = 1;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 1:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 1;
			}
			else { free_wiz_string(&temp); return 0; }
		}
	}
	free_wiz_string(&temp);
	return 1 == state; /// chk..
}
 int is_double(wiz_string* _str) {
	 wiz_string temp = make_wiz_string_from_other_wiz_string(_str);
	 wiz_string* str = &temp;

	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		free_wiz_string(&temp);
		temp = substr_wiz_string(str, 1, size_wiz_string(str) - 1);
	}
	int state = 0;
	size_t i;
	for (i = 0; i < size_wiz_string(str); ++i) {
		switch (state)
		{
		case 0:
			if ('+' == get_cstr_wiz_string(str)[i] || '-' == get_cstr_wiz_string(str)[i]) {
				state = 0;
			}
			else if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9')
			{
				state = 1;
			}
			else { free_wiz_string(&temp);  return 0; }
			break;
		case 1:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 1;
			}
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 2;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 2:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 3:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else if ('e' == get_cstr_wiz_string(str)[i] || 'E' == get_cstr_wiz_string(str)[i]) {
				state = 4;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 4:
			if (get_cstr_wiz_string(str)[i] == '+' || get_cstr_wiz_string(str)[i] == '-') {
				state = 5;
			}
			else {
				state = 5;
			}
			break;
		case 5:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 6;
			}
			else {
				free_wiz_string(&temp); return 0;
			}
			break;
		case 6:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 6;
			}
			else {
				free_wiz_string(&temp); return 0;
			}
		}
	}
	free_wiz_string(&temp);
	return 3 == state || 6 == state;
}
 int is_date(wiz_string* _str) /// chk!!
{
	 wiz_string temp = make_wiz_string_from_other_wiz_string(_str);
	 wiz_string* str = &temp;

	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		free_wiz_string(&temp);
		temp = substr_wiz_string(str, 1, size_wiz_string(str) - 1);
	}
	int state = 0;
	size_t i;
	for (i = 0; i < size_wiz_string(str); ++i) {
		switch (state)
		{
		case 0:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9')
			{
				state = 1;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 1:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 1;
			}
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 2;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 2:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 3:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 4;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 4:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 5:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else { free_wiz_string(&temp); return 0; }
			break;
		}
	}
	free_wiz_string(&temp);
	return 5 == state;
}
 int is_datetime_a(wiz_string* _str) // yyyy.MM.dd.hh
{
	 wiz_string temp = make_wiz_string_from_other_wiz_string(_str);
	 wiz_string* str = &temp;


	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		free_wiz_string(&temp);
		temp = substr_wiz_string(str, 1, size_wiz_string(str) - 1);
	}
	int state = 0;
	size_t i;
	for (i = 0; i < size_wiz_string(str); ++i) {
		switch (state)
		{
		case 0:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9')
			{
				state = 1;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 1:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 1;
			}
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 2;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 2:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 3:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 4;
			}
			else { free_wiz_string(&temp); return 0; }
			break;
		case 4:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 5:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else if (get_cstr_wiz_string(str)[i] == '.') { state = 6; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 6:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 7; }
			else { free_wiz_string(&temp); return 0; }
			break;
		case 7:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 7; }
			else { free_wiz_string(&temp); return 0; }
			break;
		}
	}
	free_wiz_string(&temp);
	return 7 == state;
}
 int is_datetime_b(wiz_string* _str) // yyyy.MM.dd.hh.mm
{
	int state = 0;
	size_t i;
	wiz_string temp = make_wiz_string_from_other_wiz_string(_str);
	wiz_string* str = &temp;

	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		free_wiz_string(&temp);
		temp = substr_wiz_string(_str, 1, size_wiz_string(str) - 1);
	}
	for (i = 0; i < size_wiz_string(str); ++i) {
		switch (state)
		{
		case 0:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9')
			{
				state = 1;
			}
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 1:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') {
				state = 1;
			}
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 2;
			}
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 2:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 3:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 3; }
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 4;
			}
			else
			{
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 4:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 5:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 5; }
			else if (get_cstr_wiz_string(str)[i] == '.') { state = 6; }
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 6:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 7; }
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 7:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 7; }
			else if (get_cstr_wiz_string(str)[i] == '.') {
				state = 8;
			}
			else {
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 8:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 9; }
			else
			{
				free_wiz_string(&temp);
				return 0;
			}
			break;
		case 9:
			if (get_cstr_wiz_string(str)[i] >= '0' && get_cstr_wiz_string(str)[i] <= '9') { state = 9; }
			else {
				free_wiz_string(&temp); return 0;
			}
			break;
		}
	}
	free_wiz_string(&temp);
	return 9 == state;
}
int is_minus(wiz_string* str)
{
	wiz_string temp = *str;
	if (size_wiz_string(str) > 2 && get_cstr_wiz_string(str)[0] == back_wiz_string(str) && get_cstr_wiz_string(str)[0] == '\"') {
		temp = substr_wiz_string(str, 1, size_wiz_string(str) - 2);
	}
	return empty_wiz_string(&temp) == 0 && get_cstr_wiz_string(&temp)[0] == '-';
}
wiz_string make_wiz_string_from_other_wiz_string(wiz_string* other)
{
	wiz_string result;

	init_wiz_string(&result, get_cstr_wiz_string(other), size_wiz_string(other));

	return result;
}
//////////////////////////////////////////////////////////////////////////



int comp(const char* str1, const char* str2, const size_t n) /// isSameData
{
	size_t i;
	for (i = 0; i < n; ++i)
	{
		if (str1[i] != str2[i]) { return 0; }
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////
int get_type(wiz_string* str) {
	if (is_integer(str)) { return 1; }
	else if (is_double(str)) { return 2; }
	else if (is_datetime_b(str)) { return 6; }
	else if (is_datetime_a(str)) { return 5; }
	else if (is_date(str)) { return 4; }
	else return 3; // STRING
}

int compare_wiz_string_in_utility(wiz_string* str1, wiz_string* str2, wiz_string_builder* builder, int type) // type = 0
{
	int result = -1;

	int type1;
	int type2;

	wiz_string temp1, temp2;

	if (size_wiz_string(str1) > 2 && get_cstr_wiz_string(str1)[0] == back_wiz_string(str1) && get_cstr_wiz_string(str1)[0] == '\"')
	{
		temp1 = substr_wiz_string(str1, 1, size_wiz_string(str1) - 1);	
	}
	else {
		temp1 = make_wiz_string_from_other_wiz_string(str1);
	}
	if (size_wiz_string(str2) > 2 && get_cstr_wiz_string(str2)[0] == back_wiz_string(str1) && get_cstr_wiz_string(str2)[0] == '\"')
	{
		temp2 = substr_wiz_string(str2, 1, size_wiz_string(str2) - 1);
	}
	else {
		temp2 = make_wiz_string_from_other_wiz_string(str2);
	}

	type1 = get_type(&temp1);
	type2 = get_type(&temp2);

	if (type1 != type2) {
		free_wiz_string(&temp1);
		free_wiz_string(&temp2);
		return 2; // "ERROR";
	}

	if (TYPE_WIZ_STRING == type1 || type == 1)
	{
		int comparision = strcmp(get_cstr_wiz_string(str1), get_cstr_wiz_string(str2));
		
		free_wiz_string(&temp1);
		free_wiz_string(&temp2);

		if (comparision < 0) {
			return -1; // "< 0";
		}
		else if (0 == comparision) {
			return 0; // "== 0";
		}
		return 1; // "> 0";
	}
	else if (TYPE_WIZ_INTEGER == type1)
	{
		wiz_string x;
		wiz_string y;
		const int minusComp = is_minus(str1) && is_minus(str2);
		

		free_wiz_string(&temp1);
		free_wiz_string(&temp2);

		if (is_minus(str1) && !is_minus(str2)) { return -1; }
		else if (!is_minus(str1) && is_minus(str2)) { return 1; }


		if (0 == minusComp) {
			if (get_cstr_wiz_string(str1)[0] == '+') { erase_wiz_string(str1, 0); }
			if (get_cstr_wiz_string(str2)[0] == '+') { erase_wiz_string(str2, 0); }

			init_wiz_string(&x, get_cstr_wiz_string(str1), size_wiz_string(str1));
			reverse_wiz_string(&x);

			init_wiz_string(&y, get_cstr_wiz_string(str2), size_wiz_string(str2));
			reverse_wiz_string(&y);

			if (size_wiz_string(&x) < size_wiz_string(&y)) {
				clear_wiz_string_builder(builder);
				append_wiz_string_builder(builder, get_cstr_wiz_string(&x), size_wiz_string(&x));

				while (size_wiz_string_builder(builder) < size_wiz_string(&y)) {
					append_wiz_string_builder(builder, "0", 1);
				}
				free_wiz_string(&x);
				x = make_wiz_string(str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));
			}
			else {
				clear_wiz_string_builder(builder);
				append_wiz_string_builder(builder, get_cstr_wiz_string(&y), size_wiz_string(&y));

				while (size_wiz_string_builder(builder) < size_wiz_string(&x)) {
					append_wiz_string_builder(builder, "0", 1);
				}
				free_wiz_string(&y);
				y = make_wiz_string(str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));
			}
			reverse_wiz_string(&x);
			reverse_wiz_string(&y);

			result = compare_wiz_string_in_utility(&x, &y, builder, 1);
			
			free_wiz_string(&x);
			free_wiz_string(&y);

			return result;
		}
		else {

			free_wiz_string(&temp1);
			free_wiz_string(&temp2);

			init_wiz_string(&x, get_cstr_wiz_string(str1), size_wiz_string(str1));
			init_wiz_string(&y, get_cstr_wiz_string(str2), size_wiz_string(str2));
			erase_wiz_string((&x), 0);
			erase_wiz_string((&y), 0);
			
			result = compare_wiz_string_in_utility(&y, &x, builder, 0);
			
			free_wiz_string(&x);
			free_wiz_string(&y);
			return result;
		}
	}
	else if (TYPE_WIZ_DOUBLE == type1)
	{
		wiz_string_tokenizer tokenizer1;// (str1, ".", builder);
		wiz_string_tokenizer tokenizer2;// (str2, ".", builder);
		wiz_string x, x2;// = tokenizer1.nextToken();
		wiz_string y, y2; //= tokenizer2.nextToken();
		wiz_vector_wiz_string dilim;
		wiz_string dot;
		int chk = 0;


		free_wiz_string(&temp1);
		free_wiz_string(&temp2);

		init_wiz_string(&dot, ".", 1);
		init_wiz_vector_wiz_string(&dilim, 1);
		push_back_wiz_vector_wiz_string(&dilim, &dot);
		init_wiz_string_tokenizer(&tokenizer1, str1, &dilim, builder, 1);
		init_wiz_string_tokenizer(&tokenizer2, str2, &dilim, builder, 1);


		int z = compare_wiz_string_in_utility(&x, &y, builder, 0);
		if (0 == z)
		{
			x = *next_token_wiz_string_tokenizer(&tokenizer1);
			y = *next_token_wiz_string_tokenizer(&tokenizer2);

			if (size_wiz_string(&x) < size_wiz_string(&y)) {
				clear_wiz_string_builder(builder);
				append_wiz_string_builder(builder, get_cstr_wiz_string(&x), size_wiz_string(&x));

				while (size_wiz_string(&x) < size_wiz_string(&y)) {
					append_wiz_string_builder(builder, "0", 1);
				}
				init_wiz_string(&x2, str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));
				chk = 1;
			}
			else {
				clear_wiz_string_builder(builder);
				append_wiz_string_builder(builder, get_cstr_wiz_string(&y), size_wiz_string(&y));

				while (size_wiz_string(&y) < size_wiz_string(&x)) {
					append_wiz_string_builder(builder, "0", 1);
				}
				init_wiz_string(&y2, str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));
				chk = 2;
			}
			if (1 == chk) {
				result = compare_wiz_string_in_utility(&x2, &y, builder, 1);
				free_wiz_string(&x2);
			}
			else if (2 == chk) {
				result = compare_wiz_string_in_utility(&x, &y2, builder, 1);
				free_wiz_string(&y2);
			}
		}
		else
		{
			result = z;
		}
		
		free_wiz_string(&dot);
		free_wiz_vector_wiz_string(&dilim);

		free_wiz_string_tokenizer(&tokenizer1);
		free_wiz_string_tokenizer(&tokenizer2);

		return result;
	}
	else if (TYPE_WIZ_DATE == type1)
	{
		wiz_string_tokenizer tokenizer1;
		wiz_string_tokenizer tokenizer2;
		wiz_string dot;
		wiz_vector_wiz_string dilim;


		free_wiz_string(&temp1);
		free_wiz_string(&temp2);

		init_wiz_string(&dot, ".", 1);
		init_wiz_vector_wiz_string(&dilim, 1);
		push_back_wiz_vector_wiz_string(&dilim, &dot);
		init_wiz_string_tokenizer(&tokenizer1, str1, &dilim, builder, 1);
		init_wiz_string_tokenizer(&tokenizer2, str2, &dilim, builder, 1);

		result = 0;
		for (int i = 0; i < 3; ++i) {
			wiz_string* x = next_token_wiz_string_tokenizer(&tokenizer1);
			wiz_string* y = next_token_wiz_string_tokenizer(&tokenizer2);

			int comp = compare_wiz_string_in_utility(x, y, builder, 0);

			if (comp == -1) { result = comp; }
			else if (comp == 1) { result = comp; }
		}

		free_wiz_string(&dot);
		free_wiz_vector_wiz_string(&dilim);

		free_wiz_string_tokenizer(&tokenizer1);
		free_wiz_string_tokenizer(&tokenizer2);

		return result;
	}
	else if (TYPE_WIZ_DATETIMEA == type1) {
		wiz_string_tokenizer tokenizer1;
		wiz_string_tokenizer tokenizer2;
		wiz_string dot;
		wiz_vector_wiz_string dilim;

		free_wiz_string(&temp1);
		free_wiz_string(&temp2);

		init_wiz_string(&dot, ".", 1);
		init_wiz_vector_wiz_string(&dilim, 1);
		push_back_wiz_vector_wiz_string(&dilim, &dot);
		init_wiz_string_tokenizer(&tokenizer1, str1, &dilim, builder, 1);
		init_wiz_string_tokenizer(&tokenizer2, str2, &dilim, builder, 1);

		result = 0;
		for (int i = 0; i < 4; ++i) {
			wiz_string* x = next_token_wiz_string_tokenizer(&tokenizer1);
			wiz_string* y = next_token_wiz_string_tokenizer(&tokenizer2);

			int comp = compare_wiz_string_in_utility(x, y, builder, 0);

			if (comp == -1) { result = comp; }
			else if (comp == 1) { result = comp; }
		}

		free_wiz_string(&dot);
		free_wiz_vector_wiz_string(&dilim);

		free_wiz_string_tokenizer(&tokenizer1);
		free_wiz_string_tokenizer(&tokenizer2);

		return result;
	}
	else if (TYPE_WIZ_DATETIMEB == type2) {
		wiz_string_tokenizer tokenizer1;
		wiz_string_tokenizer tokenizer2;
		wiz_string dot;
		wiz_vector_wiz_string dilim;


		free_wiz_string(&temp1);
		free_wiz_string(&temp2);


		init_wiz_string(&dot, ".", 1);
		init_wiz_vector_wiz_string(&dilim, 1);
		push_back_wiz_vector_wiz_string(&dilim, &dot);
		init_wiz_string_tokenizer(&tokenizer1, str1, &dilim, builder, 1);
		init_wiz_string_tokenizer(&tokenizer2, str2, &dilim, builder, 1);

		result = 0;
		for (int i = 0; i < 5; ++i) {
			wiz_string* x = next_token_wiz_string_tokenizer(&tokenizer1);
			wiz_string* y = next_token_wiz_string_tokenizer(&tokenizer2);

			int comp = compare_wiz_string_in_utility(x, y, builder, 0);

			if (comp == -1) { result = comp; }
			else if (comp == 1) { result = comp; }
		}

		free_wiz_string(&dot);
		free_wiz_vector_wiz_string(&dilim);

		free_wiz_string_tokenizer(&tokenizer1);
		free_wiz_string_tokenizer(&tokenizer2);

		return result;
	}
	

	free_wiz_string(&temp1);
	free_wiz_string(&temp2);

	return 2; // ERROR
}

wiz_string bool_operation(wiz_string* op, wiz_string* x, wiz_string* y)
{
	if (0 == strcmp(get_cstr_wiz_string(x), "ERROR") || 0 == strcmp(get_cstr_wiz_string(y), "ERROR")) { return make_wiz_string("ERROR", 5); }
	if (0 == strcmp(get_cstr_wiz_string(op), "NOT")) { return 0 == strcmp(get_cstr_wiz_string(x), "TRUE")? make_wiz_string("FALSE", 5) : make_wiz_string("TRUE", 4); }
	else if (0 == strcmp(get_cstr_wiz_string(op), "AND")) {
		if (0 == strcmp(get_cstr_wiz_string(x), "TRUE") && 
			0 == strcmp(get_cstr_wiz_string(y), "TRUE")) { return make_wiz_string("TRUE", 4); }
		else {
			return make_wiz_string("FALSE", 5);
		}
	}
	else if (0 == strcmp(get_cstr_wiz_string(op), "OR")) {
		if (0 == strcmp(get_cstr_wiz_string(x), "TRUE") || 0 == strcmp(get_cstr_wiz_string(y), "TRUE")) { return make_wiz_string("TRUE", 4); }
		else {
			return make_wiz_string("FALSE", 5);
		}
	}
	else {
		return make_wiz_string("ERROR", 5);
	}
}

void add_space(wiz_string* str, wiz_string* temp, wiz_string_builder* builder)
{
	size_t i;
	wiz_string  result;
	clear_wiz_string_builder(builder);

	for (i = 0; i < size_wiz_string(str); ++i)
	{
		if ('=' == get_cstr_wiz_string(str)[i]) {
			append_wiz_string_builder(builder, " = ", 3);
		}
		else if ('{' == get_cstr_wiz_string(str)[i]) {
			append_wiz_string_builder(builder, " { ", 3);
		}
		else if ('}' == get_cstr_wiz_string(str)[i]) {
			append_wiz_string_builder(builder, " } ", 3);
		}
		else {
			append_char_wiz_string_builder(builder, get_cstr_wiz_string(str)[i]);
		}
	}
	init_wiz_string(&result, str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));

	assign_wiz_string(temp, &result);

	free_wiz_string(&result);
	
	//return temp;
}

wiz_string replace_wiz_string(wiz_string* origin, wiz_string* mark, wiz_string* changed, wiz_string_builder* builder)
{	
	size_t i;
	const char* pStr = get_cstr_wiz_string(origin);
	wiz_string result;

	clear_wiz_string_builder(builder);

	// chk??
	if (empty_wiz_string(mark)) { 
		init_wiz_string(&result, "", 0); // chk..
		return result; 
	}

	for (i = 0; i < size_wiz_string(origin); i++) {
		if (strlen(pStr + i) >= size_wiz_string(mark)
			&& comp(pStr + i, get_cstr_wiz_string(mark), size_wiz_string(mark)))
		{
			append_wiz_string_builder(builder, get_cstr_wiz_string(changed), size_wiz_string(changed));
			i = i + size_wiz_string(mark) - 1;
		}
		else
		{
			append_char_wiz_string_builder(builder, get_cstr_wiz_string(origin)[i]);
		}
	}

	init_wiz_string(&result, str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));

	return result;
}

wiz_string wiz_ll_to_string(long long x)
{
	wiz_string result;
	wiz_string_builder temp;
	int size = 1024;
	init_wiz_string_builder(&temp, size, "", 0);

	while (1) {
		int chk = snprintf(str_wiz_string_builder(&temp, NULL), size, "%lld", x);
		if (!(0 <= chk && chk < size)) {
			size = size * 2;
			free_wiz_string_builder(&temp);
			init_wiz_string_builder(&temp, size, "", 0);
		}
		else {
			temp.len = chk;
			break;
		}
	}

	init_wiz_string(&result, str_wiz_string_builder(&temp, NULL), size_wiz_string_builder(&temp));

	free_wiz_string_builder(&temp);
	return result;
}
wiz_string wiz_ld_to_string(long double x)
{
	wiz_string result;
	wiz_string_builder temp;
	int size = 1024;
	init_wiz_string_builder(&temp, size, "", 0);

	while (1) {
		int chk = snprintf(str_wiz_string_builder(&temp, NULL), size, "%Lf", x);
		if (!(0 <= chk && chk < size)) {
			size = size * 2;
			free_wiz_string_builder(&temp);
			init_wiz_string_builder(&temp, size, "", 0);
		}
		else {
			temp.len = chk;
			break;
		}
	}

	init_wiz_string(&result, str_wiz_string_builder(&temp, NULL), size_wiz_string_builder(&temp));
	
	free_wiz_string_builder(&temp);
	return result;
}


int rand_int() // 0~int_max
{
	size_t byteSize = sizeof(int);
	int val = 0;

	// char단위로 rand()호출,
	val = val | rand() % 0x7F;  // 0111 1111
	for (size_t i = 1; i < byteSize; i++)
	{
		val = val << 8; // left shift 1 byte(8bits)

		val = val | (rand() % 0xFF);
	}

	return val;
}

// clear

void clear_now_condition(condition* cond)
{
	size_t i;

	for (i = 0; i < size_wiz_stack_wiz_string(&cond->token_stack); ++i) {
		free_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, i));
	}
	for (i = 0; i < size_wiz_vector_wiz_string(&cond->token_vec); ++i) {
		free_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, i));
	}
}


// need to rename
int ChkExist(wiz_string* str) // for \"
{
	int state = -1;
	size_t i;

	for (i = 0; i < size_wiz_string(str); ++i)
	{
		if (0 >= state && i == 0 && '\"' == get_cstr_wiz_string(str)[i]) {
			state = 1;
		}
		else if (0 >= state && i > 0 && '\"' == get_cstr_wiz_string(str)[i] && '\\' != get_cstr_wiz_string(str)[i - 1])
		{
			state = 1;
		}
		else if (1 == state && i > 0 && '\\' != get_cstr_wiz_string(str)[i - 1] && '\"' == get_cstr_wiz_string(str)[i]) {
			state = 0;
		}
		else if (0 >= state && get_cstr_wiz_string(str)[i] == '#') {
			break;
		}
	}

	return 0 == state; // exist and valid !! chk - todo!
}

int comp_wiz_string_and_cstr(wiz_string* x, char* y)
{
	return 0 == strcmp(get_cstr_wiz_string(x), y);
}

wiz_string union_wiz_string(wiz_string* x, wiz_string* y)
{
	wiz_string result;
	wiz_string_builder builder;

	init_wiz_string_builder(&builder, size_wiz_string(x) + size_wiz_string(y), get_cstr_wiz_string(x), size_wiz_string(x));

	append_wiz_string_builder(&builder, get_cstr_wiz_string(y), size_wiz_string(y));

	result = make_wiz_string(str_wiz_string_builder(&builder, NULL), size_wiz_string_builder(&builder));

	free_wiz_string_builder(&builder);
	return result;
}

