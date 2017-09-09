
#include "wiz_deck_pair_user_type_ptr_and_int.h"

#define FORM(A, B) A##B


//static?
void FORM(expand_wiz_deck_, pair_user_type_ptr_and_int)(FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	size_t i;
	FORM(wiz_vector_, pair_user_type_ptr_and_int) temp;

	FORM(init_wiz_vector_, pair_user_type_ptr_and_int)(&temp, (deck->num) * 2);

	temp.num = deck->num;
	for (i = 0; i < deck->num; ++i) {
		temp.vec[i] = *(FORM(get_wiz_deck_, pair_user_type_ptr_and_int)(deck, i));
	}

	//printf("%d %d\n", temp.capacity, deck->num);

	FORM(free_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck)); // cf) ~.swap(~);
	deck->deck = temp;
	deck->start = 0;
}

void FORM(init_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	deck->num = 0;
	deck->start = 0;
	FORM(init_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck), 2);
}
void FORM(free_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	deck->num = 0;
	deck->start = 0;
	FORM(free_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck));
}

void FORM(push_back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, pair_user_type_ptr_and_int* val)
{
	if (FORM(is_full_wiz_deck_, pair_user_type_ptr_and_int)(deck))
	{
		FORM(expand_wiz_deck_, pair_user_type_ptr_and_int)(deck);
	}
	FORM(set_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck), (deck->start + deck->num) & (FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int)(deck) - 1), val);
	deck->num++;
	deck->deck.num++;
}

void FORM(push_front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, pair_user_type_ptr_and_int* val)
{
	if (FORM(is_full_wiz_deck_, pair_user_type_ptr_and_int)(deck))
	{
		FORM(expand_wiz_deck_, pair_user_type_ptr_and_int)(deck);
	}

	deck->start = (deck->start - 1 + FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int)(deck))
		& (FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int) (deck) - 1); // % deck.size(), 2^n.
	FORM(set_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck), deck->start, val);
	deck->num++;
	deck->deck.num++;
}
pair_user_type_ptr_and_int* FORM(pop_front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	pair_user_type_ptr_and_int* temp = FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (deck, deck->start);

	//deck[start] = T();

	deck->start = (deck->start + 1) & (FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int) (deck) - 1); // % deck.size(), 2^n.
	deck->num--;
	deck->deck.num--;
	return temp;
}
pair_user_type_ptr_and_int* FORM(pop_back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	pair_user_type_ptr_and_int* temp = (FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (deck, deck->num - 1));

	deck->num--;
	deck->deck.num--;

	return temp;
}

pair_user_type_ptr_and_int* FORM(back_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	pair_user_type_ptr_and_int* temp = (FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (deck, deck->num - 1));

	return temp;
}
pair_user_type_ptr_and_int* FORM(front_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	pair_user_type_ptr_and_int* temp = (FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (deck, 0));

	return temp;
}
pair_user_type_ptr_and_int* FORM(get_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck, const size_t idx)
{
	return (FORM(get_wiz_vector_, pair_user_type_ptr_and_int)(&(deck->deck), (deck->start + idx) & (FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int)(deck) - 1)));
}

int FORM(is_full_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	return deck->num >= FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int)(deck);
}
size_t  FORM(size_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	return deck->num;
}
int  FORM(empty_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	return 0 == deck->num;
}
size_t  FORM(get_num_max_wiz_deck_, pair_user_type_ptr_and_int) (FORM(wiz_deck_, pair_user_type_ptr_and_int)* deck)
{
	return deck->deck.capacity;
}
