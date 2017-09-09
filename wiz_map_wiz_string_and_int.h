
#ifndef WIZ_MAP_WIZ_STRING_AND_INT_H
#define WIZ_MAP_WIZ_STRING_AND_INT_H

#include "wiz_string.h"
#include "pair.h"

#define FORM(A, B) A##B

struct FORM(binary_node_, wiz_string_and_int);

struct FORM(wiz_map_, wiz_string_and_int)
{
	struct FORM(binary_node_, wiz_string_and_int)* root;
	size_t count;
};

typedef struct FORM(wiz_map_, wiz_string_and_int) FORM(wiz_map_, wiz_string_and_int);


void FORM(init_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map);
void FORM(free_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, int option);

void FORM(balancing_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map);

int FORM(insert_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map,
	pair_wiz_string_and_int* val, int option); // optino, 0 : nothing, 1 : insert and balancing!

int FORM(get_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int* val);

int FORM(is_exist_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int* val);
int FORM(empty_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map);

void FORM(inorder_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int arr[]);

void FORM(clear_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, int option);


#endif

