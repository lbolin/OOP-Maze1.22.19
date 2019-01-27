//Lauren Bolin
#pragma once
#include <iostream>
#include <Windows.h>
#include <stack>

using namespace std;
const int WIDTH = 11;
const int HEIGHT = 11;

class Maze
{
public:
	Maze();
	~Maze();
	void playGame();

private:
	void display();
	void fillWall();
	void makeMaze();
	void getoddRand();
	bool validMove();
	bool isAvaliable(COORD) const;
	bool isBorder(COORD) const;
	bool isWall(COORD) const;
	void digPath();
	
	bool isSolved();
	int getKey();
	char MazeA[HEIGHT][WIDTH];

	stack<COORD> MazeStack;
	COORD Start;
	COORD End;
    COORD Current;
	COORD Player;
};



