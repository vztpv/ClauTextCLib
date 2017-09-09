
#include "wiz_deck_wiz_string.h"

#define FORM(A, B) A##B


//static?
void FORM(expand_wiz_deck_, wiz_string)(FORM(wiz_deck_, wiz_string)* deck)
{
	size_t i;
	FORM(wiz_vector_, wiz_string) temp;

	FORM(init_wiz_vector_, wiz_string)(&temp, (deck->num) * 2);

	temp.num = deck->num;
	for (i = 0; i < deck->num; ++i) {
		temp.vec[i] = *(FORM(get_wiz_deck_, wiz_string)(deck, i));
	}

	//printf("%d %d\n", temp.capacity, deck->num);

	FORM(free_wiz_vector_, wiz_string)(&(deck->deck)); // cf) ~.swap(~);
	deck->deck = temp;
	deck->start = 0;
}

void FORM(init_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	deck->num = 0;
	deck->start = 0;
	FORM(init_wiz_vector_, wiz_string)(&(deck->deck), 2);
}
void FORM(free_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	deck->num = 0;
	deck->start = 0;
	FORM(free_wiz_vector_, wiz_string)(&(deck->deck));
}

void FORM(push_back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, wiz_string* val)
{
	if (FORM(is_full_wiz_deck_, wiz_string)(deck))
	{
		FORM(expand_wiz_deck_, wiz_string)(deck);
	}
	FORM(set_wiz_vector_, wiz_string)(&(deck->deck), (deck->start + deck->num) & (FORM(get_num_max_wiz_deck_, wiz_string)(deck) - 1), val);
	deck->num++;
	deck->deck.num++;
}

void FORM(push_front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, wiz_string* val)
{
	if (FORM(is_full_wiz_deck_, wiz_string)(deck))
	{
		FORM(expand_wiz_deck_, wiz_string)(deck);
	}

	deck->start = (deck->start - 1 + FORM(get_num_max_wiz_deck_, wiz_string)(deck)) 
									& (FORM(get_num_max_wiz_deck_, wiz_string) (deck) - 1); // % deck.size(), 2^n.
	FORM(set_wiz_vector_, wiz_string)(&(deck->deck), deck->start, val);
	deck->num++;
	deck->deck.num++;
}
wiz_string* FORM(pop_front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	wiz_string* temp = FORM(get_wiz_deck_, wiz_string) (deck, deck->start);

	//deck[start] = T();

	deck->start = (deck->start + 1) & (FORM(get_num_max_wiz_deck_, wiz_string) (deck) - 1); // % deck.size(), 2^n.
	deck->num--;
	deck->deck.num--;
	return temp;
}
wiz_string* FORM(pop_back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	wiz_string* temp = (FORM(get_wiz_deck_, wiz_string) (deck, deck->num - 1));

	deck->num--;
	deck->deck.num--;

	return temp;
}

wiz_string* FORM(back_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	wiz_string* temp = (FORM(get_wiz_deck_, wiz_string) (deck, deck->num - 1));

	return temp;
}
wiz_string* FORM(front_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	wiz_string* temp = (FORM(get_wiz_deck_, wiz_string) (deck, 0));

	return temp;
}
wiz_string* FORM(get_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck, const size_t idx)
{
	return (FORM(get_wiz_vector_, wiz_string)(&(deck->deck), (deck->start + idx) & (FORM(get_num_max_wiz_deck_, wiz_string)(deck) - 1)));
}

int FORM(is_full_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	return deck->num >= FORM(get_num_max_wiz_deck_, wiz_string)(deck);
}
size_t  FORM(size_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	return deck->num;
}
int  FORM(empty_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	return 0 == deck->num;
}
size_t  FORM(get_num_max_wiz_deck_, wiz_string) (FORM(wiz_deck_, wiz_string)* deck)
{
	return deck->deck.capacity;
}
