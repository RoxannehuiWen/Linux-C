#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"
#include "../include/queue.h"

void Init_eTreeNode(pTree *p,etype data)
{
	*p=malloc(sizeof(Tree));
	(*p)->data=data;
	(*p)->count=1;;
	(*p)->left=NULL;
	(*p)->right=NULL;
	(*p)->next=NULL;
}

void Init_TreeNode(pTree *p)
{
	*p=malloc(sizeof(Tree));
	(*p)->data=0;
	(*p)->count=0;
	(*p)->left=NULL;
	(*p)->right=NULL;
	(*p)->next=NULL;
}

int Read_File(pTree proot,FILE *pr,FILE *pw)
{
	pTree p,pnew;
	unsigned char ch;
	if(proot==NULL)return 0;
	while(fread(&ch,sizeof(unsigned char),1,pr)>0)
	{
		printf("%c",ch);
		for(p=proot;p->next!=NULL;p=p->next)
			if(p->next->data==ch)
			{
				(p->next->count)++;
				break;
			}
		if(p->next==NULL&&p->data!=ch)
		{
			Init_eTreeNode(&pnew,ch);
			p->next=pnew;
		}
	}
	//for test
	int total=0,num=0;
	for(p=proot->next;p!=NULL;p=p->next)
	{
		//	printf("%c:%d\n",p->data,p->count);
		fwrite(&p->data,sizeof(char),1,pw);		
		fwrite(&p->count,sizeof(int),1,pw);		
		printf("%c:%d\n",p->data,p->count);
		total+=p->count;
		num++;
	}
	printf("total:%d num:%d\n",total,num);
	return num;
}

pTree Get_Frequency(pTree proot)
{
	//	if(proot==NULL)return NULL;
	if(proot->next==NULL) return NULL;
	pTree p,ps=proot,min=proot->next,prev;
	//pnode ptmp,pi;
	for(prev=proot;prev->next!=NULL;prev=prev->next)
	{
		p=prev->next;
		
		if(p->count<min->count)
		{
			min=p;ps=prev;
			//		printf("%p-",min);
		}
	}


	ps->next=min->next;

	printf("huffman:%d",min->count);
	return min;
		
}

void huffman(pTree *proot)
{
	pTree min1,min2;
	pTree pnew,p;

	while((min1=Get_Frequency(*proot))!=NULL&&(min2=Get_Frequency(*proot))!=NULL)
	{	
		Init_TreeNode(&pnew);
		puts("*");
	
		pnew->left=min1;
		pnew->right=min2;
		pnew->count=min1->count+min2->count;
		min1->next=pnew;min2->next=pnew;
		p=(*proot)->next;
		(*	proot)->next=pnew;
		pnew->next=p;
		
	}

	
	free(*proot);
	*proot=min1;
	puts("----");
}

void Read_Huffman(pTree proot,int n,FILE *pr,FILE *pw)
{

	unsigned char bigcode=0;

	pTree pnew,pp,pc;
	Init_eTreeNode(&pnew,0);
	pStack ps;
	Init_Stack(&ps);

	pQueue p;

	Init_Queue(&p,NULL);
	push_queue(p,proot);

	int count=0,Num_Byte=1;
	unsigned char ch;
	while(fread(&ch,sizeof(char),1,pr)>0)
	{
		push_queue(p,proot);
		while(pop_queue(p,&pnew))
		{
			if(pnew->left==NULL)
			{
				if(ch==pnew->data)
				{
				
					while(pnew!=NULL)
					{//printf(":%d:",pnew->count);
						push(ps,pnew);
						pnew=pnew->next;
					}//puts("**");
					pop(ps,&pp);
					while(pop(ps,&pc))
					{

						if(count==8){
					//		printf("bigcode=%d\n",bigcode);
							fwrite(&bigcode,sizeof(char),1,pw);
							count=0;
							bigcode=0;Num_Byte++;
							}
						if(pp->left==pc)
							{
								bigcode=(bigcode<<1)+0;
								count++;
							}
						else    {
								bigcode=(bigcode<<1)+1;
								count++;
							}

							pp=pc;
					}
					while(pop_queue(p,&pnew));

				}
			}
			else {
				push_queue(p,pnew->right);
				push_queue(p,pnew->left);
			}
		}

	}
	bigcode=bigcode<<(8-count);
	fwrite(&bigcode,sizeof(char),1,pw);
	printf("bigcode=%d\n",bigcode);
	
	int info0=n;
	int info1=count;
	int info2=Num_Byte;
	fwrite(&info0,sizeof(int),1,pw);
	fwrite(&info1,sizeof(int),1,pw);
	fwrite(&info2,sizeof(int),1,pw);
}
void Create_Huffman(pTree proot,int ch,FILE *pr)
{

	if(proot==NULL)return ;
	etype data;type count;


		printf("ch=%d\n",ch);
	pTree p=proot,pnew;
	while(ch)
	{
	fread(&data,sizeof(etype),1,pr);
	fread(&count,sizeof(type),1,pr);

	Init_eTreeNode(&pnew,data);
	pnew->data=data;pnew->count=count;
	p->next=pnew;p=pnew;

		ch--;
	}
	//for test
	int total=0,num=0;
	for(p=proot->next;p!=NULL;p=p->next)
	{
	//	printf("%c:%dch=%d\n",p->data,p->count,ch);
		total+=p->count;
		num++;
	}
	printf("total:%d num:%d\n",total,num);
	
}


void ReHuffman(pTree proot,FILE *pr,FILE *pw,int count ,int Num_Byte){
	pTree p=proot;
	unsigned char ch,chcpy[8];
	int n;
	while(--Num_Byte&&fread(&ch,sizeof(unsigned char),1,pr)>0)
	{
		chcpy[0]=ch&128;
		chcpy[1]=ch&64;
		chcpy[2]=ch&32;
		chcpy[3]=ch&16;
		chcpy[4]=ch&8;
		chcpy[5]=ch&4;
		chcpy[6]=ch&2;
		chcpy[7]=ch&1;
		for(n=0;n<8;n++)	
			printf("%d--",chcpy[n]);n=0;
		while(n<8)
		{
			if(p->left==NULL)
			{
				printf("%c\n",p->data);
				fwrite(&p->data,sizeof(unsigned char ),1,pw);
				p=proot;
				continue;
			}
			if(chcpy[n])
			{
				p=p->right;
			}
			else 
			{
				p=p->left;
			}
			n++;
		}
	}

	fread(&ch,sizeof(unsigned char),1,pr);
		chcpy[0]=ch&128;
		chcpy[1]=ch&64;
		chcpy[2]=ch&32;
		chcpy[3]=ch&16;
		chcpy[4]=ch&8;
		chcpy[5]=ch&4;
		chcpy[6]=ch&2;
		chcpy[7]=ch&1;
		for(n=0;n<8;n++)	
			printf("%d--",chcpy[n]);
		n=0;
		while(n<count)
		{
			if(p->left==NULL)
			{
				printf("%c:\n",p->data);
				fwrite(&p->data,sizeof(char),1,pw);
				p=proot;
				continue;
			}
			if(chcpy[n])
			{
				p=p->right;
			}
			else 
			{
				p=p->left;
			}
			n++;
		}
}

