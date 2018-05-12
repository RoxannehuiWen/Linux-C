#include "../include/head.h"

Player player1,player2;

extern int key1,key2;
extern int playerblock[4][4];
extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;

int write_array(pBlock p)
{
		int i,j;
		for(i=0;i<4;i++)
				for(j=0;j<4;j++)
						if((p->pb)[i][j])
						{	if(p->y+i)
								{player_array[p->y+i][p->x+j]=p->color;}
								else {game_over=1;}
						}
		return game_over;
}

void Init_player()
{
	current_player=1;
	int i,j;
	srand(getpid());
	player1.now.style=rand()%BLOCK_NUM;
	for(i=0;i<4;i++)
	for(j=0;j<4;j++)
	player1.now.pb[i][j]=block[player1.now.style][i][j];
	player1.now.color=rand()%8+40;
	player1.now.x=WITH/2-1;
	player1.now.y=-4;
	player1.old=player1.now;
	player1.score=0;
	player1.speed=100;
	make_will_block(&player1);

	current_player=2;
	player2.now.style=rand()%BLOCK_NUM;
	for(i=0;i<4;i++)
	for(j=0;j<4;j++)
	player2.now.pb[i][j]=block[player2.now.style][i][j];
	player2.now.color=rand()%8+40;
	player2.now.x=STATUS_WITH*2+WITH+WITH/2-1;
	player2.now.y=-4;
	player2.old=player1.now;
	player2.score=0;
	player2.speed=100;
	make_will_block(&player2);

	for(i=0;i<HIGH;i++)
		for(j=0;j<(WITH*2+STATUS_WITH*2+2);j++)
		{
			player_array[i][j]=0;
		}
}


void run_game(int key)
{	
		switch(key)
		{
				case 0:turn_around(&player1);break;
				case 1:move_block_a(&player1);break;
				case 2:move_block_s(&player1);break;
				case 3:move_block_d(&player1);break;	

				case 5:turn_around(&player2);break;
				case 6:move_block_s(&player2);break;
				case 7:move_block_d(&player2);break;
				case 8:move_block_a(&player2);break;	
				default:break;
		}

}
void get_input()
{
		int ch;
		while(1)
		{
				ch=getch();
				if(ch=='q')
						break;
				if(ch=='\033')
				{
						ch=getch();
						if(ch=='[')
						{
								ch=getch();
								switch(ch)
								{
										case 'A':key2=5;break;//up
										case 'B':key2=6;break;//down
										case 'C':key2=7;break;//right
										case 'D':key2=8;break;//left
								}
						}
						current_player=2;
						run_game(key2);
						key2=9;
				}
				switch(ch)
				{
						case 'w':key1=0;break;
						case 'a':key1=1;break;//down
						case 's':key1=2;break;//right
						case 'd':key1=3;break;    //left	
				}
				current_player=1;
				run_game(key1);
				key1=4;
		}
}
void show_background()
{
	current_player=1;	
	Line line_bottom={0,0,(WITH*2+STATUS_WITH*2)*2+2,'_',GREEN_BLUE};
	draw_line_row(&line_bottom);
	line_bottom.y=HIGH-1;
	draw_line_row(&line_bottom);
	line_bottom.x=WITH*2;
	line_bottom.length=22;
	line_bottom.y=6;
	draw_line_row(&line_bottom);
	line_bottom.y=11;
	draw_line_row(&line_bottom);
	line_bottom.y=16;
	draw_line_row(&line_bottom);

	Line line_wall={-1,1,HIGH-1,'|',GREEN_BLUE};
	draw_line_col(&line_wall);
	line_wall.x=WITH*2;
	draw_line_col(&line_wall);
	line_wall.x=WITH*2+STATUS_WITH*2;
	draw_line_col(&line_wall);
	line_wall.x=WITH*2+STATUS_WITH*2+1;
	draw_line_col(&line_wall);
	line_wall.x=WITH*2+STATUS_WITH*2*2+1;
	draw_line_col(&line_wall);
	line_wall.x=(WITH*2+STATUS_WITH*2+1)*2;
	draw_line_col(&line_wall);
	
	draw_text(WITH*2+2,9,32,"PLAYER1");
	draw_text(WITH*2+13,9,32,"PLAYER2\n");
	draw_text(WITH*2+3,13,32,"SCORE");
	draw_text(WITH*2+14,13,32,"SCORE\n");
	draw_number(WITH*2+5,14,32,player1.score);
	draw_number(WITH*2+16,14,32,player2.score);
}
