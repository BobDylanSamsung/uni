#include "chess.h"

int main()
{
	srandom(time(NULL));
	struct position rand_loc;
	rand_loc.row = (random() % 8) + 'a';
	rand_loc.column = random() % 8;

	printf("%c\t %d\n", rand_loc.row, rand_loc.column);
	return 0;
}