
#ifndef WIZ_LOAD_DATA_ITEM_TYPE
#define WIZ_LOAD_DATA_ITEM_TYPE

#include <stdlib.h>
#include "wiz_string.h"

struct item_type
{
	wiz_string name;
	wiz_string value;
	
	// int inited; // remove?
};

typedef struct item_type item_type;

void init_item_value_in_item_type(item_type* item, const char* name, size_t name_len, const char* value, size_t value_len);
void free_item_value_in_item_type(item_type* item);

wiz_string* get_name_in_item_type(item_type* item);
wiz_string* get_value_in_item_type(item_type* item);

#endif
