// header files
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <windows.h>
using namespace std;

// Used for clearing console and changing color
#define cls system("cls");
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Initializes properties of maze and player
const int ROWS = 19;
const int COLS = 19;
int posX = 1, posY = 0;
int endX = 17, endY = 18;
unsigned char player = 'P';

// Stack to store player's previous and current moves
stack<pair<int, int>> playerMoves;
stack<pair<int, int>> PrevplayerMoves;

// move the cursor
void gotoxy(int x, int y)
{
	// Get the X,Y of the cursor of console
	COORD coord;
	// Aligns the cursor to the column
	coord.X = x * 2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to print the maze
void printMaze(const unsigned char maze[ROWS][COLS])
{
	// Set the console text color 9 is blue
	SetConsoleTextAttribute(hConsole, 9);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);

			std::cout << maze[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	// Reset the console text color to default 15 is default
	SetConsoleTextAttribute(hConsole, 15);

	// Instruction
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\nMaze Game with Stacks" << endl;
	cout << "---------------------" << endl;

	cout << "Legend:" << endl;
	cout << "S: Start point" << endl;
	cout << "E: Exit point" << endl;
	cout << "#: Walls" << endl;
	cout << "P: Player" << endl;
	cout << "Blank spaces: Valid paths" << endl;
	SetConsoleTextAttribute(hConsole, 15);
}

// Initializes Maze
unsigned char maze[ROWS][COLS] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'S', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#'},
	{'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'E'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

// function to move the player
void playermove(int prevposY, int prevposX, int posY, int posX)
{
	// Using 2 gotoxy function to clear the prev moves & move the player
	unsigned char space = {32};
	maze[posX][posY] = player;

	// Set the console text color 14 is yellow
	SetConsoleTextAttribute(hConsole, 14);

	gotoxy(prevposY, prevposX);
	cout << space;
	gotoxy(posY, posX);
	cout << player;

	// Reset the console text color to default 15 is default
	SetConsoleTextAttribute(hConsole, 15);
}

void playerAction()
{
	//  reads input without waiting to press the Enter key.
	char move = _getch();

	// store the current position before moving.
	int prevposX = posX;
	int prevposY = posY;

	// update player position and push the stacks for backtracking
	switch (move)
	{
	case 'w':
		if (maze[posX - 1][posY] != '#' && maze[posX][posX] != 'S')
		{
			posX--;
			playerMoves.push({prevposX, prevposY});
			PrevplayerMoves.push({posX, posY});
			playermove(prevposY, prevposX, posY, posX);
		}
		break;
	case 's':
		if (maze[posX + 1][posY] != '#' && maze[posX][posX] != 'S')
		{
			posX++;
			playerMoves.push({prevposX, prevposY});
			PrevplayerMoves.push({posX, posY});
			playermove(prevposY, prevposX, posY, posX);
		}
		break;
	case 'a':
		if (maze[posX][posY - 1] != '#' && maze[posX][posX] != 'S')
		{
			posY--;
			playerMoves.push({prevposX, prevposY});
			PrevplayerMoves.push({posX, posY});
			playermove(prevposY, prevposX, posY, posX);
		}
		break;
	case 'd':
		if (maze[posX][posY + 1] != '#' && maze[posX][posX] != 'S')
		{
			posY++;
			playerMoves.push({prevposX, prevposY});
			PrevplayerMoves.push({posX, posY});
			playermove(prevposY, prevposX, posY, posX);
		}
		break;
	}
}

int main()
{
	cls;
	printMaze(maze);

	while (true)
	{
		playerAction();
		// Check if the player reaches the end
		if (maze[posX][posY] == maze[endX][endY])
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "You win";
			SetConsoleTextAttribute(hConsole, 15);
			break;
		}
	}

	// backtrack the player's move
	while (!playerMoves.empty())
	{
		// get the top of the position and the previous
		pair<int, int> pos = playerMoves.top();
		pair<int, int> prevPos = PrevplayerMoves.top();

		// backtrack to the stack
		playerMoves.pop();
		PrevplayerMoves.pop();

		// move the player using the top of the stack
		playermove(prevPos.second, prevPos.first, pos.second, pos.first);

		// Delay for animation
		Sleep(100);
	}
	cls;

	return 0;
}
