// pap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <queue>


class Apple {
public:
	Apple() {
		
	}
};

class BodyPart {
public:
	int x, y;
};

class Snake {
public:
	int direction = 6;
	int length = 1;
	Snake(int x_start, int y_start) {
		head = (BodyPart*)malloc(sizeof(BodyPart));
		head->x = x_start;
		head->y = y_start;

		parts.push_back(*head);
	}

	void Step() {

		BodyPart* newHead = (BodyPart*)malloc(sizeof(BodyPart));
		if (direction == 6) {
			newHead->x = head->x + 1;
			newHead->y = head->y;
		}
		else if (direction == 2) {
			newHead->x = head->x;
			newHead->y = head->y -1;
		}
		else if (direction == 4) {
			newHead->x = head->x - 1;
			newHead->y = head->y;
		}
		else {
			newHead->x = head->x;
			newHead->y = head->y + 1;
		}

		head = newHead;
		parts.push_back(*head);
		length += 1;
	}

	void Draw(char** grid) {
		for (int i = 0; i < length; i++) {
			int x = parts[i].x;
			int y = parts[i].y;
			grid[y][x] = 'o';
		}
	}

private:
	std::vector<BodyPart> parts;
	BodyPart* head;
};

class Game {
private:
	char** grid;

protected:
	int width, height;
	Snake* snake;

public:
	Game(int w, int h) {
		width = w;
		height = h;
		snake = new Snake(w/2, h/2);
		grid = (char**)malloc(h * sizeof(char*));

		for (int i = 0; i < h; i++) {
			grid[i] = (char*)malloc(w * sizeof(char));
			
			for (int j = 0; j < w; j++) {
				grid[i][j] = 'x';
			}
		}
	}

	void Step() {
		AdvanceState();
		Render();
		Draw();
	}

private:
	void AdvanceState() {
		snake->Step();
	}
	
	void Render() {
		ResetGrid();
		snake->Draw(grid);
	}

	void Draw() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << grid[i][j];
			}
			std::cout << "\n";
		}
	}

	void ResetGrid() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				grid[i][j] = 'x';
			}
		}
	}
};


int main()
{
	Game* g = new Game(10, 5);
	std::string input;

	while (std::cin) {
		std::getline(std::cin, input);
		system("CLS");
		
		g->Step();
	}


    return 0;
}





