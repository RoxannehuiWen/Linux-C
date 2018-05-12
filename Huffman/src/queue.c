#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

void Init_Queue(pQueue *p, QueueElem data)
{
	*p=malloc(sizeof(sQueue));

	(*p)->data = data;
	(*p)->next = NULL;
}

int push_queue(pQueue pq, QueueElem ptree)
{
	pQueue ptrav = pq, pnew;
	if ( pq == NULL )
	{
		return 0;
	}
	while ( ptrav->next != NULL )
	{
		ptrav = ptrav->next;
	}
	Init_Queue(&pnew, ptree);
	
	ptrav->next = pnew;
	return 1;
}

int pop_queue(pQueue pq, QueueElem *data)
{
	pQueue pdel;
	if ( pq == NULL )
	{
		return -1;
	}
	if ( pq->next == NULL )
	{
		return 0;
	}
	pdel = pq->next;
	*data = pdel->data;

	pq->next = pdel->next;

free(pdel);
	return 1;
}




