#include "../include/proto.h"
#include "thr_list.h"
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

void _Malloc(void **p,int size)
{
	*p=malloc(size);
}

void _Free(void **p)
{
	if(*p!=NULL)
	{
		free(*p);
		*p=NULL;
	}
}

void Init_Node(pNode *p)
{
	_Malloc((void**)p,sizeof(sNode));
	(*p)->chnid=0;
	(*p)->next=NULL;
}
void Init_Music(pNode *p)
{
	_Malloc((void **)p,sizeof(Music));
	(*p)->chnid=0;
	(*p)->next=NULL;

}
void Create_List_From_Tail(pNode phead,pNode pnew)
{
	pNode ptail=phead;
	if(phead==NULL)
		return;

	while(ptail->next!=NULL){
		ptail=ptail->next;
	}
	ptail->next=pnew;
}

void Delete_Node_By_chnid(pNode phead,chnid_t chnid)
{
	pNode pdel,prev;
	if(phead == NULL)
		return ;
	for(prev=phead;prev->next!=NULL;)
	{
		pdel=prev->next;

		if(pdel->chnid==chnid)
		{
			prev->next=pdel->next;
			pdel->next=NULL;
			_Free_Node(&pdel);
		}else{
			prev=prev->next;
		}
	}
}

void Output_List(pNode phead)
{
	pNode ptrav=phead->next;
	for(;ptrav!=NULL;ptrav=ptrav->next)
		printf("id:%d_%s\n",ptrav->chnid,ptrav->desc);
	printf("\n");

}

////////////////////////////////////////////////////////////////////////////////
