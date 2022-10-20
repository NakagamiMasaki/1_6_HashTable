#include <stdio.h>

#include "LinkedList.h"
#include "HashTable.h"

class HashFunc
{
public:

	int32_t operator()(int n)
	{
		return n % 10;
	}
};

int main(void)
{
	HashTable<int, float, HashFunc, 10> table;
	table.Insert(0, 0.0f);
	table.Insert(10, 10.0f);
	table.Insert(1, 1.0f);
	table.Insert(2, 2.0f);

	float f;
	table.Find(10, f);
	printf("%f", f);


	rewind(stdin);
	getchar();

	return 0;
}