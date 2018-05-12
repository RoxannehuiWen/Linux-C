#include "../include/head.h"

Player player1,player2;

extern int key1,key2;

extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;

int horizontal_left_collision(int (*tmp)[4],pBlock p)
{
		int left;
		if(current_player==1)
				left=0;
		else left=WITH+STATUS_WITH*2+1;
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if(tmp[i][j]&&((j+p->x)<left||player_array[p->y+i][j+p->x]))
								return 1;
		return 0;
}

int horizontal_right_collision(int (*tmp)[4],pBlock p)
{
		int right;
		if(current_player==1)
				right=WITH-1;
		else right=WITH*2+STATUS_WITH*2;
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if(tmp[i][j]&&((j+p->x)>right||player_array[p->y+i][j+p->x]))
								return 1;
		return 0;
}

int vertical_collision(int (*tmp)[4],pBlock p)
{
		int i,j;

		for(i=3;i>=0;i--)
				for(j=0;j<4;j++)
						if(tmp[i][j]&&(i+p->y)==HIGH)
								return 2;

		for(i=3;i>0;i--)
				for(j=0;j<4;j++)
						if(tmp[i][j]&&p->y+i>0&&player_array[p->y+i][p->x+j])
						{
								return 3;
						}
		return 0;
}

int is_horizontal_left_collision(pBlock p)
{
		int left;
		if(current_player==1)
				left=0;
		else left=WITH+STATUS_WITH*2+1;
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if((p->pb)[i][j]&&((j+p->x-1)<left||player_array[p->y+i][j+p->x-1]))
								return 1;
		return 0;
}

int is_horizontal_right_collision(pBlock p)
{
		int right;
		if(current_player==1)
				right=WITH-1;
		else right=WITH*2+STATUS_WITH*2;
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if((p->pb)[i][j]&&((j+p->x+1)>right||player_array[p->y+i][j+p->x+1]))
								return 1;
		return 0;
}

int is_vertical_collision(pBlock p)
{
		int i,j;

		for(i=3;i>=0;i--)
				for(j=0;j<4;j++)
						if((p->pb)[i][j]&&(i+p->y+1)==HIGH)
								return 2;

		for(i=3;i>0;i--)
				for(j=0;j<4;j++)
						if((p->pb)[i][j]&&p->y+1+i>0&&player_array[p->y+1+i][p->x+j])
						{
								//	printf("i=%d,j=%d\n ret=%d",p->y+i+1,p->x+j,player_array[p->y+1+i][p->x+j]);
								return 3;
						}
		return 0;
}



