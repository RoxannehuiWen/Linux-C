#include "../include/head.h"

Player player1,player2;

extern int key1,key2;

extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;

void move_block_a(pPlayer player)
{
		pBlock p=&player->now;
		if(!is_horizontal_left_collision(p))
		{

				delete_old(p);
				p->x--;
				draw_block(p);
				player->old=player->now;
		}
}

void move_block_d(pPlayer player)
{
		pBlock p=&player->now;
		if(!is_horizontal_right_collision(p))
		{

				delete_old(p);
				p->x++;
				draw_block(p);
				player->old=player->now;

		}
}
void move_block_s(pPlayer player)
{
		pBlock p=&player->now;
		if(!is_vertical_collision(p))
		{
				delete_old(p);
				p->y++;
				draw_block(p);
				player->old=player->now;
		}
}
void turn_around(pPlayer player)
{int i,j;
		int playerblock[4][4];	
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						playerblock[i][j]=0;
		pBlock p=&player->now;

		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
				{
						playerblock[j][3-i]=(p->pb)[i][j];
				}

		if(!horizontal_left_collision(playerblock,p)&&!horizontal_right_collision(playerblock,p)&&!vertical_collision(playerblock,p))
		{
				delete_old(p);
				for(i=0;i<4;i++)
						for(j=0;j<4;j++)
						{				
								(p->pb)[i][j]=playerblock[i][j];
						}

				draw_block(p);
				player->old=player->now;
		}

}

