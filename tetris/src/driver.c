#include "../include/head.h"

Player player1,player2;
extern int key1,key2;
extern int player1block[4][4];
extern int player2block[4][4];
extern int block[BLOCK_NUM][4][4];
extern int player_array[HIGH][WITH*2+STATUS_WITH*2+1];
extern int game_over;
extern int current_player;

void set_timer(int c)
{
	struct itimerval tick = { { 0,c*5000 }, { 0,c*5000 } };
	setitimer(ITIMER_REAL, &tick, NULL);
}

void gotoxy(int x,int y)
{
//		if(current_player==1)
	printf("\033[%d;%dH",y+BG_TOP,x+BG_LEFT);
//		else 
//	printf("\033[%d;%dH",y+BG_TOP,x+BG_LEFT+WITH+STATUS_WITH*2);
}

int getch(void)
{
        int ch;
        struct termios raw,save;
        tcgetattr(0,&save);
        cfmakeraw(&raw);
        tcsetattr(0,0,&raw);
        ch=getchar();
        fflush(NULL);
        tcsetattr(0,0,&save);
        return ch;
}

void assistant_driver(void)
{
	signal(SIGALRM, turn_game);
	set_timer(100);
//	alarm(1);
	system("clear");
	printf("\033[?25l");
}

void draw_line_row(pLine line)
{
	int i;
	gotoxy(line->x,line->y);
	for(i=0;i<line->length;++i)
	{
		printf("\033[0;%dm%c\033[0m",line->color,line->character);
	}
}

void draw_line_col(pLine line)
{
	int i;
	for(i=0;i<line->length;++i)
	{
		gotoxy(line->x,line->y+i);
		printf("\033[0;%dm%c\033[0m",line->color,line->character);
	}
}
void draw_text(int x,int y,int tcolor,const char *text)
{
	gotoxy(x,y);
	printf("\033[%dm%s\033[0m",tcolor,text);
}

void draw_number(int x,int y,int tcolor,int num)
{
	gotoxy(x,y);
	printf("\033[%dm%d\033[0m",tcolor,num);
}




