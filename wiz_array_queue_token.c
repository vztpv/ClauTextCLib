
#include "wiz_array_queue_token.h"

#define FORM(A, B) A##B


//static?
void FORM(expand_wiz_array_queue_, token)(FORM(wiz_array_queue_, token)* que)
{
	size_t i;
	FORM(wiz_vector_, token) temp;
	
	FORM(init_wiz_vector_, token)(&temp, (que->num) * 2);
	
	temp.num = que->num;
	for (i = 0; i < que->num; ++i) {
		temp.vec[i] = *(FORM(get_wiz_array_queue_, token)(que, i));
	}

	//printf("%d %d\n", temp.capacity, que->num);

	FORM(free_wiz_vector_, token)(&(que->que)); // cf) ~.swap(~);
	que->que = temp;
	que->start = 0;
}

void FORM(init_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	que->num = 0;
	que->start = 0;
	FORM(init_wiz_vector_, token)(&(que->que), 2);
}
void FORM(free_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	que->num = 0;
	que->start = 0;
	FORM(free_wiz_vector_, token)(&(que->que));
}

void FORM(push_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que, token* val)
{
	if (FORM(is_full_wiz_array_queue_, token)(que))
	{
		FORM(expand_wiz_array_queue_, token)(que);
	}
	FORM(set_wiz_vector_, token)(&(que->que), (que->start + que->num) & (FORM(get_num_max_wiz_array_queue_, token)(que) - 1), val);
	que->num++;
	que->que.num++;
}
token* FORM(pop_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	token* temp = FORM(get_wiz_array_queue_, token) (que, que->start);

	//que[start] = T();

	que->start = (que->start + 1) & (FORM(get_num_max_wiz_array_queue_, token) (que) - 1); // % que.size(), 2^n.
	que->num--;
	que->que.num--;
	return temp;
}
token* FORM(pop_back_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	token* temp = (FORM(get_wiz_array_queue_, token) (que, que->num - 1));

	que->num--;
	que->que.num--;

	return temp;
}

token* FORM(back_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	token* temp = (FORM(get_wiz_array_queue_, token) (que, que->num - 1));

	return temp;
}
token* FORM(front_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	token* temp = (FORM(get_wiz_array_queue_, token) (que, 0));

	return temp;
}
token* FORM(get_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que, const size_t idx)
{
	return (FORM(get_wiz_vector_, token)(&(que->que), (que->start + idx) & (FORM(get_num_max_wiz_array_queue_, token)(que) - 1)));
}

int FORM(is_full_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	return que->num >= FORM(get_num_max_wiz_array_queue_, token)(que);
}
int FORM(is_empty_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que)
{
	return 0 == que->num;
}
size_t  FORM(size_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que) 
{ 
	return que->num;
}
int  FORM(empty_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que) 
{ 
	return FORM(is_empty_wiz_array_queue_, token) (que);
}
size_t  FORM(get_num_max_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que) 
{
	return que->que.capacity;
}
size_t  FORM(get_num_wiz_array_queue_, token) (FORM(wiz_array_queue_, token)* que) 
{ 
	return que->num;
}

void FORM(erase_in_wiz_array_queue_, token)(FORM(wiz_array_queue_, token)* token_vec, size_t idx)
{
	size_t i;

	for (i = idx; i < token_vec->num - 1; ++i) {
		*get_wiz_array_queue_token(token_vec, i) = *get_wiz_array_queue_token(token_vec, i + 1);
	}
	token_vec->num--;
	token_vec->que.num--;
}

