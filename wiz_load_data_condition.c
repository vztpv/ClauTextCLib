
#include "wiz_load_data_condition.h"
#include "pair.h"
#include "utility.h"
#include "wiz_string.h"

pair_int_and_wiz_vector_any Get(wiz_string* var,  wiz_string* position, user_type* utPosition, user_type* global, wiz_string_builder* builder) {
	wiz_string valTemp = *position;
	wiz_string_tokenizer tokenizer; // (position, "/", builder, 1);
	user_type* utTemp;
	wiz_string root;
	wiz_vector_wiz_string delim_vec;
	pair_int_and_wiz_vector_any result;
	int chk = 0; // with result.

	init_wiz_string(&root, "root", 4);
	init_wiz_vector_wiz_string(&delim_vec, 1);
	push_back_wiz_vector_wiz_string(&delim_vec, &root);
	init_wiz_string_tokenizer(&tokenizer, position, &delim_vec, builder, 1);

	if (0 == has_more_tokens_wiz_string_tokenizer(&tokenizer)) {
		utTemp = utPosition;
	}
	else {
		if (!equal_wiz_string(next_token_wiz_string_tokenizer(&tokenizer), &root)) {
			utTemp = utPosition;
		}
		else { // equal to token == "root"  // root/x 
			valTemp = substr_wiz_string(position, 5, size_wiz_string(position));
			utTemp = global;
			chk = 1;
		}
	}

	free_wiz_vector_wiz_string(&delim_vec);
	free_wiz_string_tokenizer(&tokenizer);
	free_wiz_string(&root);
	result = find_user_type_in_user_type(utTemp, &valTemp, builder);
	if (chk) {
		free_wiz_string(&valTemp);
	}
	return result;
}
// val -> rename?, parameter:option -> removal?
wiz_string GetValueA(wiz_string* op,  wiz_string* var,  wiz_string* val, user_type* utPosition, user_type* global, wiz_string_builder* builder)
{
	size_t i;
	/// ExistItem, ExistUserType
	if (NULL == utPosition) { return make_wiz_string("ERROR", 5); }

	if (0 == strcmp("EXISTITEM", get_cstr_wiz_string(op))) { /// option == 1?	
		pair_int_and_wiz_vector_any x = Get(var, val, utPosition, global, builder);
		if (x.first) {
			for (i = 0; i < size_wiz_vector_any(&(x.second)); ++i) {
				wiz_vector_item_type temp = get_item_in_user_type((user_type*)(get_wiz_vector_any(&(x.second), i)), var);
				if (size_wiz_vector_item_type(&temp) > 0)
				{
					free_wiz_vector_item_type(&temp);
					free_wiz_vector_any(&x.second);
					return make_wiz_string("TRUE", 4);
				}
				free_wiz_vector_item_type(&temp);
				free_wiz_vector_any(&x.second);
			}
			return make_wiz_string("FALSE", 5);
		}
		return make_wiz_string("FALSE", 5);
	}
	else if (0 == strcmp("EXISTUSERTYPE", get_cstr_wiz_string(op))) { /// option == 1?	
		pair_int_and_wiz_vector_any x = Get(var, val, utPosition, global, builder);
		if (x.first) {
			for (i = 0; i < size_wiz_vector_any(&(x.second)); ++i) {
				wiz_vector_any temp = get_user_type_item_in_user_type(get_wiz_vector_any(&(x.second), i), var);
				if (size_wiz_vector_any(&temp) > 0)
				{
					free_wiz_vector_any(&temp);
					free_wiz_vector_any(&x.second);
					return make_wiz_string("TRUE", 4);
				}
				free_wiz_vector_any(&temp);
				free_wiz_vector_any(&x.second);
			}
			return make_wiz_string("FALSE", 5);
		}
		return make_wiz_string("FALSE", 5);
	}
	else if (0 == strcmp("NOTEXISTITEM", get_cstr_wiz_string(op))) { /// option == 2 ?
		pair_int_and_wiz_vector_any x = Get(var, val, utPosition, global, builder);
		if (x.first) {
			for (i = 0; i < size_wiz_vector_any(&(x.second)); ++i) {
				wiz_vector_item_type temp = get_item_in_user_type(get_wiz_vector_any(&(x.second), i), var);
				if (0 < size_wiz_vector_item_type(&temp))
				{
					free_wiz_vector_item_type(&temp);
					free_wiz_vector_any(&x.second);
					return make_wiz_string("FALSE", 5);
				}
				free_wiz_vector_item_type(&temp);
				free_wiz_vector_any(&x.second);
			}
			return make_wiz_string("TRUE", 4);
		}
		return make_wiz_string("FALSE", 5);
	}
	else if (0 == strcmp("NOTEXISTUSERTYPE", get_cstr_wiz_string(op))) { /// option == 2 ?
		pair_int_and_wiz_vector_any x = Get(var, val, utPosition, global, builder);
		if (x.first) {
			for (i = 0; i <  size_wiz_vector_any(&x.second); ++i) {
				wiz_vector_any temp = get_user_type_item_in_user_type(get_wiz_vector_any(&(x.second), i), var);
				if (0 < size_wiz_vector_any(&temp))
				{
					free_wiz_vector_any(&temp);
					free_wiz_vector_any(&x.second);
					return make_wiz_string("FALSE", 5);
				}
				free_wiz_vector_any(&temp);
				free_wiz_vector_any(&x.second);
			}
			return make_wiz_string("TRUE", 4);
		}
		return make_wiz_string("FALSE", 5);
	}

	return make_wiz_string("ERROR", 5);
}
wiz_string GetValueB(wiz_string* op,  wiz_string* var1,  wiz_string* position1,  wiz_string* var2,  wiz_string* position2,
	user_type* utPosition, user_type* global, wiz_string_builder* builder,  wiz_string* option) // = "FALSE")
{
	size_t i, j;
	wiz_vector_item_type value1;
	wiz_vector_item_type value2;
	pair_int_and_wiz_vector_any x = Get(var1, position1, utPosition, global, builder);
	pair_int_and_wiz_vector_any y = Get(var2, position2, utPosition, global, builder);
	wiz_string result;
	int chk = 0; // with result?

	// COMP<, COMP>, EQ, NOTEQ
	if (NULL == utPosition) { return make_wiz_string("ERROR", 5); }

	if (0 != strcmp("~", get_cstr_wiz_string(position1)) && 0 == x.first)
	{
		free_wiz_vector_any(&x.second);
		free_wiz_vector_any(&y.second);
		return make_wiz_string("ERROR GV1", 9);
	}
	if (0 != strcmp("~", get_cstr_wiz_string(position2)) && 0 == y.first)
	{
		free_wiz_vector_any(&x.second);
		free_wiz_vector_any(&y.second);
		return make_wiz_string("ERROR GV2", 9);
	}
	//
	if (((x.first && size_wiz_vector_any(&(x.second)) > 1) ||
		(y.first && size_wiz_vector_any(&(y.second)) > 1))) {
		free_wiz_vector_any(&x.second);
		free_wiz_vector_any(&y.second);
		return make_wiz_string("ERROR GV3", 9);
	}

	// added..
	if (0 != strcmp("~", get_cstr_wiz_string(position1))) {
		value1 = get_item_in_user_type(get_wiz_vector_any(&x.second, 0), var1);
	}
	if (0 != strcmp("~", get_cstr_wiz_string(position2))) {
		value2 = get_item_in_user_type(get_wiz_vector_any(&y.second, 0), var2);
	}
	//
	if (0 == strcmp("~", get_cstr_wiz_string(position1))) {
		item_type temp;
		init_wiz_vector_item_type(&value1, 1);
		temp.name = make_empty_wiz_string();
		temp.value = *var1;
		push_back_wiz_vector_item_type(&value1, &temp);
	}
	if (0 == strcmp("~", get_cstr_wiz_string(position2))) {
		item_type temp;
		init_wiz_vector_item_type(&value2, 1);
		temp.name = make_empty_wiz_string();
		temp.value = *var2;
		push_back_wiz_vector_item_type(&value2, &temp);
	}

	while (1) {
		if (empty_wiz_vector_item_type(&value1)) {
			result = make_wiz_string("ERROR GV4", 9); chk = 1; break;
		}
		if (empty_wiz_vector_item_type(&value2)) {
			result = make_wiz_string("ERROR GV5", 9); chk = 1; break;
		}

		if (0 == strcmp("FALSE", get_cstr_wiz_string(option)) && size_wiz_vector_item_type(&value1) > 1 || size_wiz_vector_item_type(&value2) > 1) {
			result = make_wiz_string("ERROR GV6", 9); chk = 1; break;
		}

		if (0 == strcmp("COMP<", get_cstr_wiz_string(op))) {
			if (0 != strcmp("FALSE", get_cstr_wiz_string(option))) { // ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j < size_wiz_vector_item_type(&value2); ++j) {
						if (compare_wiz_string_in_utility(&(get_wiz_vector_item_type(&value1, i)->value), &(get_wiz_vector_item_type(&value2, j)->value), builder, 0) == -1) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("TRUE", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }
				if (0 == strcmp("1", get_cstr_wiz_string(option))) { chk = 1; result = make_wiz_string("FALSE", 5); break; }
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("1", 4); chk = 1; break;
				}
			}
			else {
				if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0) == -1) {
					result = make_wiz_string("1", 4); chk = 1; break;
				}
			}
			result = make_wiz_string("FALSE", 5);
		}
		else if (0 == strcmp(get_cstr_wiz_string(op), "COMP<EQ")) {
			if (0 != strcmp("0", get_cstr_wiz_string(option))) { /// ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j <size_wiz_vector_item_type(&value2); ++j) {
						int temp = compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, i)->value, &get_wiz_vector_item_type(&value2, i)->value, builder, 0);
						if (temp == -1 || temp == 0) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("1", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }
				if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
					result = make_wiz_string("FALSE", 5); chk = 1;
					break;
				}
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			else {
				int temp = compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0);
				if (temp == -1 || temp == 0) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			result = make_wiz_string("FALSE", 5);
		}
		else if (0 == strcmp(get_cstr_wiz_string(op), "COMP>")) {
			if (0 != strcmp("0", get_cstr_wiz_string(option))) { /// ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j <size_wiz_vector_item_type(&value2); ++j) {
						if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, i)->value, &get_wiz_vector_item_type(&value2, i)->value, builder, 0) == 1) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) {
								result = make_wiz_string("TRUE", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) {
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }
				if (0 == strcmp("1", get_cstr_wiz_string(option))) {
					result = make_wiz_string("FALSE", 5); chk = 1;
					break;
				}
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			else {
				if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0) == 1) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			result = make_wiz_string("FALSE", 5); chk = 1; break;
		}
		else if (0 == strcmp(get_cstr_wiz_string(op), "COMP>EQ")) {
			if (0 != strcmp("0", get_cstr_wiz_string(option))) { /// ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j <size_wiz_vector_item_type(&value2); ++j) {
						int temp = compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, i)->value, &get_wiz_vector_item_type(&value2, i)->value, builder, 0);
						if (temp == 1 || temp == 0) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) {
								result = make_wiz_string("TRUE", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }

				if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
					result = make_wiz_string("FALSE", 5); chk = 1;
					break;
				}
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			else {
				int temp = compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0);
				if (temp == 1 || temp == 0) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			result = make_wiz_string("FALSE", 5);
		}
		else if (0 == strcmp(get_cstr_wiz_string(op), "EQ")) {
			if (0 != strcmp("0", get_cstr_wiz_string(option))) { /// ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j <size_wiz_vector_item_type(&value2); ++j) {
						if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, i)->value, &get_wiz_vector_item_type(&value2, i)->value, builder, 0) == 0) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("TRUE", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }

				if (0 == strcmp("1", get_cstr_wiz_string(option))) {
					result = make_wiz_string("FALSE", 5); chk = 1;
					break;
				}
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			else {
				if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0) == 0) {
					result = make_wiz_string("TRUE", 4); chk = 1; break;
				}
			}
			return make_wiz_string("FALSE", 5);
		}
		else if (0 == strcmp(get_cstr_wiz_string(op), "NOTEQ")) {
			if (0 != strcmp("0", get_cstr_wiz_string(option))) { /// ToDo.. // 0. just 1-1, // 1. for any case // 2. for all case
				for (i = 0; i < size_wiz_vector_item_type(&value1); ++i) {
					for (j = 0; j <size_wiz_vector_item_type(&value2); ++j) {
						if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, i)->value, &get_wiz_vector_item_type(&value2, i)->value, builder, 0) != 0) {
							if (0 == strcmp("1", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("TRUE", 4); chk = 1; break;
							}
						}
						else {
							if (0 == strcmp("2", get_cstr_wiz_string(option))) { 
								result = make_wiz_string("FALSE", 5); chk = 1; break;
							}
						}
					}
					if (chk) { break; }
				}
				if (chk) { break; }
				if (0 == strcmp("1", get_cstr_wiz_string(option))) { result = make_wiz_string("FALSE", 5); chk = 1;
				break;
				}
				else if (0 == strcmp("2", get_cstr_wiz_string(option))) {
					result = make_wiz_string("TRUE", 4); chk = 1;
					break;
				}
			}
			else {
				if (compare_wiz_string_in_utility(&get_wiz_vector_item_type(&value1, 0)->value, &get_wiz_vector_item_type(&value2, 0)->value, builder, 0) != 0) {
					result = make_wiz_string("TRUE", 4); chk = 1;
					break;
				}
			}
			result = make_wiz_string("FALSE", 5); chk = 1;
			break;
		}

		break;
	}
	result = make_wiz_string("ERROR GV7", 9); chk = 1;

	free_wiz_vector_any(&x.second);
	free_wiz_vector_any(&y.second);
	free_wiz_vector_item_type(&value1);
	free_wiz_vector_item_type(&value2);
	return result;
}
wiz_string GetValue3(wiz_string* op,  wiz_string* val,  wiz_string* dir, user_type* utPosition, user_type* global, wiz_string_builder* builder)
{
	size_t i;
	pair_int_and_wiz_vector_any x;
	if (NULL == utPosition) { return make_wiz_string("ERROR", 5); }

	x = Get(val, dir, utPosition, global, builder);

	if (0 == x.first || size_wiz_vector_any(&x.second) != 1) {
		free_wiz_vector_any(&x.second);
		return make_wiz_string("ERROR", 5);
	}

	if (0 == strcmp(get_cstr_wiz_string(op), "EXISTITEMBYVALUE"))
	{
		for (i = 0; i < get_item_list_size_in_user_type((user_type*)get_wiz_vector_any(&x.second, 0)); ++i) {
			if (equal_wiz_string(val, &get_item_list_in_user_type((user_type*)&x.second, 0)->value)) {
				free_wiz_vector_any(&x.second);
				return make_wiz_string("TRUE", 4);
			}
		}
		free_wiz_vector_any(&x.second);
		return make_wiz_string("FALSE", 5);
	}
	free_wiz_vector_any(&x.second);
	return make_wiz_string("ERROR", 5);
}

void init_in_condition(condition* cond, wiz_string* cond_str, user_type* position, user_type* global, wiz_string_builder* builder)
{
	int evalue = 0;
	wiz_string str;
	wiz_string_tokenizer tokenizer; // (str, { " ", "\t", "\n", "\r" }, builder, 1);
	wiz_vector_wiz_string vec_of_str;
	wiz_string empty_str;

	cond->braceNum = 0;
	cond->builder = builder;
	cond->cond = *cond_str;
	cond->global = global;
	cond->i = 0;
	cond->position = position;

	init_wiz_string(&str, "", 0);
	init_wiz_stack_wiz_string(&cond->token_stack, 1);
	init_wiz_vector_wiz_string(&cond->token_vec, 1);
	init_wiz_vector_wiz_string(&vec_of_str, 1);
	push_back_cstr_wiz_vector_wiz_string(&vec_of_str, " ");
	push_back_cstr_wiz_vector_wiz_string(&vec_of_str, "\t");
	push_back_cstr_wiz_vector_wiz_string(&vec_of_str, "\r");
	push_back_cstr_wiz_vector_wiz_string(&vec_of_str, "\n");
	add_space(cond_str, &str, builder);

	init_wiz_string_tokenizer(&tokenizer, &str, &vec_of_str, builder, 1);
	init_wiz_string(&empty_str, "", 0);

	
	while (has_more_tokens_wiz_string_tokenizer(&tokenizer)) {
		wiz_string* temp = next_token_wiz_string_tokenizer(&tokenizer);

		if (0 == strcmp(get_cstr_wiz_string(temp), "^")) { // ^ or _   -> only _ ?
			assign_wiz_string(temp, &empty_str);
		}
		else if (0 == strcmp(get_cstr_wiz_string(temp), "_")) { // ^ or _   -> only _ ?
			assign_wiz_string(temp, &empty_str);
		}
		push_back_wiz_vector_wiz_string(&cond->token_vec, temp);
	}

	free_wiz_string(&empty_str);
	free_wiz_string(&str);
	free_wiz_vector_wiz_string(&vec_of_str);
	free_wiz_string_tokenizer(&tokenizer);
}

void free_in_condition(condition* cond)
{
	free_wiz_stack_wiz_string(&cond->token_stack);
	free_wiz_vector_wiz_string(&cond->token_vec);
	free_wiz_string(&cond->cond);
}

int next_in_condition(condition* cond)
{
	if (cond->i >= size_wiz_vector_wiz_string(&cond->token_vec)) { return 0; }
	if (0 == size_wiz_vector_wiz_string(&cond->token_vec)) {
		return 0;
	}
	{
		if (0 != strcmp("=", get_cstr_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, cond->i)))
			&& 0 != strcmp("{", get_cstr_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, cond->i)))
			&& 0 != strcmp("}", get_cstr_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, cond->i)))) {
			push_wiz_stack_wiz_string(&cond->token_stack, get_wiz_vector_wiz_string(&cond->token_vec, cond->i));
		}

		if (0 == strcmp("{", get_cstr_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, cond->i)))) {
			cond->braceNum++;
		}
		else if (0 == strcmp("}", get_cstr_wiz_string(get_wiz_vector_wiz_string(&cond->token_vec, cond->i)))) {
			cond->braceNum--;

			// COMP<, COMP<EQ, COMP>, COMP>EQ, EQ, NOTEQ
			if (size_wiz_stack_wiz_string(&cond->token_stack) >= 6 && 
				( 0 == strcmp("COMP<", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				|| 0 == strcmp("COMP<EQ", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				|| 0 == strcmp("COMP>", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				|| 0 == strcmp("COMP>EQ", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				|| 0 == strcmp("EQ", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				|| 0 == strcmp("NOTEQ", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6)))
				)
			)
			{
				wiz_string* op = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 6);
				wiz_string* var1 = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 5);
				wiz_string* position1 = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 4);
				wiz_string* var2 = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 3);
				wiz_string* position2 = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2);
				wiz_string* option = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 1);
				wiz_string result;

				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);

				result = GetValueB(op, var1, position1, var2, position2, cond->position, cond->global, cond->builder, option);

				push_wiz_stack_wiz_string(&cond->token_stack, &result);
				
				free_wiz_string(&result);
			}
			else if (size_wiz_stack_wiz_string(&cond->token_stack) >= 3 &&
				0 == strcmp("EXISTITEMBYVALUE", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 3)))
			)
			{
				wiz_string* op = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 3);
				wiz_string* val = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2);
				wiz_string* dir = get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 1);
				wiz_string result;

				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);

				result = GetValue3(op, val, dir, cond->position, cond->global, cond->builder);
				
				push_wiz_stack_wiz_string(&cond->token_stack, &result);

				free_wiz_string(&result);
			}
			else if (size_wiz_stack_wiz_string(&cond->token_stack) >= 3 && 0 != strcmp("NOT", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2)))) {
				wiz_string* op =get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 3);
				wiz_string* operand1 =get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2);
				wiz_string* operand2 =get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 1);
				
				if (strcmp(get_cstr_wiz_string(op), "AND") == 0 || 0 == strcmp(get_cstr_wiz_string(op), "OR")) {
					wiz_string result;

					pop_wiz_stack_wiz_string(&cond->token_stack);
					pop_wiz_stack_wiz_string(&cond->token_stack);
					pop_wiz_stack_wiz_string(&cond->token_stack);

					result = bool_operation(op, operand1, operand2);

					push_wiz_stack_wiz_string(&cond->token_stack, &result);

					free_wiz_string(&result);
				}
				else { // EXIST, NOTEXIST for ( ITEM or USERTYPE )
					wiz_string result;
					pop_wiz_stack_wiz_string(&cond->token_stack);
					pop_wiz_stack_wiz_string(&cond->token_stack);
					pop_wiz_stack_wiz_string(&cond->token_stack);
					
					result = GetValueA(op, operand1, operand2, cond->position, cond->global, cond->builder);
					
					push_wiz_stack_wiz_string(&cond->token_stack, &result);

					free_wiz_string(&result);
				}
			}
			else if (size_wiz_stack_wiz_string(&cond->token_stack) >= 2 && 0 == strcmp("NOT", get_cstr_wiz_string(get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2)))) {
				wiz_string* op =get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 2);
				wiz_string* operand1 =get_wiz_stack_wiz_string(&cond->token_stack, size_wiz_stack_wiz_string(&cond->token_stack) - 1);
				wiz_string result;

				pop_wiz_stack_wiz_string(&cond->token_stack);
				pop_wiz_stack_wiz_string(&cond->token_stack);
				
				result = bool_operation(op, operand1, operand1);

				push_wiz_stack_wiz_string(&cond->token_stack, &result);

				free_wiz_string(&result);
			}
		}
		++(cond->i);
	}
	return 1;
}


wiz_stack_wiz_string* now_in_condition(condition* cond)
{
	return &(cond->token_stack);
}


