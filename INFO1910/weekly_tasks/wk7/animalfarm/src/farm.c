#include "farm.h"

int main()
{
	struct resources res;

	res.eggs = 0;
	res.milk = 0;
	res.wool = 0;
	res.pork = 0;

	srandom(time(NULL));
	struct animal farm[128];

	struct animal (*animal_constructor[4])(int) = {cow_constructor, 
		hen_constructor,
		pig_constructor,
		sheep_constructor};


	for(int i = 0; i < 128; i++)
	{
		int efficiency = random() % 5 + 1;
		farm[i] = animal_constructor[random() % 4](efficiency);
		farm[i].exclaim(&farm[i]);
	}

	workday(farm, &res);



	return 0;
}

void workday(struct animal* farm, struct resources* res)
{
	for(int i = 0; i < 128; i++)
	{
        work(farm + i, res);
	}

	printf("Milk: %ld\n", res->milk);
	printf("Wool: %ld\n", res->wool);
	printf("Eggs: %ld\n", res->eggs);
	printf("Pork: %ld\n", res->pork);

	return;
}
