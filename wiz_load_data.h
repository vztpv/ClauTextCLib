
#ifndef WIZ_LOAD_DATA_H
#define WIZ_LOAD_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "wiz_load_data_user_type.h"
#include "wiz_map_wiz_string_and_wiz_string.h"
#include "wiz_map_wiz_string_and_user_type.h"
#include "wiz_stack_int.h"
#include "wiz_stack_wiz_string.h"
#include "wiz_stack_any.h"
#include "wiz_stack_size_t.h"


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

	typedef struct event_info event_info;

	void init_event_info(event_info* info);

	event_info deep_copy_event_info(event_info* info);

	void free_all_event_info(event_info* info);

	struct excute_data
	{
		int valid;

		user_type* pEvents;
		event_info info; // chk!
		int chkInfo;

		wiz_map_wiz_string_and_user_type* pObjectMap;
		wiz_map_wiz_string_and_user_type* pModule;

		long long depth;
	};

	typedef struct excute_data excute_data;

	//wiz_string excute_module(wiz_string* mainStr, user_type* _global, excute_data* excuteData);

	//
	pair_wiz_string_and_wiz_string Find2(user_type* ut, wiz_string* str);
	user_type load_data_from_file_in_load_data(wiz_string* fileName);
	user_type load_data_from_string_in_load_data(wiz_string* str);
	int save_data_in_load_data(wiz_string* fileName, user_type* global, int option);
	//wiz_string ToBool4(user_type* now, user_type* global, wiz_string* temp, excute_data* excuteData, wiz_string_builder* builder);


	// search_item
	// search_user_type
	// add_data_at_afront
	//// add_data
	int add_data_in_load_data(user_type* global, wiz_string* position, wiz_string* data, wiz_string* condition, excute_data* excuteData, wiz_string_builder* builder);

	// insert
	// add_no_name_user_type

	// get_item_list_names_data
	// get_user_type_list_names_data
	// get_data_by_var_name
	// remove_by_var_name
	// remove
	// remove_user_type
	// remove_item_type
	// remove_by_index
	// exist_data
	// exist_user_type
	// exist_one_user_type
	// exist_item
	// 
	// search_item
	// search_user_type
	// replace_item
	// remove_user_type_total
	// remove_data_type
	// replace_date_type
	// replace_date_type2
	// replace_data_type1
	// replace_data_type1_2
	// replace_data_type2
	//
#ifdef __cplusplus
}
#endif

#endif

