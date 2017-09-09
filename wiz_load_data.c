
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>

#include "wiz_load_data.h"
#include "wiz_array_queue_token.h"
#include "wiz_load_data_condition.h"
#include "utility.h"


/*
struct event_info
{
	int valid;
	user_type* eventUT;
	wiz_stack_any nowUT; //
	wiz_stack_size_t userType_idx;
	wiz_map_wiz_string_and_wiz_string parameters;
	wiz_map_wiz_string_and_wiz_string locals;
	wiz_string id; //
	wiz_stack_wiz_string conditionStack;
	wiz_stack_int state;
	wiz_string return_value;
	wiz_string option;
};
*/
void init_event_info(event_info* info)
{
	info->valid = 1;

	info->eventUT = NULL;

	init_wiz_stack_any(&info->nowUT, 1);
	init_wiz_stack_size_t(&info->userType_idx, 1);
	init_wiz_map_wiz_string_and_wiz_string(&info->parameters);
	init_wiz_map_wiz_string_and_wiz_string(&info->locals);
	init_wiz_string(&info->id, "", 0);
	init_wiz_stack_wiz_string(&info->conditionStack, 1);
	init_wiz_stack_int(&info->state, 1);
	init_wiz_string(&info->return_value, "", 0);
	init_wiz_string(&info->option, "", 0);
}


event_info deep_copy_event_info(event_info* info) //chk
{
	int i;
	event_info copyResult;

	copyResult.valid = info->valid;
	copyResult.eventUT = info->eventUT;
	
	init_wiz_stack_any(&copyResult.nowUT, 1);
	{
		for (i = 0; i < info->nowUT.count; ++i) {
			user_type temp = *(user_type*)get_wiz_stack_any(&info->nowUT, i);
			push_wiz_stack_any(&copyResult.nowUT, (void*)&temp);
		}
	}

	init_wiz_stack_size_t(&copyResult.userType_idx, 1);
	for (i = 0; i < size_wiz_stack_size_t(&info->userType_idx); ++i) {
		push_wiz_stack_size_t(&copyResult.userType_idx, get_wiz_stack_size_t(&info->userType_idx, i));
	}

	init_wiz_map_wiz_string_and_wiz_string(&copyResult.parameters);
	if (info->parameters.count != 0) {
		pair_wiz_string_and_wiz_string* arr = malloc(sizeof(pair_wiz_string_and_wiz_string) * info->parameters.count);

		inorder_wiz_string_and_wiz_string(&info->parameters, arr);

		for (i = 0; i < info->parameters.count; ++i) {
			pair_wiz_string_and_wiz_string temp;
			temp.first = make_wiz_string_from_other_wiz_string(&arr[i].first);
			temp.second = make_wiz_string_from_other_wiz_string(&arr[i].second);

			insert_wiz_map_wiz_string_and_wiz_string(&copyResult.parameters, &temp, 0);
		}
		free(arr);
		balancing_wiz_map_wiz_string_and_wiz_string(&copyResult.parameters);
	}

	init_wiz_map_wiz_string_and_wiz_string(&copyResult.locals);
	if (info->locals.count != 0) {
		pair_wiz_string_and_wiz_string* arr = malloc(sizeof(pair_wiz_string_and_wiz_string) * info->locals.count);

		inorder_wiz_string_and_wiz_string(&info->locals, arr);

		for (i = 0; i < info->locals.count; ++i) {
			pair_wiz_string_and_wiz_string temp;
			temp.first = make_wiz_string_from_other_wiz_string(&arr[i].first);
			temp.second = make_wiz_string_from_other_wiz_string(&arr[i].second);

			insert_wiz_map_wiz_string_and_wiz_string(&copyResult.locals, &temp, 0);
		}
		free(arr);
		balancing_wiz_map_wiz_string_and_wiz_string(&copyResult.locals);
	}
	init_wiz_string(&copyResult.id, get_cstr_wiz_string(&info->id), size_wiz_string(&info->id));
	init_wiz_stack_wiz_string(&copyResult.conditionStack, 1);
	{
		for (i = 0; i < info->conditionStack.count; ++i) {
			wiz_string temp = make_wiz_string_from_other_wiz_string(get_wiz_stack_wiz_string(&info->conditionStack, i));
			push_wiz_stack_wiz_string(&copyResult.conditionStack, &temp);
		}
	}
	init_wiz_stack_int(&copyResult.state, 1);
	{
		for (i = 0; i < info->state.count; ++i) {
			push_wiz_stack_int(&copyResult.state, get_wiz_stack_int(&info->state, i));
		}
	}
	copyResult.return_value = make_wiz_string_from_other_wiz_string(&info->return_value);
	copyResult.option = make_wiz_string_from_other_wiz_string(&info->option);

	return copyResult;
}

void free_all_event_info(event_info* info)
{
	int i;


	info->valid = 0;
	//info->eventUT; //

	free_wiz_stack_any(&info->nowUT);
	free_wiz_stack_size_t(&info->userType_idx);
	//
	{//chk
		if (info->parameters.count != 0) {
	    	pair_wiz_string_and_wiz_string* temp = malloc(sizeof(pair_wiz_string_and_wiz_string)*(info->parameters.count));
			inorder_wiz_string_and_wiz_string(&info->parameters, temp);
			for (i = 0; i < info->parameters.count; ++i) {
				free_wiz_string(&temp[i].first);
				free_wiz_string(&temp[i].second);
			}
			free(temp);
		}
	}
	free_wiz_map_wiz_string_and_wiz_string(&info->parameters);
	//
	{//chk
		if (info->locals.count > 0) {
			pair_wiz_string_and_wiz_string* temp = malloc(sizeof(pair_wiz_string_and_wiz_string)*(info->locals.count));
			inorder_wiz_string_and_wiz_string(&info->locals, temp);
			for (i = 0; i < info->locals.count; ++i) {
				free_wiz_string(&temp[i].first);
				free_wiz_string(&temp[i].second);
			}
			free(temp);
		}
	}
	free_wiz_map_wiz_string_and_wiz_string(&info->locals);
	//
	free_wiz_string(&info->id);
	//
	{
		for (i = 0; i < size_wiz_stack_wiz_string(&info->conditionStack); ++i) {
			free_wiz_string(get_wiz_stack_wiz_string(&info->conditionStack, i));
		}
	}
	free_wiz_stack_wiz_string(&info->conditionStack);
	//
	free_wiz_stack_int(&info->state);
	free_wiz_string(&info->return_value);
	free_wiz_string(&info->option);
}

// rename to find_idx?
int find( char* cstr,  char x,  size_t before,  size_t n)
{
	size_t i = 0;

	for (i = before + 1; i < n; ++i) {
		if (cstr[i] == x) {
			return i;
		}
	}
	return -1;
}

//  to global.h?
int is_whitespace( char ch)
{
	return ' ' == ch || '\t' == ch || '\r' == ch || '\n' == ch;
}

// to do
int is_state0( long long state_reserve)
{
	return 1 == state_reserve;
}

int equal(wiz_string* str1, wiz_string* str2)
{
	if (!str1 || !str2) { return 0; }
	return 0 == strcmp(get_cstr_wiz_string(str1), get_cstr_wiz_string(str2));
}

int chk_comment(user_type* ut, wiz_array_queue_token* token_vec, int offset)
{
	int count = 0;
	size_t idx = 0;
	token* x;

	if (empty_wiz_array_queue_token(token_vec)) {
		return 0;
	}

	do {
		x = get_wiz_array_queue_token(token_vec, idx);

		if (x->isComment) {
			push_comment_in_user_type(ut, &(x->str));
			erase_in_wiz_array_queue_token(token_vec, idx);
		}
		else if (count == offset - 1) {
			return 1;
		}
		else {
			count++;
			idx++;
		}

		if (idx == size_wiz_array_queue_token(token_vec)) {
			break;
		}
	} while (1);
	return 0;
}

wiz_string* Top(user_type* ut, wiz_array_queue_token* token_vec)
{
	if (get_wiz_array_queue_token(token_vec, 0)->isComment && 0 == chk_comment(ut, token_vec, 1)) {
		return NULL;
	}
	if (empty_wiz_array_queue_token(token_vec)) {
		return NULL;
	}

	return &(get_wiz_array_queue_token(token_vec, 0)->str);
}

int Pop(user_type* ut, wiz_array_queue_token* token_vec, wiz_string* result)
{
	token temp;

	if (get_wiz_array_queue_token(token_vec, 0)->isComment && 0 == chk_comment(ut, token_vec, 1)) {
		return 0;
	}

	if (empty_wiz_array_queue_token(token_vec)) {
		return 0;
	}

	temp = *front_wiz_array_queue_token(token_vec);
	pop_wiz_array_queue_token(token_vec);

	if (result != NULL) {
		free_wiz_string(result);
		*result = temp.str;
	}
	else {
		free_wiz_string(&(temp.str));
	}

	return 1;
}
pair_int_and_token LookUp(user_type* ut, wiz_array_queue_token* token_vec) {
	pair_int_and_token temp;

	if (!(size_wiz_array_queue_token(token_vec) >= 2 && !get_wiz_array_queue_token(token_vec, 0)->isComment && !get_wiz_array_queue_token(token_vec, 1))) {
		if (0 == chk_comment(ut, token_vec, 2)) {
			temp.first = 0;
			return temp;
		}
	}

	if (size_wiz_array_queue_token(token_vec) >= 2) {
		temp.first = 1;
		temp.second = *get_wiz_array_queue_token(token_vec, 1);
	}
	else {
		temp.first = 0;
	}

	return temp;
}

// only one exist or do not exist
item_type GetItem(user_type* ut, wiz_string* name) {
	 wiz_vector_item_type temp = get_item_in_user_type(ut, name);
	 item_type* result = get_wiz_vector_item_type(&temp, 0);
	 return *result;
}

wiz_vector_any GetUserType(user_type* ut, wiz_string* name)
{
	return get_user_type_item_in_user_type(ut, name);
}

// chk more thinking!
wiz_string Find(user_type* ut, wiz_string* str, wiz_string_builder* builder)
{ // wiz_string ´ë½Å wiz_vector_wiz_string ??
	int count = 0;
	int idx = -1;
	wiz_string result;
	int i;
	
	
	for (i = size_wiz_string(str) - 1; i >= 0; --i) {
		if ('/' == get_cstr_wiz_string(str)[i]) {
			if (count == 0) {
				idx = i;
			}
			count++;
		}
	}

	
	if (count <= 1) // <= 1
	{
		return make_empty_wiz_string();
	}
	else {
		pair_int_and_wiz_vector_any x;
		wiz_string substr;
		size_t i, j;
		substr = substr_wiz_string(str, 0, idx + 1);

		x = find_user_type_in_user_type(ut, &substr, builder);
		free_wiz_string(&substr);
		
		clear_wiz_string_builder(builder);
		if (x.first == 0) { return make_empty_wiz_string(); }
		for (i = 0; i < size_wiz_vector_any(&x.second); ++i) {
			wiz_string itemName = substr_wiz_string(str, idx + 1, size_wiz_string(str));
			wiz_string it; // IT_STR
			
			init_wiz_string(&it, "$it", 3);

			if (starts_with_wiz_string(&itemName, &it) && size_wiz_string(&itemName) >= 4) {
				wiz_string number = substr_wiz_string(&itemName, 3, size_wiz_string(&itemName));
				int itemIdx = atoi(get_cstr_wiz_string(&number));
				wiz_string* value = &get_item_list_in_user_type((user_type*)get_wiz_vector_any(&x.second, i), itemIdx)->value;
				append_wiz_string_builder(builder, get_cstr_wiz_string(value), size_wiz_string(value));

				if (i < size_wiz_vector_any(&x.second) - 1) {
					append_char_wiz_string_builder(builder, '\n');
				}
				free_wiz_string(&number);
			}
			else {
				wiz_vector_item_type temp;
				if (0 == strcmp(get_cstr_wiz_string(&itemName), "_")) {
					free_wiz_string(&itemName);
					init_wiz_string(&itemName, "", 0);
				}
				temp = get_item_in_user_type((user_type*)get_wiz_vector_any(&x.second, i), &itemName);
				if (!empty_wiz_vector_item_type(&temp)) {
					for (j = 0; j < size_wiz_vector_item_type(&temp); ++j) {
						item_type* item = get_wiz_vector_item_type(&temp, j);
						append_wiz_string_builder(builder, get_cstr_wiz_string(&item->value), size_wiz_string(&item->value));

						if (j < size_wiz_vector_item_type(&temp) - 1) {
							append_char_wiz_string_builder(builder, ' ');
						}
					}
					if (i < size_wiz_vector_any(&x.second) - 1) {
						append_char_wiz_string_builder(builder, '\n');
					}
				}
				free_wiz_vector_item_type(&temp);
			}
			free_wiz_string(&itemName);
			free_wiz_string(&it);
		}

		free_wiz_vector_any(&x.second);
	}
	init_wiz_string(&result, str_wiz_string_builder(builder, NULL), size_wiz_string_builder(builder));
	return result;
}
 int Exist(user_type* ut, wiz_string* dir, wiz_string_builder* builder)
{
	pair_int_and_wiz_vector_any x = find_user_type_in_user_type(ut, dir, builder);
	int val = x.first;
	
	if (x.first) {
		free_wiz_vector_any(&x.second);
	}
	
	return val;
}
// to do - rename!
pair_wiz_string_and_wiz_string Find2(user_type* ut,  wiz_string* str)
{
	int idx = -1;
	int i;
	pair_wiz_string_and_wiz_string result;

	for (i = size_wiz_string(str) - 1; i >= 0; --i) {
		if ('/' == get_cstr_wiz_string(str)[i]) {
			idx = i;
			break;
		}
	}

	result.first = substr_wiz_string(str, 0, idx + 1);
	result.second = substr_wiz_string(str, idx + 1, size_wiz_string(str));
	
	return result;
}

 wiz_string FindParameters(wiz_map_wiz_string_and_wiz_string* parameters,  wiz_string* operand)
{
	 wiz_string parameter_text;
	 pair_wiz_string_and_wiz_string data;
	 wiz_string value;


	 init_wiz_string(&parameter_text, "$parameter.", 11);
	 if (starts_with_wiz_string(operand, &parameter_text)) {
		 data.first = substr_wiz_string(operand, 11, size_wiz_string(operand));
		 if (get_wiz_map_wiz_string_and_wiz_string(parameters, &data))
		 {
			 value = make_wiz_string_from_other_wiz_string(&data.second);
		 }
		 else {
			 value = make_empty_wiz_string();
		 }
		 free_wiz_string(&data.first);
	}
	 else {
		 value = make_empty_wiz_string();
	 }
	free_wiz_string(&parameter_text);

	return value;
}
 wiz_string FindLocals(wiz_map_wiz_string_and_wiz_string* locals,  wiz_string* operand)
{
	wiz_string local_text;
	
	init_wiz_string(&local_text, "$local.", 7);

	if (starts_with_wiz_string(operand, &local_text)) 
	{
		pair_wiz_string_and_wiz_string data;
		data.first = substr_wiz_string(operand, 7, size_wiz_string(operand));

		if (0 == get_wiz_map_wiz_string_and_wiz_string(locals, &data))
		{
			free_wiz_string(&local_text);
			free_wiz_string(&data.first);

			return make_empty_wiz_string();
		}

		free_wiz_string(&local_text);
		free_wiz_string(&data.first);
		return make_wiz_string_from_other_wiz_string(&data.second);
	}
	free_wiz_string(&local_text);
	return make_empty_wiz_string();
}
//need to renewal. add $AND $OR $NOT

////////////////////////////public//////////////////////////////////

// todo - error chk!
user_type load_data_from_file_in_load_data(wiz_string* fileName)
{
	user_type global;
	wiz_array_queue_token aq;
	// getline remake?
	size_t line_max = 10000; // line_max = 1 is very slow? - solved!
	size_t num = 102400;
	wiz_vector_wiz_string vec_of_str;
	wiz_string_builder builder;
	wiz_string_builder temp_builder;
	FILE* file = fopen(get_cstr_wiz_string(fileName), "rt");
	int real_count;
	int find_idx; // find \n
	int i;
	int size;
	char* builder_cstr;
	wiz_string temp;
	int temp2;
	char* temp3;
	wiz_string temp4;
	int chk = 1;
	int error = 0;


	if (NULL == file) {
		wiz_string name = make_wiz_string_from_cstr("FILE_OPEN_ERROR");
		init_in_user_type(&global, &name);
		free_wiz_string(&name);
		return global;
	 }

	init_wiz_string(&temp4, "\n", 1);

	init_wiz_vector_wiz_string(&vec_of_str, 1024);
	init_wiz_string_builder(&builder, num * 10, "", 0);

	i = 0;
	temp2 = -1;

	while (1) {
		if (chk) {
			init_wiz_string_builder(&temp_builder, num, "", 0);
			real_count = fread((void*)str_wiz_string_builder(&temp_builder, NULL), sizeof(char), num, file);
			temp_builder.len = real_count;
			temp_builder.buffer[real_count] = '\0';


			append_wiz_string_builder(&builder, str_wiz_string_builder(&temp_builder, NULL), size_wiz_string_builder(&temp_builder));

			free_wiz_string_builder(&temp_builder);
		}
		builder_cstr = str_wiz_string_builder(&builder, &size);
		//printf("chk %d %d\n", strlen(builder_cstr), size);

		find_idx = -1;
		for (; i < line_max; ++i) {
			temp2 = find(builder_cstr, '\n', temp2, size);
			if (temp2 != -1) {
				find_idx = temp2;
			}
			else {
				chk = 1;
				break;
			}
		}
		if (i == line_max || real_count != num) {
			if (find_idx != -1) {
				divide_wiz_string_builder(&builder, find_idx);

				temp3 = str_wiz_string_builder(&builder, NULL);

				//	printf("\n%d %d\n", strlen(temp3), find_idx);

				init_wiz_string(&temp, temp3, find_idx);

				concat_and_assign_wiz_string(&temp, &temp4);

				push_back_wiz_vector_wiz_string(&vec_of_str, &temp);

				left_shift_wiz_string_builder(&builder, find_idx + 1);

				//free_wiz_string(&temp); //

				i = 0;
				temp2 = -1;
				chk = 0;
			}
		}
		else {
			continue;
		}

		if (real_count != num) {
			temp3 = str_wiz_string_builder(&builder, &size);
			init_wiz_string(&temp, temp3, size);
			push_back_wiz_vector_wiz_string(&vec_of_str, &temp);
			break;
		}
	}



	//free_wiz_string(&temp);
	free_wiz_string_builder(&builder);

	fclose(file);




	init_wiz_array_queue_token(&aq);

	{
		wiz_vector_wiz_string aqTemp = vec_of_str;
		size_t left = 0, right = size_wiz_vector_wiz_string(&vec_of_str) - 1;
		size_t x;

		for (x = left; x <= right; ++x)
		{
			//wiz_string_tokenizer tokenizer(std( (*aqTemp)[x] ) );
			//while (has_more_tokens_wiz_string_tokenizer(&tokenizer)) {
			//	aq.push(next_token_wiz_string_tokenizer(&tokenizer));
			//}
			wiz_string* statement = get_wiz_vector_wiz_string(&aqTemp, x);
			long long token_first = 0, token_last = 0; // idx of token in statement.
			int state = 0;
			long long i, j;

			for (i = 0; i < size_wiz_string(statement); ++i) {
				if (0 == state && '\"' == get_cstr_wiz_string(statement)[i]) {
					//token_last = i - 1;
					//if (token_last >= 0 && token_last - token_first + 1 > 0) {
					//	aq->emplace_back(statement.substr(token_first, token_last - token_first + 1));
					//}
					state = 1;
					//token_first = i; 
					token_last = i;
				}
				else if (1 == state && '\\' == get_cstr_wiz_string(statement)[i - 1] && '\"' == get_cstr_wiz_string(statement)[i]) {
					token_last = i;
				}
				else if (1 == state && '\"' == get_cstr_wiz_string(statement)[i]) {
					state = 0; token_last = i;

					//aq->emplace_back(statement.substr(token_first, token_last - token_first + 1));
					//token_first = i + 1;
				}

				if (0 == state && '=' == get_cstr_wiz_string(statement)[i]) {
					token_last = i - 1;
					if (token_last >= 0 && token_last - token_first + 1 > 0) {
						token temp;
						temp.isComment = 0;

						temp.str = substr_wiz_string(statement, token_first, token_last + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//free_wiz_string(&temp.str);
					}
					{
						token temp;
						wiz_string str;

						temp.isComment = 0;
						init_wiz_string(&str, "=", 1);
						temp.str = str;

						push_wiz_array_queue_token(&aq, &temp);
						//free_wiz_string(&temp.str);
					}
					token_first = i + 1;
				}
				else if (0 == state && is_whitespace(get_cstr_wiz_string(statement)[i])) { // isspace ' ' \t \r \n , etc... ?
					token_last = i - 1;
					if (token_last >= 0 && token_last - token_first + 1 > 0) {
						token temp;
						temp.isComment = 0;
						temp.str = substr_wiz_string(statement, token_first, token_last + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//free_wiz_string(&temp.str);
					}
					token_first = i + 1;
				}
				else if (0 == state && '{' == get_cstr_wiz_string(statement)[i]) {
					token_last = i - 1;
					if (token_last >= 0 && token_last - token_first + 1 > 0) {
						token temp;
						temp.isComment = 0;
						temp.str = substr_wiz_string(statement, token_first, token_last + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//	free_wiz_string(&temp.str);
					}
					{
						token temp;
						wiz_string str;

						temp.isComment = 0;
						init_wiz_string(&str, "{", 1);
						temp.str = str;

						push_wiz_array_queue_token(&aq, &temp);

						//		free_wiz_string(&temp.str);
					}
					token_first = i + 1;
				}
				else if (0 == state && '}' == get_cstr_wiz_string(statement)[i]) {
					token_last = i - 1;
					if (token_last >= 0 && token_last - token_first + 1 > 0) {
						token temp;
						temp.isComment = 0;
						temp.str = substr_wiz_string(statement, token_first, token_last + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//		free_wiz_string(&temp.str);
					}
					{
						token temp;
						wiz_string str;

						temp.isComment = 0;
						init_wiz_string(&str, "}", 1);
						temp.str = str;

						push_wiz_array_queue_token(&aq, &temp);

						//		free_wiz_string(&temp.str);
					}
					token_first = i + 1;
				}

				if (0 == state && '#' == get_cstr_wiz_string(statement)[i]) { // different from load_data_from_file
					token_last = i - 1;
					if (token_last >= 0 && token_last - token_first + 1 > 0) {
						token temp;
						temp.isComment = 0;
						temp.str = substr_wiz_string(statement, token_first, token_last + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//	free_wiz_string(&temp.str);
					}
					j = 0;
					for (j = i; j < size_wiz_string(statement); ++j) {
						if (get_cstr_wiz_string(statement)[j] == '\n') // cf) '\r' ?
						{
							break;
						}
					}
					--j; // "before enter key" or "before end"

					if (j - i + 1 > 0) {
						token temp;
						temp.isComment = 1;
						temp.str = substr_wiz_string(statement, i, j + 1);

						push_wiz_array_queue_token(&aq, &temp);

						//	free_wiz_string(&temp.str);
					}
					token_first = j + 2;
					i = token_first - 1;
				}
			}

			if (token_first < size_wiz_string(statement))
			{
				token temp;
				temp.isComment = 0;
				temp.str = substr_wiz_string(statement, token_first, size_wiz_string(statement));

				push_wiz_array_queue_token(&aq, &temp);
			}

			free_wiz_string(statement);
		}
	}

	{
		size_t i;

		for (i = 0; i < size_wiz_vector_wiz_string(&vec_of_str); ++i) {
			free_wiz_string(&(vec_of_str.vec[i]));
		}
		free_wiz_vector_wiz_string(&vec_of_str);
	}


	{
		wiz_string LEFT, RIGHT, EQ_STR, EMPTY;
		int state = 0;
		int braceNum = 0;
		long long state_reserve = 0;
		wiz_vector_any nestedUT;
		wiz_string var1, var2, val;

		int varOn = 0;

		init_wiz_string(&EMPTY, "", 0);

		init_in_user_type(&global, &EMPTY);
		init_wiz_vector_any(&nestedUT, 1);
		init_wiz_string(&var1, "", 0);
		init_wiz_string(&var2, "", 0);
		init_wiz_string(&val, "", 0);

		init_wiz_string(&LEFT, "{", 1);
		init_wiz_string(&RIGHT, "}", 1);
		init_wiz_string(&EQ_STR, "=", 1);


		push_back_wiz_vector_any(&nestedUT, (void*)&global);

		while (0 == empty_wiz_array_queue_token(&aq)) {
			//printf("test %d %s\n", state, get_cstr_wiz_string(Top(get_wiz_vector_any(&nestedUT, braceNum), &aq)));

			switch (state)
			{
			case 0:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					state = 2;
				}
				else {
					pair_int_and_token bsPair = LookUp(get_wiz_vector_any(&nestedUT, braceNum), &aq);

					if (bsPair.first) {
						if (equal(&EQ_STR, &bsPair.second.str)) {
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var2);
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
							state = 2;
						}
						else {
							if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
								add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
								state = 0;
							}
						}
					}
					else {
						if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
							add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
							state = 0;
						}
					}
				}
				break;
			case 1:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					state = 0;
				}
				else {
					// syntax error.
					//rror = 1;
				}
				break;
			case 2:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					user_type ut_temp;
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					init_in_user_type(&ut_temp, &var2);
					add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &ut_temp);
					free_user_type_in_user_type(&ut_temp);

					user_type* pTemp;
					get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &pTemp);

					braceNum++;

					/// new nestedUT
					if (size_wiz_vector_any(&nestedUT) == braceNum) { /// changed 2014.01.23..
						push_back_wiz_vector_any(&nestedUT, NULL);
					}

					/// initial new nestedUT.
					set_wiz_vector_any(&nestedUT, braceNum, (void*)pTemp);
					///
					state = 3;
				}
				else {
					if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &val)) {
						add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &val);

						assign_wiz_string(&var2, &EMPTY);
						assign_wiz_string(&val, &EMPTY);

						state = 0;
					}
				}
				break;
			case 3:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;

					state = 0;
				}
				else {
					{
						/// uisng struct
						state_reserve++;
						state = 4;
					}
					//else
					{
						//	throw  "syntax error 2 ";
					}
				}
				break;
			case 4:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					user_type temp;
					init_in_user_type(&temp, &EMPTY);

					add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &temp);
					free_user_type_in_user_type(&temp);
					user_type* pTemp;
					get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &pTemp);

					braceNum++;

					/// new nestedUT
					if (size_wiz_vector_any(&nestedUT) == braceNum) { /// changed 2014.01.23..
						push_back_wiz_vector_any(&nestedUT, NULL);
					}

					/// initial new nestedUT.
					set_wiz_vector_any(&nestedUT, braceNum, pTemp);
					///
					//}

					state = 5;
				}
				else if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					state = is_state0(state_reserve) ? 0 : 4;
					state_reserve--;

					{
						set_wiz_vector_any(&nestedUT, braceNum, NULL);
						braceNum--;
					}
				}
				else {
					pair_int_and_token bsPair = LookUp(get_wiz_vector_any(&nestedUT, braceNum), &aq);
					if (bsPair.first) {
						if (equal(&EQ_STR, &bsPair.second.str)) {
							// var2
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var2);
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL); // pass EQ_STR
							state = 6;
						}
						else {
							// var1
							if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
								add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
								assign_wiz_string(&var1, &EMPTY);

								state = 4;
							}
						}
					}
					else
					{
						// var1
						if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1))
						{
							add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
							assign_wiz_string(&var1, &EMPTY);

							state = 4;
						}
					}
				}
				break;
			case 5:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					//if (flag1 == 0) {
					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;
					// }
					//
					state = 4;
				}

				else {
					int idx = -1;
					int num = -1;


					{
						/// uisng struct
						state_reserve++;
						state = 4;
					}
					//else
					{
						//	throw "syntax error 4  ";
					}
				}
				break;
			case 6:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					///
					{
						user_type ut_temp;
						init_in_user_type(&ut_temp, &var2);
						add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &ut_temp);
						free_user_type_in_user_type(&ut_temp);
						user_type* pTemp;
						get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &pTemp);
						assign_wiz_string(&var2, &EMPTY);
						braceNum++;

						/// new nestedUT
						if (size_wiz_vector_any(&nestedUT) == braceNum) {/// changed 2014.01.23..
							push_back_wiz_vector_any(&nestedUT, NULL);
						}

						/// initial new nestedUT.
						set_wiz_vector_any(&nestedUT, braceNum, pTemp);
					}
					///
					state = 7;
				}
				else {
					if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &val)) {
						add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &val);
						assign_wiz_string(&var2, &EMPTY);
						assign_wiz_string(&val, &EMPTY);

						if (empty_wiz_array_queue_token(&aq))
						{
							//
						}
						else if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

							{
								state = is_state0(state_reserve) ? 0 : 4;
								state_reserve--;

								{
									set_wiz_vector_any(&nestedUT, braceNum, NULL);
									braceNum--;
								}
							}
							{
								//state = 4;
							}
						}
						else {
							state = 4;
						}
					}
				}
				break;
			case 7:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					//

					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;
					//
					state = 4;
				}
				else {
					int idx = -1;
					int num = -1;

					{
						/// uisng struct
						state_reserve++;

						state = 4;
					}
					//else
					{
						//throw "syntax error 5 ";
					}
				}
				break;
			}
		}
		free_wiz_vector_any(&nestedUT);
		free_wiz_string(&var1);
		free_wiz_string(&var2);
		free_wiz_string(&val);

		free_wiz_string(&LEFT);
		free_wiz_string(&RIGHT);
		free_wiz_string(&EQ_STR);
		free_wiz_string(&EMPTY);

	//	free_user_type_in_user_type(&global);
	}

	{
		free_wiz_array_queue_token(&aq);
	}


	return global;
}

user_type load_data_from_string_in_load_data(wiz_string* str) // , int error? = 0
{
	user_type global;
	wiz_array_queue_token aq;
	int chk = 1;
	int error = 0;

	wiz_string statement = make_wiz_string_from_other_wiz_string(str);
	long long token_first = 0, token_last = 0; // idx of token in statement.
	int state = 0;
	long long i, j;

	init_wiz_array_queue_token(&aq);


	for (i = 0; i < size_wiz_string(&statement); ++i) {
		if (0 == state && '\"' == get_cstr_wiz_string(&statement)[i]) {
			//token_last = i - 1;
			//if (token_last >= 0 && token_last - token_first + 1 > 0) {
			//	aq->emplace_back(statement.substr(token_first, token_last - token_first + 1));
			//}
			state = 1;
			//token_first = i; 
			token_last = i;
		}
		else if (1 == state && '\\' == get_cstr_wiz_string(&statement)[i - 1] && '\"' == get_cstr_wiz_string(&statement)[i]) {
			token_last = i;
		}
		else if (1 == state && '\"' == get_cstr_wiz_string(&statement)[i]) {
			state = 0; token_last = i;

			//aq->emplace_back(statement.substr(token_first, token_last - token_first + 1));
			//token_first = i + 1;
		}

		if (0 == state && '=' == get_cstr_wiz_string(&statement)[i]) {
			token_last = i - 1;
			if (token_last >= 0 && token_last - token_first + 1 > 0) {
				token temp;
				temp.isComment = 0;

				temp.str = substr_wiz_string(&statement, token_first, token_last + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//free_wiz_string(&temp.str);
			}
			{
				token temp;
				wiz_string str;

				temp.isComment = 0;
				init_wiz_string(&str, "=", 1);
				temp.str = str;

				push_wiz_array_queue_token(&aq, &temp);
				//free_wiz_string(&temp.str);
			}
			token_first = i + 1;
		}
		else if (0 == state && is_whitespace(get_cstr_wiz_string(&statement)[i])) { // isspace ' ' \t \r \n , etc... ?
			token_last = i - 1;
			if (token_last >= 0 && token_last - token_first + 1 > 0) {
				token temp;
				temp.isComment = 0;
				temp.str = substr_wiz_string(&statement, token_first, token_last + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//free_wiz_string(&temp.str);
			}
			token_first = i + 1;
		}
		else if (0 == state && '{' == get_cstr_wiz_string(&statement)[i]) {
			token_last = i - 1;
			if (token_last >= 0 && token_last - token_first + 1 > 0) {
				token temp;
				temp.isComment = 0;
				temp.str = substr_wiz_string(&statement, token_first, token_last + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//	free_wiz_string(&temp.str);
			}
			{
				token temp;
				wiz_string str;

				temp.isComment = 0;
				init_wiz_string(&str, "{", 1);
				temp.str = str;

				push_wiz_array_queue_token(&aq, &temp);

				//		free_wiz_string(&temp.str);
			}
			token_first = i + 1;
		}
		else if (0 == state && '}' == get_cstr_wiz_string(&statement)[i]) {
			token_last = i - 1;
			if (token_last >= 0 && token_last - token_first + 1 > 0) {
				token temp;
				temp.isComment = 0;
				temp.str = substr_wiz_string(&statement, token_first, token_last + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//		free_wiz_string(&temp.str);
			}
			{
				token temp;
				wiz_string str;

				temp.isComment = 0;
				init_wiz_string(&str, "}", 1);
				temp.str = str;

				push_wiz_array_queue_token(&aq, &temp);

				//		free_wiz_string(&temp.str);
			}
			token_first = i + 1;
		}

		if (0 == state && '#' == get_cstr_wiz_string(&statement)[i]) { // different from load_data_from_file
			token_last = i - 1;
			if (token_last >= 0 && token_last - token_first + 1 > 0) {
				token temp;
				temp.isComment = 0;
				temp.str = substr_wiz_string(&statement, token_first, token_last + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//	free_wiz_string(&temp.str);
			}
			j = 0;
			for (j = i; j < size_wiz_string(&statement); ++j) {
				if (get_cstr_wiz_string(&statement)[j] == '\n') // cf) '\r' ?
				{
					break;
				}
			}
			--j; // "before enter key" or "before end"

			if (j - i + 1 > 0) {
				token temp;
				temp.isComment = 1;
				temp.str = substr_wiz_string(&statement, i, j + 1);

				push_wiz_array_queue_token(&aq, &temp);

				//	free_wiz_string(&temp.str);
			}
			token_first = j + 2;
			i = token_first - 1;
		}
	}

	if (token_first < size_wiz_string(&statement))
	{
		token temp;
		temp.isComment = 0;
		temp.str = substr_wiz_string(&statement, token_first, size_wiz_string(&statement));

		push_wiz_array_queue_token(&aq, &temp);
	}

	free_wiz_string(&statement);

	{
		wiz_string LEFT, RIGHT, EQ_STR, EMPTY;
		int state = 0;
		int braceNum = 0;
		long long state_reserve = 0;
		wiz_vector_any nestedUT;
		wiz_string var1, var2, val;

		int varOn = 0;

		init_wiz_string(&EMPTY, "", 0);

		init_in_user_type(&global, &EMPTY);
		init_wiz_vector_any(&nestedUT, 1);
		init_wiz_string(&var1, "", 0);
		init_wiz_string(&var2, "", 0);
		init_wiz_string(&val, "", 0);

		init_wiz_string(&LEFT, "{", 1);
		init_wiz_string(&RIGHT, "}", 1);
		init_wiz_string(&EQ_STR, "=", 1);


		push_back_wiz_vector_any(&nestedUT, (void*)&global);

		while (0 == empty_wiz_array_queue_token(&aq)) {
			//printf("test %d %s\n", state, get_cstr_wiz_string(Top(get_wiz_vector_any(&nestedUT, braceNum), &aq)));

			switch (state)
			{
			case 0:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					state = 2;
				}
				else {
					pair_int_and_token bsPair = LookUp(get_wiz_vector_any(&nestedUT, braceNum), &aq);

					if (bsPair.first) {
						if (equal(&EQ_STR, &bsPair.second.str)) {
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var2);
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
							state = 2;
						}
						else {
							if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
								add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
								var1 = EMPTY;
								state = 0;
							}
						}
					}
					else {
						if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
							add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
							var1 = EMPTY;
							state = 0;
						}
					}
				}
				break;
			case 1:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					state = 0;
				}
				else {
					// syntax error.
					//rror = 1;
				}
				break;
			case 2:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					user_type ut_temp;
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					init_in_user_type(&ut_temp, &var2);
					add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &ut_temp);
					free_user_type_in_user_type(&ut_temp);
					user_type* pTemp;
					get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &pTemp);

					braceNum++;

					/// new nestedUT
					if (size_wiz_vector_any(&nestedUT) == braceNum) { /// changed 2014.01.23..
						push_back_wiz_vector_any(&nestedUT, NULL);
					}

					/// initial new nestedUT.
					set_wiz_vector_any(&nestedUT, braceNum, (void*)pTemp);
					///
					state = 3;
				}
				else {
					if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &val)) {
						add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &val);

						var2 = EMPTY;
						val = EMPTY;

						state = 0;
					}
				}
				break;
			case 3:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;

					state = 0;
				}
				else {
					{
						/// uisng struct
						state_reserve++;
						state = 4;
					}
					//else
					{
						//	throw  "syntax error 2 ";
					}
				}
				break;
			case 4:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					user_type temp;
					init_in_user_type(&temp, &EMPTY);

					add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &temp);
					free_user_type_in_user_type(&temp);
					user_type* pTemp;
					get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &pTemp);

					braceNum++;

					/// new nestedUT
					if (size_wiz_vector_any(&nestedUT) == braceNum) { /// changed 2014.01.23..
						push_back_wiz_vector_any(&nestedUT, NULL);
					}

					/// initial new nestedUT.
					set_wiz_vector_any(&nestedUT, braceNum, pTemp);
					///
					//}

					state = 5;
				}
				else if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					state = is_state0(state_reserve) ? 0 : 4;
					state_reserve--;

					{
						set_wiz_vector_any(&nestedUT, braceNum, NULL);
						braceNum--;
					}
				}
				else {
					pair_int_and_token bsPair = LookUp(get_wiz_vector_any(&nestedUT, braceNum), &aq);
					if (bsPair.first) {
						if (equal(&EQ_STR, &bsPair.second.str)) {
							// var2
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var2);
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL); // pass EQ_STR
							state = 6;
						}
						else {
							// var1
							if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1)) {
								add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
								var1 = EMPTY;

								state = 4;
							}
						}
					}
					else
					{
						// var1
						if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &var1))
						{
							add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &EMPTY, &var1);
							var1 = EMPTY;

							state = 4;
						}
					}
				}
				break;
			case 5:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					//if (flag1 == 0) {
					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;
					// }
					//
					state = 4;
				}

				else {
					int idx = -1;
					int num = -1;


					{
						/// uisng struct
						state_reserve++;
						state = 4;
					}
					//else
					{
						//	throw "syntax error 4  ";
					}
				}
				break;
			case 6:
				if (equal(&LEFT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

					///
					{
						user_type ut_temp;
						init_in_user_type(&ut_temp, &var2);
						add_user_type_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &ut_temp);
						free_user_type_in_user_type(&ut_temp);
						user_type* pTemp;
						get_last_user_type_item_ref_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &pTemp);
						assign_wiz_string(&var2, &EMPTY);
						braceNum++;

						/// new nestedUT
						if (size_wiz_vector_any(&nestedUT) == braceNum) {/// changed 2014.01.23..
							push_back_wiz_vector_any(&nestedUT, NULL);
						}

						/// initial new nestedUT.
						set_wiz_vector_any(&nestedUT, braceNum, pTemp);
					}
					///
					state = 7;
				}
				else {
					if (Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, &val)) {
						add_item_in_user_type((user_type*)get_wiz_vector_any(&nestedUT, braceNum), &var2, &val);
						var2 = EMPTY;
						val = EMPTY;

						if (empty_wiz_array_queue_token(&aq))
						{
							//
						}
						else if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
							Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);

							{
								state = is_state0(state_reserve) ? 0 : 4;
								state_reserve--;

								{
									set_wiz_vector_any(&nestedUT, braceNum, NULL);
									braceNum--;
								}
							}
							{
								//state = 4;
							}
						}
						else {
							state = 4;
						}
					}
				}
				break;
			case 7:
				if (equal(&RIGHT, Top(get_wiz_vector_any(&nestedUT, braceNum), &aq))) {
					Pop(get_wiz_vector_any(&nestedUT, braceNum), &aq, NULL);
					//

					set_wiz_vector_any(&nestedUT, braceNum, NULL);
					braceNum--;
					//
					state = 4;
				}
				else {
					int idx = -1;
					int num = -1;

					{
						/// uisng struct
						state_reserve++;

						state = 4;
					}
					//else
					{
						//throw "syntax error 5 ";
					}
				}
				break;
			}
		}
		free_wiz_vector_any(&nestedUT);
		free_wiz_string(&var1);
		free_wiz_string(&var2);
		free_wiz_string(&val);

		free_wiz_string(&LEFT);
		free_wiz_string(&RIGHT);
		free_wiz_string(&EQ_STR);
		free_wiz_string(&EMPTY);

		//	free_user_type_in_user_type(&global);
	}

	{
		free_wiz_array_queue_token(&aq);
	}

	return global;
}


int save_data_in_load_data(wiz_string* fileName, user_type* global, int option)
{
	FILE* file = fopen(get_cstr_wiz_string(fileName), "wt");
	if (NULL == file) { return 0; }

	if (1 == option) {
		save1_in_user_type(file, global, 0);
	}
	else if (2 == option) {
		save2_in_user_type(file, global, 0);
	}

	fclose(file);

	return 1;
}



int add_data_in_load_data(user_type* global, wiz_string* position, wiz_string* data, wiz_string* cond_str, excute_data* excuteData, wiz_string_builder* builder) {
	user_type utTemp;
	int is1 = 0;
	pair_int_and_wiz_vector_any finded;
	size_t i, k;

	utTemp = load_data_from_string_in_load_data(data);

	finded = find_user_type_in_user_type(global, position, builder);
	if (finded.first) {
		for (i = 0; i < size_wiz_vector_any(&finded.second); ++i) {
			int item_n = 0;
			int user_n = 0;

			if (size_wiz_string(cond_str) == 0) {
				wiz_string* _cond = cond_str;
				condition cond;
				
				// _cond = ToBool4(get_wiz_vector_any(&finded.second, i), global, _cond, excuteData, builder);

				init_in_condition(&cond, _cond, (user_type*)get_wiz_vector_any(&finded.second, i), global, builder);

				while (next_in_condition(&cond));
				
				if (size_wiz_string(get_wiz_stack_wiz_string(now_in_condition(&cond), 0)) != 1 || 0 != strcmp("TRUE", get_cstr_wiz_string(get_wiz_stack_wiz_string(now_in_condition(&cond), 0)))) // || cond.Now().size()  != 1
				{
					// free all cond data
					clear_now_condition(&cond);
					free_in_condition(&cond);
					continue;
				}
				// free all cond data?
				clear_now_condition(&cond);
				free_in_condition(&cond);
			}

			for (k = 0; k < get_ilist_size_in_user_type(&utTemp); ++k) {
				if (is_item_list_in_user_type(&utTemp, k)) {
					wiz_string name = make_wiz_string_from_other_wiz_string(&get_item_list_in_user_type(&utTemp, item_n)->name);
					wiz_string value = make_wiz_string_from_other_wiz_string(&get_item_list_in_user_type(&utTemp, item_n)->value);
					add_item_in_user_type(get_wiz_vector_any(&finded.second, i), &name, &value);
					item_n++;
				}
				else {
					add_user_type_item_in_user_type(get_wiz_vector_any(&finded.second, i), get_user_type_list_in_user_type(&utTemp, user_n));
					user_n++;
				}
			}
			is1 = 1;
		}
		
		free_wiz_vector_any(&finded.second);
	}
	else {
		is1 = 0;
	}

	free_user_type_in_user_type(&utTemp);
	return is1;
}
