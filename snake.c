#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "snake.h"


#define UP_ARROW (char)'A' 
#define LEFT_ARROW (char)'D'
#define RIGHT_ARROW (char)'C'
#define DOWN_ARROW (char)'B'

#define ENTER_KEY 10
	
const char SNAKE_HEAD = 'X';
const char SNAKE_BODY = '#';
const char WALL = '#';	
const char FOOD = '*';
const char BLANK = ' ';

	


void loadEnviroment(int consoleWidth, int consoleHeight) {
	int i;
	int x = 1, y = 1;
	int rectangleHeight = consoleHeight - 4;
	clrscr(); /*clear the console*/
	
	gotoxy(x,y); /*Top left corner*/
	
	for (; y < rectangleHeight; y++)
	{
		gotoxy(x, y);  
		printf("%c",WALL);
		
		gotoxy(consoleWidth, y); 
		printf("%c",WALL);
	}
	
	y = 1;
	for (; x < consoleWidth + 1; x++)
	{
		gotoxy(x, y);  
		printf("%c",WALL);
		
		gotoxy(x, rectangleHeight); 
		printf("%c",WALL);
	}
	/*x = (consoleWidth+1)/3;
	for (y = (rectangleHeight) / 3; y < (2 * rectangleHeight) / 3; y++)
	{
		gotoxy(x, y);  
		printf("%c",WALL);
		
		gotoxy((consoleWidth) / 3, y); 
		printf("%c",WALL);
	}
	y = (rectangleHeight) / 3;
	
	for (x = (consoleWidth + 1) / 3; x < (2 * consoleWidth + 1) / 3; x++)
	{
		gotoxy(x, y);  
		printf("%c",WALL);
		
		gotoxy(x, (rectangleHeight) / 3); 
		printf("%c",WALL);
	}*/
	return;
}
void loadSnake(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength) {
	int i;
	for (i = 0; i < snakeLength; i++)
	{
		gotoxy(snakeXY[0][i], snakeXY[1][i]);
		printf("%c", SNAKE_BODY); 
	}
	
	return;
}
void prepairSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength) {
	int i, x;
	int snakeX = snakeXY[0][0];
	int snakeY = snakeXY[1][0];
	for(i = 1; i <= snakeLength; i++)
	{
		snakeXY[0][i] = snakeX + i;
		snakeXY[1][i] = snakeY;
	}
	
	return;
}
void loadGame(void) {
	int snakeXY[2][SNAKE_ARRAY_SIZE];   /*two dimensional array*/
	int snakeLength = 4;		    /*initial lenght*/
	int direction = LEFT_ARROW;	    /*initial direction*/
	int foodXY[] = {5,5};
	int score = 0;
	int consoleWidth = 80;
	int consoleHeight = 25;
	int speed = getGameSpeed();
	snakeXY[0][0] = 40;     /*starting position of the snake*/
	snakeXY[1][0] = 10;
	
	loadEnviroment(consoleWidth, consoleHeight); /*borders*/
	prepairSnakeArray(snakeXY, snakeLength);
	loadSnake(snakeXY, snakeLength);
	
	refreshInfoBar(score, speed); /*Bottom info bar. Score, Level etc*/
	startGame(snakeXY, foodXY, consoleWidth, consoleHeight, snakeLength, direction, score, speed);

	return;
}

int getGameSpeed(void){
	int speed;
	clrscr();
	
	do
	{
		gotoxy(10,5);
		printf("Select The game speed between 1 and 9.");
		speed = waitForAnyKey()-48;
	} while(speed < 1 || speed > 9);
	return(speed);
}

int collisionSnake (int x, int y, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int detect) {
	int i;
	for (i = detect; i < snakeLength; i++) //Checks if the snake collided with itself
	{
		if ( x == snakeXY[0][i] && y == snakeXY[1][i])
			return(1);
	}
	return(0);
}

void moveSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction) {
	int i;
	for( i = snakeLength-1; i >= 1; i-- )
	{
		snakeXY[0][i] = snakeXY[0][i-1];
		snakeXY[1][i] = snakeXY[1][i-1];
	}	
	
	/*
	because we dont actually know the new snakes head x y, 
	we have to check the direction and add or take from it depending on the direction.
	*/
	switch(direction)
	{
		case DOWN_ARROW:
			snakeXY[1][0]++;
			break;
		case RIGHT_ARROW:
			snakeXY[0][0]++;
			break;
		case UP_ARROW:
			snakeXY[1][0]--;
			break;
		case LEFT_ARROW:
			snakeXY[0][0]--;
			break;			
	}
	
	return;
}

int collisionDetection(int snakeXY[][SNAKE_ARRAY_SIZE], int consoleWidth, int consoleHeight, int snakeLength ) {
	int colision = 0;
	if ((snakeXY[0][0] == 1) || (snakeXY[1][0] == 1) || (snakeXY[0][0] == consoleWidth) || (snakeXY[1][0] == consoleHeight - 4)) //Checks if the snake collided wit the wall or it's self
		colision = 1;
	else
		if (collisionSnake(snakeXY[0][0], snakeXY[1][0], snakeXY, snakeLength, 1)) //If the snake collided with the wall, theres no point in checking if it collided with itself.
			colision = 1;
			
	return(colision);
}
void refreshInfoBar(int score, int speed) {
	gotoxy(5,23);
	printf("Score: %d", score);
	
	gotoxy(5,24);
	printf("Speed: %d", speed);

	gotoxy(52,23);
	printf("Coder: Amoli Kotalwar");

}

void youWinScreen(void) {
	int x = 6, y = 7;
	gotoxy(x,y++);
	printf("'##:::'##::'#######::'##::::'##::::'##:::::'##:'####:'##::: ##:'####:");
	gotoxy(x,y++);
	printf(". ##:'##::'##.... ##: ##:::: ##:::: ##:'##: ##:. ##:: ###:: ##: ####:");
	gotoxy(x,y++);
	printf(":. ####::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ####: ##: ####:");
	gotoxy(x,y++);
	printf("::. ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ## ## ##:: ##::");
	gotoxy(x,y++);
	printf("::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##. ####::..:::");
	gotoxy(x,y++);
	printf("::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##:. ###:'####:");
	gotoxy(x,y++);
	printf("::: ##::::. #######::. #######:::::. ###. ###::'####: ##::. ##: ####:");
	gotoxy(x,y++);
	printf(":::..::::::.......::::.......:::::::...::...:::....::..::::..::....::");
	gotoxy(x,y++);	
	
	waitForAnyKey();
	clrscr(); /*clear the console*/
	return;
}
void gameOverScreen(void) {
	int x = 17, y = 3;
	
	
	
	gotoxy(x,y++);
	printf(":'######::::::'###::::'##::::'##:'########:\n");
	gotoxy(x,y++);
	printf("'##... ##::::'## ##::: ###::'###: ##.....::\n");
	gotoxy(x,y++);
	printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::\n");
	gotoxy(x,y++);
	printf(" ##::'####:'##:::. ##: ## ### ##: ######:::\n");
	gotoxy(x,y++);
	printf(" ##::: ##:: #########: ##. #: ##: ##...::::\n");
	gotoxy(x,y++);
	printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::\n");
	gotoxy(x,y++);
	printf(". ######::: ##:::: ##: ##:::: ##: ########:\n");
	gotoxy(x,y++);
	printf(":......::::..:::::..::..:::::..::........::\n");
	gotoxy(x,y++);
	printf(":'#######::'##::::'##:'########:'########::'####:\n");
	gotoxy(x,y++);
	printf("'##.... ##: ##:::: ##: ##.....:: ##.... ##: ####:\n");
	gotoxy(x,y++);
	printf(" ##:::: ##: ##:::: ##: ##::::::: ##:::: ##: ####:\n");
	gotoxy(x,y++);
	printf(" ##:::: ##: ##:::: ##: ######::: ########::: ##::\n");
	gotoxy(x,y++);
	printf(" ##:::: ##:. ##:: ##:: ##...:::: ##.. ##::::..:::\n");
	gotoxy(x,y++);
	printf(" ##:::: ##::. ## ##::: ##::::::: ##::. ##::'####:\n");
	gotoxy(x,y++);
	printf(". #######::::. ###:::: ########: ##:::. ##: ####:\n");
	gotoxy(x,y++);
	printf(":.......::::::...:::::........::..:::::..::....::\n");
		waitForAnyKey();
	clrscr(); /*clear the console*/
	return;
}

void welcomeArt(void) {
	clrscr(); 
	
	printf("\n");	
	printf("\t\t    _________         _________ 			\n");	
	printf("\t\t   /         \\       /         \\ 			\n");	
	printf("\t\t  /  /~~~~~\\  \\     /  /~~~~~\\  \\ 			\n");	
	printf("\t\t  |  |     |  |     |  |     |  | 			\n");		
	printf("\t\t  |  |     |  |     |  |     |  | 			\n");
	printf("\t\t  |  |     |  |     |  |     |  |         /	\n");
	printf("\t\t  |  |     |  |     |  |     |  |       //	\n");
	printf("\t\t (o  o)    \\  \\_____/  /     \\  \\_____/ / 	\n");
	printf("\t\t  \\__/      \\         /       \\        / 	\n");
	printf("\t\t    |        ~~~~~~~~~         ~~~~~~~~ 		\n");
	printf("\t\t    ^											\n");
	printf("\t		Welcome To The Snake Game!			\n");
	printf("\t			    Press Any Key To Continue...	\n");			
	printf("\n");
	
	waitForAnyKey();
	return;
}



void exitYN(void) {
	char pressed;
	gotoxy(9,8);
	printf("Are you sure you want to exit(Y/N)\n");
	if (pressed == 'y')
	{
		clrscr(); /*clear the console*/
		exit(1);
	}
	return;
}

void gotoxy(int x,int y) {
	printf("%c[%d;%df",0x1B,y,x);
}
int kbhit(void);
char getch() {
	char c;
	system("stty raw");
	c= getchar();
	system("stty sane");
	
	return(c);
}
void clrscr() {
	system("clear");
		return;
}








