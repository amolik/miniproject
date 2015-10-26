#define SNAKE_ARRAY_SIZE 310

int snakeXY[][SNAKE_ARRAY_SIZE];
int foodXY[];

void gotoxy(int x,int y);
//int kbhit(void);
char getch();
void clrscr();
//char waitForAnyKey(void);
int getGameSpeed(void);
//void pauseMenu(void);
//int checkKeysPressed(int direction);
int collisionSnake (int x, int y, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int detect);
//int generateFood(int foodXY[], int width, int height, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength);
void moveSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction);
//void move(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction);
//int eatFood(int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[]);
int collisionDetection(int snakeXY[][SNAKE_ARRAY_SIZE], int consoleWidth, int consoleHeight, int snakeLength );
void refreshInfoBar(int score, int speed);
//void createHighScores(void);
//int getLowestScore();
//void inputScore(int score);
//void displayHighScores(void);
void youWinScreen(void);
void gameOverScreen(void);
void startGame( int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[], int consoleWidth, int consoleHeight, int snakeLength, int direction, int score, int speed);
void loadEnviroment(int consoleWidth, int consoleHeight);
void loadSnake(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength);
void prepairSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength);
void loadGame(void);
//int menuSelector(int x, int y, int yStart);
void welcomeArt(void);
//void controls(void);
//void exitYN(void);
//int mainMenu(void);


