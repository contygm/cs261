#include "linkedList.h"
#include <stdio.h>

int main(){
	printf("--Linked List Tests---\n");
	struct LinkedList* l = linkedListCreate(); 
	linkedListAddFront(l, (TYPE)1);
	linkedListAddBack(l, (TYPE)2);
	linkedListAddBack(l, (TYPE)3);
	linkedListAddFront(l, (TYPE)4);
	linkedListAddFront(l, (TYPE)5);
	linkedListAddBack(l, (TYPE)6);
	printf("linked list [5, 4, 1, 2, 3, 6]:\n");
	linkedListPrint(l);

	printf("linked front:\n");
	printf("%i\n", linkedListFront(l));
	printf("linked back:\n");
	printf("%i\n", linkedListBack(l));
	linkedListRemoveFront(l);
	linkedListRemoveBack(l);
	printf("linked list, remove front & back [4, 1, 2, 3]:\n");
	linkedListPrint(l);
    linkedListDestroy(l);
/* BAG */
	
	struct LinkedList* k = linkedListCreate(); 
	linkedListAdd (k, (TYPE)10);
	linkedListAdd (k, (TYPE)11);
	linkedListAdd (k, (TYPE)13);
	linkedListAdd(k, (TYPE)14);
	linkedListRemove(k, (TYPE)11);
	linkedListPrint(k);
	linkedListDestroy(k);
	return 0;
}

