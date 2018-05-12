#include "../include/head.h"

Player player1,player2;

extern int key1,key2;

extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;

void draw_block(pBlock p)
{
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
				{
						gotoxy(j*2+p->x*2,i+p->y);
						if((p->pb)[i][j]&&i+p->y>0)
						{
								printf("\033[%dm__\033[0m",p->color);
						}
				}
		printf("\n");
}

void delete_old(pBlock p)
{
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if((p->pb)[i][j]&&i+p->y>0)
						{
								gotoxy(j*2+p->x*2,i+p->y);
								if(!(i+p->y))
										printf("\033[%dm__\033[0m",GREEN_BLUE);
								else if(i+p->y==HIGH-1)
										printf("\033[%dm__\033[0m",GREEN_BLUE);
								else printf("  ");
						}
		
		printf("\n");
}
void make_will_block(pPlayer player)
{
		int i,j;
		pBlock p;
		p=&player->will;
		if(current_player==1)p->x=WITH+1;else p->x=STATUS_WITH+WITH+1;
		p->y=2;
		delete_old(p);
		p->style=rand()%BLOCK_NUM;
		p->forward=rand()%4;
		p->color=rand()%COLOR_NUM+40;
		if(current_player==1)p->x=WITH+1;else p->x=STATUS_WITH+WITH+1;
		p->y=2;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						(p->pb)[i][j]=block[p->style][i][j];
		draw_block(p);
		if(current_player==1)p->x=WITH/2-1;else p->x=STATUS_WITH*2+WITH+WITH/2-1;
		p->y=-3;
		for(i=0;i<4;i++)
				if(block[p->style][3][i])
				{
						p->y=-4;break;
				}
}
void show_blocks()
{
	int i,j;
	for(i=0;i<HIGH;i++)
		for(j=0;j<(WITH*2+STATUS_WITH*2+1);j++)
		{
			if(player_array[i][j])
			{
				gotoxy(2*j,i);
				printf("\033[%dm__\033[0m",player_array[i][j]);
			}
		}
	printf("\n");
}
void delete_line(pPlayer cplayer)
{
		int left,right;
		if(cplayer==&player1)
		{left=0;right=WITH;}
		else 
		{
				left=WITH+STATUS_WITH*2+1;
				right=WITH*2+STATUS_WITH*2+1;
		}
		int i,j,k;
		for(i=0;i<HIGH;i++)
		{			
				for(j=left;j<right;j++)
						if(!player_array[i][j])break;
				if(j==right)
				{
						cplayer->score++;
						if(cplayer->speed>10)
								set_timer(cplayer->speed--);
if(current_player==1)
						draw_number(WITH*2+5,14,32,cplayer->score);
else draw_number(WITH*2+16,14,32,cplayer->score);
						for(k=i;k>0;k--)
						{		
								for(j=left;j<right;j++)
								{	 
										player_array[k][j]=player_array[k-1][j]; 	 
										gotoxy(2*j,k);
									if(k==HIGH-1) printf("\033[%dm__\033[0m",GREEN_BLUE);					
										else	printf("  ");

								}
								printf("\n");
						}
				}

		}

		show_blocks();
}

