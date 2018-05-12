#include "../include/head.h"

Player player1,player2;

extern int key1,key2;

extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;




void turn_game(int time)
{
		current_player=1;
		int ret1=is_vertical_collision(&player1.now);
		switch(ret1)
		{
				case 0:
						delete_old(&player1.old);
						(player1.now.y)++;
						draw_block(&player1.now);
						player1.old=player1.now;break;
				case 2:
				case 3:
						if(write_array(&player1.now))
								return;
						player1.now=player1.will;
						player1.old=player1.will;
						make_will_block(&player1);
						delete_line(&player1);
						break;
		}



		current_player=2;
		int  ret2=is_vertical_collision(&player2.now);
		switch(ret2)
		{
				case 0:
						delete_old(&player2.old);
						(player2.now.y)++;
						draw_block(&player2.now);
						player2.old=player2.now;break;
				case 2:
				case 3:
						if(write_array(&player2.now))
								return;
						player2.now=player2.will;
						player2.old=player2.will;
						make_will_block(&player2);
						delete_line(&player2);
						break;
		}
}


void init_game(void)
{
		assistant_driver();
		Init_player();
		show_background();
}

int main()
{
		init_game();
		get_input();	
		return 0;
}
