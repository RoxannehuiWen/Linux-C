#ifndef _Russia_Tetris_H
#define _Russia_Tetris_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

///////////////////////////////////////////////////

#define BG_LEFT 10
#define BG_TOP 3
#define WITH 10
#define HIGH 22
#define STATUS_WITH 5
#define BLOCK_NUM 7

///////////////////////////////////////////////////

#define COLOR_NUM 8
#define GREEN_BLUE 36

///////////////////////////////////////////////////

typedef struct LINE{
	int x;
	int y;
	int length;
	int character;
	int color;
}Line,*pLine;

typedef struct BLOCK{
	int style;
	int forward;
	int x;
	int color;
	int y;
	int pb[4][4];
}Block,*pBlock;

typedef struct PLAYER
{
	Block now;
	Block old;
	Block will;
	char *name;
	int speed;
	int score;
	
}Player,*pPlayer;

///////////////////////////////////////////////////
/*******             driver.c             ********/

void set_timer(int c);
void gotoxy(int x,int y);
int getch(void);
void assistant_driver(void);
void draw_line_row(pLine line);
void draw_line_col(pLine line);
void draw_text(int x,int y,int tcolor,const char *text);
void draw_number(int x,int y,int tcolor,int num);

///////////////////////////////////////////////////
/*******             common.c             ********/
int write_array(pBlock p);
void Init_player();
void run_game(int key);
void get_input();
void show_background();

///////////////////////////////////////////////////
/*******             output.c             ********/
void draw_block(pBlock p);
void delete_old(pBlock p);
void make_will_block(pPlayer player);
void show_blocks();
void delete_line(pPlayer cplayer);

///////////////////////////////////////////////////
/*******              move.c              ********/

void turn_around(pPlayer player);
void move_block_a(pPlayer player);
void move_block_d(pPlayer player);
void move_block_s(pPlayer player);

///////////////////////////////////////////////////
/*******              check.c             ********/

int horizontal_left_collision(int (*tmp)[4],pBlock p);
int horizontal_right_collision(int (*tmp)[4],pBlock p);
int vertical_collision(int (*tmp)[4],pBlock p);
int is_horizontal_left_collision(pBlock p);
int is_horizontal_right_collision(pBlock p);
int is_vertical_collision(pBlock p);

///////////////////////////////////////////////////
/*******              main.c              ********/

void init_game();
void turn_game(int time);

#endif
