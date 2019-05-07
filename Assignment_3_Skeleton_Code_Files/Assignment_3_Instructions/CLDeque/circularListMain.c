#include "circularList.h"
#include <stdio.h>

int main()
{	
	printf("--ADD Tests---\n");

	struct CircularList* deque = circularListCreate(); 
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	
	printf("PRINT [6, 5, 4, 1, 2, 3]: \n");
	circularListPrint(deque);

	printf("FRONT 6: \n");
	printf("%g\n", circularListFront(deque));

	printf("FRONT 3: \n");
	printf("%g\n", circularListBack(deque));
	
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);

	printf("PRINT [5, 4, 1, 2]: \n");
	circularListPrint(deque);
	
	printf("PRINT [2, 1, 4, 5]: \n");
	circularListReverse(deque);
	circularListPrint(deque);
	
	circularListDestroy(deque);
	
	return 0;
}
