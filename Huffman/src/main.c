#include <stdio.h>
#include "../include/tree.h"
#include "../include/queue.h"
int main(int argc,char *argv[])
{
	FILE *pr,*pw;
	pTree proot;
	Init_TreeNode(&proot);
	int num=0;
	if(argc<4)
	{
		fprintf(stderr,"not enough arguments\n");
		return -1;
	}
	if(*argv[1]=='c')
	{
		pr=fopen(argv[2],"r");
		if(pr==NULL)
		{
			perror("fopen(r)");
			return -1;
		}
		
		pw=fopen(argv[3],"w");
		if(pw==NULL)
		{
			perror("fopen(w)");
			return -1;
		}
		num=Read_File(proot,pr,pw);

		huffman(&proot);
		fseek(pr,0,SEEK_SET);
	
		Read_Huffman(proot,num,pr,pw);

	}
	else if(*argv[1]=='d')
	{
		int count,Num_Byte,ch;
		pr=fopen(argv[2],"r");
		if(pr==NULL)
		{
			perror("fopen(r)");
			return -1;
		}
		fseek(pr,-12,SEEK_END);
		fread(&ch,sizeof(int),1,pr);
		fread(&count,sizeof(int),1,pr);
		fread(&Num_Byte,sizeof(int),1,pr);
		printf("%d/%d/%d\n",ch,count,Num_Byte);
		fseek(pr,0,SEEK_SET);
		Create_Huffman(proot,ch,pr);
		huffman(&proot);
		fseek(pr,(sizeof(int)+sizeof(char))*ch,SEEK_SET);
		pw=fopen(argv[3],"w");
		if(pw==NULL)
		{
			perror("fopen(w)");
			return -1;
		}
		ReHuffman(proot,pr,pw,count,Num_Byte);
	}
	else{
		fprintf(stderr,"the arguments can not tell\n");
		return -1;
	}
	return 1;
}
