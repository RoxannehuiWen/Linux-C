#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE 128
#define STACK_INCREMENT_SIZE 128
#include "tree.h"

typedef pTree ElemType;
typedef struct stack
{
ElemType *bottom;
int top;
int size;

}sStack,*pStack;
void Init_Stack(pStack *p);
int isEmpty(pStack p);
int isFull(pStack p);
int push(pStack,ElemType e);
int pop(pStack p,ElemType *e);
int getTop(pStack p,ElemType *e);
#endif
