/*
 * qlib.c              Matt Bishop		April 4, 2005
 *
 * Implement a "queue of integers" module. 
 */
#include <stdio.h>
#include <stdlib.h>
#include "fqlib.h"

/*
 * create or delete a queue
 *
 * PARAMETERS:	QUEUE **qptr	space for, or pointer to, queue
 * 		int flag	1 for create, 0 for delete
 *		int size	max elements in queue
 */
void qmanage(QUEUE **qptr, int flag, int size)
{
	if (flag){
		/* allocate a new queue */
		*qptr = malloc(sizeof(QUEUE));
		(*qptr)->head = (*qptr)->count = 0;
		(*qptr)->que = malloc(size * sizeof(int));
		(*qptr)->size = size;
	}
	else{
		/* delete the current queue */
		(void) free((*qptr)->que);
		(void) free(*qptr);
	}
}

/*
 * add an element to an existing queue
 *
 * PARAMETERS:	QUEUE *qptr	pointer for queue involved
 *		int n		element to be appended
 */
void put_on_queue(QUEUE *qptr, int n)
{
	/* add new element to tail of queue */
	qptr->que[(qptr->head + qptr->count) % qptr->size] = n;
	qptr->count++;

}

/*
 * take an element off the front of an existing queue
 *
 * PARAMETERS:	QUEUE *qptr	pointer for queue involved
 *		int *n		storage for the return element
 */
void take_off_queue(QUEUE *qptr, int *n)
{
	/* return the element at the head of the queue */
	*n = qptr->que[qptr->head++];
	qptr->count--;
	qptr->head %= qptr->size;
}

int main() 
{
	QUEUE *qptr;
	
	// Overfilling Queue
	qmanage(&qptr,1,5);
	put_on_queue(qptr,1);
	put_on_queue(qptr,2);
	put_on_queue(qptr,3);
	put_on_queue(qptr,4);
	put_on_queue(qptr,5);
	put_on_queue(qptr,7);
	put_on_queue(qptr,7);
	put_on_queue(qptr,8);
	
	printf("QUEUE SIZE: %d\n", qptr->size);
	printf("QUEUE ELEMENTS ADDED: %d\n", qptr->count);
	// Taking off too many elements
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);
	take_off_queue(qptr, qptr->que);

	printf("QUEUE SIZE: %d\n", qptr->size);
	printf("QUEUE ELEMENTS REMOVED: %d\n", qptr->count);
	printf("QUEUE SIZE: %d\n", qptr->size);




	

	return 0;
}

