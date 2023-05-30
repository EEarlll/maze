#include <iostream>
#include <conio.h>
#include <stack>

using namespace std;

// Maze dimensions
const int ROWS = 20;
const int COLS = 20;

// Maze structure
char maze[ROWS][COLS] = {
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

// Player position
int playerX = 1;
int playerY = 0;

// Stack to store player's path
stack<pair<int, int>> pathStack;

// Function to print the maze
void printMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == playerX && j == playerY) {
                cout << 'P' << " "; // Player position
            } else {
                cout << maze[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Function to check if the move is valid
bool isValidMove(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != '#');
}

// Function to move the player
void movePlayer(int x, int y) {
    maze[playerX][playerY] = ' '; // Clear the previous player position
    playerX = x;
    playerY = y;
    pathStack.push(make_pair(playerX, playerY));
    maze[playerX][playerY] = 'P'; // Update the new player position
}

int main() {
    cout << "Maze Game with Stacks" << endl;
    cout << "---------------------" << endl;

    cout << "Legend:" << endl;
    cout << "S: Start point" << endl;
    cout << "E: Exit point" << endl;
    cout << "#: Walls" << endl;
    cout << "P: Player" << endl;
    cout << "Blank spaces: Valid paths" << endl;

    cout << endl;
    printMaze();
    cout << endl;

    pathStack.push(make_pair(playerX, playerY)); // Push the start position to the stack

    char move;
    while (true) {
        move = getch();

        // Handle arrow key movements
        switch (move) {
            case 72: // Up arrow
                if (isValidMove(playerX - 1, playerY)) {
                    movePlayer(playerX - 1, playerY);
                }
                break;
            case 80: // Down arrow
                if (isValidMove(playerX + 1, playerY)) {
                    movePlayer(playerX + 1, playerY);
                }
                break;
            case 75: // Left arrow
                if (isValidMove(playerX, playerY - 1)) {
                    movePlayer(playerX, playerY - 1);
                }
                break;
            case 77: // Right arrow
                if (isValidMove(playerX, playerY + 1)) {
                    movePlayer(playerX, playerY + 1);
                }
                break;
            case 8: // Backspace key
                if (!pathStack.empty()) {
                    pathStack.pop(); // Remove the current position from the stack
                    if (!pathStack.empty()) {
                        pair<int, int> previousPos = pathStack.top();
                        movePlayer(previousPos.first, previousPos.second); // Move back to the previous position
                    }
                }
                break;
        }

        system("CLS"); // Clear the console screen
        printMaze();
        cout << endl;

        // Check if the player reached the exit point
        if (maze[playerX][playerY] == 'E') {
            cout << "Congratulations! You reached the exit." << endl;
            break;
        }
    }

    return 0;
}
