#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <windows.h>

using namespace std;

#define cls system("cls");

const int ROWS = 19;
const int COLS = 19;
int posX = 1, posY = 0; 
int endX = 17, endY = 18;
unsigned char player = {1};
unsigned char action;

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x*2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMaze(const unsigned char maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
			gotoxy(j,i);
            std::cout << maze[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

unsigned char maze[ROWS][COLS] = {
    { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}, 
	{ 'S',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'}, 
	{ '#',' ','#',' ','#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#'}, 
	{ '#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'}, 
	{ '#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#','#','#','#','#'}, 
	{ '#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#'}, 
	{ '#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'}, 
	{ '#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#'}, 
	{ '#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#'}, 
	{ '#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#'}, 
	{ '#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#'}, 
	{ '#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#'}, 
	{ '#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#'}, 
	{ '#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#'}, 
	{ '#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#'}, 
	{ '#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#'}, 
	{ '#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#'}, 
	{ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','E'},
	{ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
};

void playermove(int prevposY, int prevposX, int posY, int posX){
	unsigned char space = {32};
	maze[posX][posY] = player;
	gotoxy(prevposY,prevposX);
	cout << space;
	gotoxy(posY, posX);
	cout << player;
}

void playerAction(){
	char move = _getch();
	int prevposX = posX;
	int prevposY = posY;
	
	switch(move){
		case 'w':
			if(maze[posX-1][posY] != '#' && maze[posX][posX] != 'S'){
				posX--;
				playermove(prevposY,prevposX, posY, posX);
			}
			break;
		case 's':
			if(maze[posX+1][posY] != '#' && maze[posX][posX] != 'S'){
				posX++;
				playermove(prevposY,prevposX, posY, posX);
			}
			break;
		case 'a':
			if(maze[posX][posY-1] != '#' && maze[posX][posX] != 'S'){
				posY--;
				playermove(prevposY,prevposX, posY, posX);
			}
			break;
		case 'd':
			if(maze[posX][posY+1] != '#' && maze[posX][posX] != 'S'){
				posY++;
				playermove(prevposY,prevposX, posY, posX);
			}
			break;
	}
}


int main() {
	cls;
	cout << "control WASD" << endl;
	cout << endl;
	printMaze(maze);
	while (action != 'Q' || 'q')
	{
		playerAction();
		if(maze[posX][posY] == maze[endX][endY]){
			cout << " YOU WIN :)";
		}
	}

    return 0;
}




