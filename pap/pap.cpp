// pap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <queue>
#include <Windows.h>
#include <conio.h>
#include <random>


class Apple {
public:
	int x, y;
	Apple(int x_start, int y_start) {
		x = x_start;
		y = y_start;
	}

	void Step(bool eatingApple, int w, int h) {
		if (eatingApple) {
			x = rand() % w;
			y = rand() % h;
		}
	}

	void Draw(char** grid) {
		grid[y][x] = '@';
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

	void SetDirection(int newDir) {
		direction = newDir;
	}

	BodyPart* GetHead() {
		return head;
	}

	void Step(bool ateApple) {

		BodyPart* newHead = (BodyPart*)malloc(sizeof(BodyPart));
		if (direction == 6) {
			newHead->x = head->x + 1;
			newHead->y = head->y;
		}
		else if (direction == 2) {
			newHead->x = head->x;
			newHead->y = head->y+1;
		}
		else if (direction == 4) {
			newHead->x = head->x - 1;
			newHead->y = head->y;
		}
		else {
			newHead->x = head->x;
			newHead->y = head->y - 1;
		}

		head = newHead;
		parts.push_back(*head);
		
		if (ateApple) {
			length += 1;
		}
		else {
			std::_Vector_iterator<std::_Vector_val<std::_Simple_types<BodyPart>>> it =  parts.end();
			parts.erase(parts.begin());
		}
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
	int width, height;
	Snake* snake;
	Apple* apple;

public:
	Game(int w, int h) {
		width = w;
		height = h;
		snake = new Snake(w/2, h/2);
		apple = new Apple(w / 2 + w / 4, h / 2 + h / 4);
		grid = (char**)malloc(h * sizeof(char*));

		for (int i = 0; i < h; i++) {
			grid[i] = (char*)malloc(w * sizeof(char));
			
			for (int j = 0; j < w; j++) {
				grid[i][j] = '.';
			}
		}
	}

	void SetDirection(int direction) {
		snake->SetDirection(direction);
	}

	void Step() {
		AdvanceState();
		Render();
		Draw();
	}

private:
	void AdvanceState() {
		if (CheckDeath()) {
			return;
		}

		bool eatingApple = AppleCollision();
		apple->Step(eatingApple, width, height);
		snake->Step(eatingApple);
	}
	
	void Render() {
		ResetGrid();
		snake->Draw(grid);
		apple->Draw(grid);
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
				grid[i][j] = '.';
			}
		}
	}

	bool CheckDeath() {
		BodyPart* head = snake->GetHead();
		int hx = head->x;
		int hy = head->y;

		if (hx > width || hx < 0 || hy > height || hy < 0)
			return true;
		

		return false;
	}

	bool AppleCollision() {
		BodyPart* head = snake->GetHead();
		return head->x == apple->x && head->y == apple->y;
	}
};


int main()
{
	Game* g = new Game(30, 10);
	std::string input;
	int dir;
	while (std::cin) {
		dir = _getch() - 48;
		//std::cin >> dir;
		//std::cin.ignore();
		//std::getline(std::cin, input);

		g->SetDirection(dir);
		system("CLS");
		
		g->Step();
	}


    return 0;
}





