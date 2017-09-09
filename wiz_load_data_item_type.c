
#include "wiz_load_data_item_type.h"

void init_item_value_in_item_type(item_type* item, const char* name, size_t name_len, const char* value, size_t value_len)
{
	init_wiz_string(&(item->name), name, name_len);
	init_wiz_string(&(item->value), value, value_len);
}
void free_item_value_in_item_type(item_type* item)
{
	free_wiz_string(&(item->name));
	free_wiz_string(&(item->value));
}

wiz_string* get_name_in_item_type(item_type* item)
{
	return &(item->name);
}
wiz_string* get_value_in_item_type(item_type* item)
{
	return &(item->value);
}
