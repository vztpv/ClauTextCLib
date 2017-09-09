
#ifndef WIZ_LOAD_DATA_USER_TYPE_H
#define WIZ_LOAD_DATA_USER_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "wiz_string.h"
#include "wiz_vector.h"
#include "wiz_load_data_item_type.h"
#include "wiz_string_builder.h"
#include "pair.h"



	struct user_type {
		wiz_string name;
		struct user_type* parent;
		wiz_vector_wiz_string comment_list;
		wiz_vector_int ilist;
		wiz_vector_item_type item_list;
		wiz_vector_any2 user_type_list;
	};

	typedef struct user_type user_type;

	void push_comment_in_user_type(user_type* ut, wiz_string* comment);
	size_t get_comment_list_size_in_user_type(user_type* ut);
	wiz_string* get_comment_list_in_user_type(user_type* ut, size_t idx);
	size_t get_ilist_size_in_user_type(user_type* ut);
	size_t get_item_list_size_in_user_type(user_type* ut);
	size_t get_user_type_list_size_in_user_type(user_type* ut);
	int get_ilist_in_user_type(user_type* ut, size_t idx);
	void set_ilist_in_user_type(user_type* ut, size_t idx, int val);

	item_type* get_item_list_in_user_type(user_type* ut, size_t idx);
	user_type* get_user_type_list_in_user_type(user_type* ut, size_t idx);

	int is_item_list_in_user_type(user_type* ut, size_t idx);
	int is_user_type_list_in_user_type(user_type* ut, size_t idx);

	//remove? - void add_item_list_in_user_type(user_type* ut, item_type* item);
	user_type* get_parent_in_user_type(user_type* ut);


	void link_user_type_in_user_type(user_type* ut, user_type* ut2);

	void init_in_user_type(user_type* ut, wiz_string* name);
	void init_from_other_user_type_in_user_type(user_type* ut_this, user_type* ut_other);
	void free_user_type_in_user_type(user_type* ut);
	void shallow_free_user_type_in_user_type(user_type* ut);

	//void Reset_in_user_type(user_type* ut, user_type* ut);
	//void _remove_in_user_type(user_type* ut);
	/// val : 1 or 2
	int _get_index_in_user_type(user_type* ut, wiz_vector_int* ilist, int val, size_t start);
	// test? - need more thinking!
	size_t _get_item_index_from_ilist_index_in_user_type(user_type* ut, wiz_vector_int* ilist, size_t ilist_idx);
	size_t _get_user_type_index_from_ilist_index_in_user_type(user_type* ut, wiz_vector_int* ilist, size_t ilist_idx);
	/// type : 1 or 2
	int _get_ilist_index_in_user_type(user_type* ut, wiz_vector_int* ilist, size_t index, int type);
	void remove_item_list_by_idx_in_user_type(user_type* ut, size_t idx);//
	void remove_user_type_list_by_idx_in_user_type(user_type* ut, size_t idx);// chk
	void remove_item_list_by_var_name_in_user_type(user_type* ut, wiz_string* varName, int option);
	void remove_item_list_in_user_type(user_type* ut);//
	void remove_empty_item_in_user_type(user_type* ut);
	void remove_user_type_in_user_type(user_type* ut);
	//void remove_user_type_list_in_user_type(user_type* ut); // chk
	void remove_user_type_list_by_var_name_in_user_type(user_type* ut, wiz_string* varName, int option);
	//			
	void remove_list_in_user_type(user_type* ut, size_t idx); // ilis_t_idx!

	int empty_in_user_type(user_type* ut);

	void insert_item_by_ilist_in_user_type(user_type* ut, size_t ilis_t_idx, wiz_string* name, wiz_string* item);

	// chk
	void insert_user_type_by_ilist_in_user_type(user_type* ut, int ilis_t_idx, user_type* item);
	void add_item_in_user_type(user_type* ut, wiz_string* name, wiz_string* item);
	void add_user_type_item_in_user_type(user_type* ut, user_type* item);
	void add_user_type_item_in_user_type2(user_type* ut, user_type* item);
	void add_item_at_front_in_user_type(user_type* ut, wiz_string* name, wiz_string* item);
	void add_user_type_item_at_front_in_user_type(user_type* ut, user_type* item);


	wiz_vector_item_type get_item_in_user_type(user_type* ut, wiz_string* name);

	// regex to SetItem?
	int set_item_by_idx_in_user_type(user_type* ut, size_t idx, wiz_string* value);

	/// add set Data
	int set_item_by_name_in_user_type(user_type* ut, wiz_string* name, wiz_string* value);

	wiz_vector_any get_user_type_item_in_user_type(user_type* ut, wiz_string* name);
	wiz_vector_any get_user_type_item_except_in_user_type(user_type* ut, wiz_string* name);
	// deep copy.
	wiz_vector_any get_copy_user_type_item_in_user_type(user_type* ut, wiz_string* name);
	int get_user_type_item_ref_in_user_type(user_type* ut, size_t idx, user_type* ref);
	int get_last_user_type_item_ref_in_user_type(user_type* ut, wiz_string* name, user_type** ref);
	void save1_in_user_type(FILE* stream, user_type* ut, int depth);
	void save2_in_user_type(FILE* stream, user_type* ut, int depth);
	wiz_string item_list_to_string_in_user_type(user_type* ut, wiz_string_builder* builder);
	wiz_string item_list_names_to_string_in_user_type(user_type* ut);
	wiz_vector_wiz_string userType_list_names_to_string_array_in_user_type(user_type* ut);
	wiz_string user_type_list_names_to_string_in_user_type(user_type* ut);
	wiz_string to_string_in_user_type(user_type* ut, wiz_string_builder* builder);
	pair_int_and_wiz_vector_any find_user_type_in_user_type(user_type* global, wiz_string* _position, wiz_string_builder* builder);

#ifdef __cplusplus
}
#endif

#endif
