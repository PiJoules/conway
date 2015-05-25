#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int getNeighborCount(int x, int y, int width, int height, int* board);
void printBoard(int* board, int width, int height);
int isEmpty(int* board, int width, int height);

int main(){
	cout << "\n";

	/* Read from stdin */
    char *line = NULL;
	int width, height;
	scanf("%d %d", &width, &height);
	while (getchar() != '\n'); // kill remaining line
	int board[height][width];
	int nextBoard[height][width];
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			board[y][x] = 0;
		}
	}

	int x,y;
	while (scanf("%d %d", &x, &y) > 0) {
		board[y][x] = 1;
    }

	printBoard((int*)board, width, height);

	while (!isEmpty((int*)board, width, height)){
		/*
		1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
		2. Any live cell with two or three live neighbours lives on to the next generation.
		3. Any live cell with more than three live neighbours dies, as if by overcrowding.
		4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
		*/
		for (int y = 0; y < height; y++){
			for (int x = 0; x < width; x++){
				int neightborCount = getNeighborCount(x,y,width,height,(int*)board);
				if (board[y][x] == 1){
					// Rule 1 || Rule 3
					if (neightborCount < 2 || neightborCount > 3){
						nextBoard[y][x] = 0;
					}
					// Rule 2
					else {
						nextBoard[y][x] = 1;
					}
				}
				else {
					// Rule 4
					if (neightborCount == 3){
						nextBoard[y][x] = 1;
					}
					// Continue being dead
					else {
						nextBoard[y][x] = 0;
					}
				}
			}
		}

		for (int y = 0; y < height; y++){
			for (int x = 0; x < width; x++){
				board[y][x] = nextBoard[y][x];
			}
		}

		printBoard((int*)board, width, height);

	}
	
	cout << "\n";
}

int getNeighborCount(int x, int y, int width, int height, int* board){
	int count = 0;

	int leftX = x-1;
	int rightX = x+1;
	int aboveY = y-1;
	int belowY = y+1;

	if (leftX < 0)
		leftX = 0;
	if (rightX > width-1)
		rightX = width-1;
	if (aboveY < 0)
		aboveY = 0;
	if (belowY > height-1)
		belowY = height-1;

	for (int checkY = aboveY; checkY <= belowY; checkY++){
		for (int checkX = leftX; checkX <= rightX; checkX++){
			if ( *((board + checkY*width) + checkX) == 1 && !(checkX == x && checkY == y) ){
				count++;
			}
		}
	}

	return count;
}

void printBoard(int* board, int width, int height){
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			cout << *((board + y*width) + x);
		}
		cout << "\n";
	}
	cout << "\n\n";
	usleep(1000000);
}

int isEmpty(int* board, int width, int height){
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if ( *((board + y*width) + x) == 1 ){
				return 0;
			}
		}
	}	
	return 1;
}