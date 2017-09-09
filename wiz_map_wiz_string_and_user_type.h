

#ifndef WIZ_MAP_WIZ_STRING_AND_USER_TYPE_H
#define WIZ_MAP_WIZ_STRING_AND_USER_TYPE_H

#include "wiz_string.h"
#include "pair.h"

#define FORM(A, B) A##B

struct FORM(binary_node_, wiz_string_and_user_type);

struct FORM(wiz_map_, wiz_string_and_user_type)
{
	struct FORM(binary_node_, wiz_string_and_user_type)* root;
	size_t count;
};

typedef struct FORM(wiz_map_, wiz_string_and_user_type) FORM(wiz_map_, wiz_string_and_user_type);


void FORM(init_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map);
void FORM(free_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map);
void FORM(free_all_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map);

void FORM(balancing_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map);

int FORM(insert_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map,
	pair_wiz_string_and_user_type* val, int option); // optino, 0 : nothing, 1 : insert and balancing!

int FORM(get_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map, pair_wiz_string_and_user_type* val);


int FORM(is_exist_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map, pair_wiz_string_and_user_type* val);
int FORM(empty_wiz_map_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map);

void FORM(inorder_, wiz_string_and_user_type)(FORM(wiz_map_, wiz_string_and_user_type)* _map, pair_wiz_string_and_user_type arr[]);


#endif
