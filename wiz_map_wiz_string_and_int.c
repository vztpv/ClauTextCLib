

#include "wiz_map_wiz_string_and_int.h"

#define FORM(A, B) A##B

struct FORM(binary_node_, wiz_string_and_int)
{
	pair_wiz_string_and_int val;
	struct FORM(binary_node_, wiz_string_and_int)* left;
	struct FORM(binary_node_, wiz_string_and_int)* right;
};

typedef struct FORM(binary_node_, wiz_string_and_int) FORM(binary_node_, wiz_string_and_int);


void init_binary_node_wiz_string_and_int(FORM(binary_node_, wiz_string_and_int)* node)
{
	node->left = NULL;
	node->right = NULL;
}

void remove_all_wiz_string_and_int(FORM(binary_node_, wiz_string_and_int)* node, int option)
{
	FORM(binary_node_, wiz_string_and_int)* left;
	FORM(binary_node_, wiz_string_and_int)* right;
	if (NULL == node) {
		return;
	}

	left = node->left;
	right = node->right;

	if (1 == option) {
		free_wiz_string(&node->val.first);
	}

	free(node);

	remove_all_wiz_string_and_int(left, option);
	remove_all_wiz_string_and_int(right, option);
}

void _inorder_wiz_string_and_int(FORM(binary_node_, wiz_string_and_int)* node, pair_wiz_string_and_int arr[], size_t* count)
{
	if (NULL == node) { return; }

	_inorder_wiz_string_and_int(node->left, arr, count);

	arr[*count] = node->val;
	++(*count);

	_inorder_wiz_string_and_int(node->right, arr, count);
}

void FORM(inorder_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int arr[])
{
	size_t count = 0;

	_inorder_wiz_string_and_int(_map->root, arr, &count);
}

FORM(binary_node_, wiz_string_and_int)* _balancing_string_and_int(pair_wiz_string_and_int arr[], int start, int last)
{
	FORM(binary_node_, wiz_string_and_int)* temp = NULL;
	size_t middle = (start + last) / 2;
	if (start > last) { return NULL; }

	temp = malloc(sizeof(FORM(binary_node_, wiz_string_and_int)) * 1);
	temp->val = arr[middle];

	temp->left = _balancing_string_and_int(arr, start, middle - 1);
	temp->right = _balancing_string_and_int(arr, middle + 1, last);

	return temp;
}

void FORM(init_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map)
{
	_map->root = NULL;
	_map->count = 0;
}
void FORM(free_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, int option)
{
	if (NULL != _map->root) {
		remove_all_wiz_string_and_int(_map->root, option);
		_map->root = NULL;
		_map->count = 0;
	}
}

void FORM(balancing_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map)
{
	size_t count = 0;
	pair_wiz_string_and_int* arr;

	arr = malloc(sizeof(pair_wiz_string_and_int) * _map->count);

	_inorder_wiz_string_and_int(_map->root, arr, &count);

	FORM(free_wiz_map_, wiz_string_and_int)(_map, 0);

	_map->root = _balancing_string_and_int(arr, 0, count - 1);
	_map->count = count;
	free(arr);
}

int FORM(insert_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map,
	pair_wiz_string_and_int* val, int option) // optino, 0 : nothing, 1 : insert and balancing!
{
	FORM(binary_node_, wiz_string_and_int)* temp = _map->root;
	FORM(binary_node_, wiz_string_and_int)* temp2 = temp;

	if (is_exist_wiz_map_wiz_string_and_int(_map, val)) {
		return 0;
	}

	if (NULL == _map->root)
	{
		_map->root = malloc(sizeof(FORM(binary_node_, wiz_string_and_int)) * 1);
		_map->root->val = *val;
		_map->root->left = NULL;
		_map->root->right = NULL;
		_map->count = 1;
	}
	else
	{
		while (NULL != temp) {
			if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) < 0) {
				temp2 = temp;
				temp = temp->right;
			}
			else if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) > 0) {
				temp2 = temp;
				temp = temp->left;
			}
		}
		if (strcmp(get_cstr_wiz_string(&(temp2->val.first)), get_cstr_wiz_string(&(val->first))) < 0) {
			temp2->right = malloc(sizeof(FORM(binary_node_, wiz_string_and_int)) * 1);
			temp2->right->val = *val;
			temp2->right->left = NULL;
			temp2->right->right = NULL;
		}
		else if (strcmp(get_cstr_wiz_string(&(temp2->val.first)), get_cstr_wiz_string(&(val->first))) > 0) {
			temp2->left = malloc(sizeof(FORM(binary_node_, wiz_string_and_int)) * 1);
			temp2->left->val = *val;
			temp2->left->left = NULL;
			temp2->left->right = NULL;
		}
		_map->count++;
	}

	if (1 == option)
	{
		FORM(balancing_wiz_map_, wiz_string_and_int)(_map);
	}

	return 1;
}


int FORM(get_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int* val)
{
	FORM(binary_node_, wiz_string_and_int)* temp = _map->root;

	if (NULL == _map->root) {
		return 0;
	}

	while (NULL != temp) {
		if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) < 0) {
			temp = temp->right;
		}
		else if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) > 0) {
			temp = temp->left;
		}
		else {
			val->second = temp->val.second;
			return 1;
		}
	}

	return 0;
}


int FORM(is_exist_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, pair_wiz_string_and_int* val)
{
	FORM(binary_node_, wiz_string_and_int)* temp = _map->root;

	if (NULL == _map->root) {
		return 0;
	}

	while (NULL != temp) {
		if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) < 0) {
			temp = temp->right;
		}
		else if (strcmp(get_cstr_wiz_string(&(temp->val.first)), get_cstr_wiz_string(&(val->first))) > 0) {
			temp = temp->left;
		}
		else {
			return 1;
		}
	}

	return 0;
}

int FORM(empty_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map)
{
	return 0 == _map->count;
}

void FORM(clear_wiz_map_, wiz_string_and_int)(FORM(wiz_map_, wiz_string_and_int)* _map, int option) 
{
	free_wiz_map_wiz_string_and_int(_map, option);
	init_wiz_map_wiz_string_and_int(_map);
}

