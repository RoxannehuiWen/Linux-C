#ifndef QUEUE_H_
#define QUEUE_H_

#include "tree.h"

typedef pTree QueueElem;

typedef struct queue
{
	QueueElem data;
	struct queue *next;
}sQueue, *pQueue;

void Init_Queue(pQueue *p, QueueElem data);

int push_queue(pQueue pq, QueueElem data);

int pop_queue(pQueue pq, QueueElem *data);

#endif

