
#ifndef WIZ_LOAD_DATA_CONDITION_H
#define WIZ_LOAD_DATA_CONDITION_H

#include <stdlib.h>
#include "wiz_vector_wiz_string.h"
#include "wiz_stack_wiz_string.h"
#include "wiz_load_data_user_type.h"
#include "wiz_string_builder.h"
#include "wiz_string_tokenizer.h"

struct condition {
	int braceNum;
	wiz_vector_wiz_string token_vec; 
	wiz_stack_wiz_string token_stack; // chk
	wiz_string cond;
	size_t i;
	user_type* position; // need set, get ter!!
	user_type* global;
	wiz_string_builder* builder;
};

typedef struct condition condition;

void init_in_condition(condition* cond, wiz_string* cond_str, user_type* position, user_type* global, wiz_string_builder* builder);
void free_in_condition(condition* cond);
int next_in_condition(condition* cond);
wiz_stack_wiz_string* now_in_condition(condition* cond);


#endif

