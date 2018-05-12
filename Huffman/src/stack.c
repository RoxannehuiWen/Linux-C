#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"


void Init_Stack(pStack *p)
{
	*p=malloc(sizeof(sStack));
	(*p)->bottom=malloc(sizeof(ElemType)*STACK_SIZE);
	(*p)->top=-1;
	(*p)->size=STACK_SIZE;

}

int isEmpty(pStack p)
{
	if(p->top==-1)
		return 1;

	return 0;

}

int isFull(pStack p)
{
	if(p->top==p->size-1)return 1;
	return 0;
}

int push(pStack p,ElemType e)
{
	if(isFull(p))
	{
		p->bottom=realloc(p->bottom,(p->size+STACK_INCREMENT_SIZE)*sizeof(ElemType));
		p->size+=STACK_INCREMENT_SIZE;


	}
	p->top++;
	p->bottom[p->top]=e;
	return 1;

}

int pop(pStack p,ElemType *e)
{
	if(isEmpty(p))
	{

		return 0;

	}

	*e=p->bottom[p->top];
	p->top--;
	return 1;

}

int getTop(pStack p,ElemType *e)
{
	if(isEmpty(p))
		return -1;
	*e=p->bottom[p->top];

	return 1;
}







