
#ifndef WIZ_MAP_WIZ_STRING_AND_WIZ_STRING_H
#define WIZ_MAP_WIZ_STRING_AND_WIZ_STRING_H

#include "wiz_string.h"
#include "pair.h"

#define FORM(A, B) A##B

struct FORM(binary_node_, wiz_string_and_wiz_string);

struct FORM(wiz_map_, wiz_string_and_wiz_string)
{
	struct FORM(binary_node_, wiz_string_and_wiz_string)* root;
	size_t count;
};

typedef struct FORM(wiz_map_, wiz_string_and_wiz_string) FORM(wiz_map_, wiz_string_and_wiz_string);


void FORM(init_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map);
void FORM(free_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map);
void FORM(free_all_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map);

void FORM(balancing_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map);

int FORM(insert_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map,
	pair_wiz_string_and_wiz_string* val, int option); // optino, 0 : nothing, 1 : insert and balancing!

int FORM(get_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map, pair_wiz_string_and_wiz_string* val);

int FORM(set_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map, pair_wiz_string_and_wiz_string* val, int option);
//if option == 1 then remove before data.
//if option == 0 then no remove before data.

int FORM(is_exist_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map, pair_wiz_string_and_wiz_string* val);
int FORM(empty_wiz_map_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map);
 
void FORM(inorder_, wiz_string_and_wiz_string)(FORM(wiz_map_, wiz_string_and_wiz_string)* _map, pair_wiz_string_and_wiz_string arr[]);

#endif
