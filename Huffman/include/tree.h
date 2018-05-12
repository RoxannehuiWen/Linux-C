#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>


typedef unsigned char etype;
typedef int type;
typedef struct TreeNode
{


etype data;

type count;

struct TreeNode *next;
struct TreeNode *left;
struct TreeNode *right;
}Tree,*pTree;


void Init_eTreeNode(pTree *p,etype data);
void Init_TreeNode(pTree *p);

int Read_File(pTree proot,FILE *pr,FILE *pw);
pTree Get_Frequency(pTree proot);

void huffman(pTree *proot);
void Read_Huffman(pTree proot,int n,FILE *pr,FILE *pw);
void Create_Huffman(pTree proot,int ch,FILE *pr);
void     ReHuffman(pTree proot,FILE *pr,FILE *pw,int count,int Num_Byte);

#endif
