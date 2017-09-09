
#ifndef PAIR_H
#define PAIR_H

#include "wiz_vector.h"
#include "wiz_load_data_token.h"
#include "wiz_string.h"

struct pair_int_and_wiz_vector_any
{
	int first;
	wiz_vector_any second;
};

struct pair_bool_and_token
{
	int first;
	token second;
};

struct pair_int_and_token
{
	int first;
	token second;
};

struct pair_user_type_ptr_and_int
{
	void* first;
	int second;
};

struct pair_wiz_string_and_wiz_string
{
	wiz_string first;
	wiz_string second;
};

struct pair_wiz_string_and_user_type
{
	wiz_string first;
	void* second;
};

struct pair_wiz_string_and_int
{
	wiz_string first;
	int second;
};

typedef struct pair_int_and_wiz_vector_any pair_int_and_wiz_vector_any;

typedef struct pair_bool_and_token pair_bool_and_token;

typedef struct pair_int_and_token pair_int_and_token;

typedef struct pair_user_type_ptr_and_int pair_user_type_ptr_and_int;

typedef struct pair_wiz_string_and_wiz_string pair_wiz_string_and_wiz_string;

typedef struct pair_wiz_string_and_user_type pair_wiz_string_and_user_type;

typedef struct pair_wiz_string_and_int pair_wiz_string_and_int;

#endif
