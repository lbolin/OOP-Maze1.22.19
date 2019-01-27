//Lauren Bolin
#include "Maze.h"
#include <time.h>

using namespace std;

const char WALL = (char) 219;
const char PATH = (char)32;
const char START = 'S';
const char DESTINATION = 'X';


Maze::Maze() {
	fillWall();
	makeMaze();
	display();
}

Maze::~Maze() {

}

void Maze::fillWall()
{
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			MazeA[row][column] = WALL;
		}
	}
}

void Maze::display()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			cout << MazeA[row][column];
		}
		cout<<endl;
	}
}

void Maze::getoddRand()
{
	int row = 0;
	int column = 0;

	srand(time(NULL));
	row = rand() % (HEIGHT - 1);
	column = rand() % (WIDTH - 1);
	
	while (row % 2 == 0) {
		row = rand() % (HEIGHT - 1);
	}

	while (column % 2 == 0) {
		column = rand() % (WIDTH - 1);
	}

	Current.X = column;
	Current.Y = row;

	Start = Current;

}

bool Maze::validMove()
{
	COORD tempLocation = Current;
	bool Valid = false;

	//North
	tempLocation.Y -= 2;
	if ((isAvaliable(tempLocation)) && !(tempLocation.Y <= 0))
	{
		Valid =true;
	}

	//South
	tempLocation.Y += 4;
	if ((isAvaliable(tempLocation)) && !(tempLocation.Y >= HEIGHT - 1 ))
	{
		Valid = true;
	}

	tempLocation.Y -= 2;
	//West
	tempLocation.X -= 2;
	if ((isAvaliable(tempLocation)) && !(tempLocation.X <= 0))
	{
		Valid = true;
	}

	//East
	tempLocation.X += 4;
	if ((isAvaliable(tempLocation)) && !(tempLocation.X >= WIDTH - 1))
	{
		Valid = true;
	}

	return Valid;
}

bool Maze::isAvaliable(COORD location) const
{
	bool Avaliable = false;

		if (!isBorder(location) && isWall(location))
		{
			Avaliable = true;
		}

	return Avaliable;
}

bool Maze::isBorder(COORD location) const
{
	return (location.Y <= 0 || location.Y >= HEIGHT - 1 || location.X <= 0 || location.X >= WIDTH - 1);
}

bool Maze::isWall(COORD location) const
{
	bool wallFound = true;

	if (MazeA[location.Y][location.X] != WALL)
	{
		wallFound = false;
	}
	return wallFound;
}

void Maze::digPath()
{
	int randNum;
	bool northFail = false;
	bool southFail = false;
	bool eastFail = false;
	bool westFail = false;
	bool didMove;
	do {

		didMove = false;
		randNum = rand() % 4;
		//display();

		switch (randNum)
		{
			//North 0
		case 0:
			if (MazeA[Current.Y - 2][Current.X] == WALL && Current.Y - 2 > 0)
			{
				MazeA[Current.Y - 1][Current.X] = PATH;
				MazeA[Current.Y - 2][Current.X] = PATH;
				Current.Y = Current.Y - 2;
				didMove = true;
			}
			else
			{
				northFail = true;
			}
			break;
			//South 1
		case 1:
			if (MazeA[Current.Y + 2][Current.X] == WALL && Current.Y + 2 < HEIGHT - 1)
			{
				MazeA[Current.Y + 1][Current.X] = PATH;
				MazeA[Current.Y + 2][Current.X] = PATH;
				Current.Y = Current.Y + 2;
				didMove = true;
			}
			else
			{
				southFail = true;
			}
			break;
			//East  2
		case 2:
			if (MazeA[Current.Y][Current.X + 2] == WALL && Current.X + 2 < WIDTH - 1)
			{
				MazeA[Current.Y][Current.X + 1] = PATH;
				MazeA[Current.Y][Current.X + 2] = PATH;
				Current.X = Current.X + 2;
				didMove = true;
			}
			else
			{
				eastFail = true;
			}
			break;
			//West  3
		case 3:
			if (MazeA[Current.Y][Current.X - 2] == WALL && Current.X - 2 > 0)
			{
				MazeA[Current.Y][Current.X - 1] = PATH;
				MazeA[Current.Y][Current.X - 2] = PATH;
				Current.X = Current.X - 2;
				didMove = true;
			}
			else
			{
				westFail = true;
			}
			break;
		}
		if (northFail && southFail && eastFail && westFail)
		{
			break;
		}
	} while (!didMove);
}

void Maze::makeMaze()
{
	getoddRand();

	do {
		
		if (validMove())
		{
			MazeStack.push(Current);

			digPath();
		}
		else
		{
			if (!MazeStack.empty())
			{
				Current = MazeStack.top();
				MazeStack.pop();
			}
		}
	} while (!MazeStack.empty());

	End.Y = rand() % (HEIGHT - 1);
	End.X = rand() % (WIDTH - 1);

	while (MazeA[End.Y][End.X] != PATH)
	{
		End.Y = rand() % (HEIGHT - 1);
		End.X = rand() % (WIDTH - 1);
	}
	MazeA[Start.Y][Start.X] = START;
	MazeA[End.Y][End.X] = DESTINATION;

	
}
bool Maze::isSolved()
{
	return(MazeA[Player.Y][Player.X] == DESTINATION);
}
void Maze::playGame()
{
	Player = Start;

	while (!isSolved())
	{
		int keyPressed = getKey();

		COORD oldCoord = { Player.X,Player.Y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), oldCoord);

		if (MazeA[Player.Y][Player.X] == START)
		{
			cout << START;
		}
		else if (MazeA[Player.Y][Player.X] == '.')
		{
			cout << PATH;
		}
		else
		{
			cout << '.';
		}

		if ((keyPressed == VK_LEFT) && MazeA[Player.Y][Player.X - 1] != WALL)
		{
			Player.X--;

		}
		else if((keyPressed == VK_UP) && MazeA[Player.Y -1][Player.X] != WALL)
		{
			Player.Y--;

		}
		else if ((keyPressed == VK_RIGHT) && MazeA[Player.Y][Player.X + 1] != WALL)
		{
			Player.X++;

		}
		else if ((keyPressed == VK_DOWN) && MazeA[Player.Y + 1][Player.X] != WALL)
		{
			Player.Y++;

		}

		COORD newCoord = { Player.X,Player.Y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
		cout << 'P';
		
	}

	COORD GAMEOVERCOORD = { 0,HEIGHT + 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), GAMEOVERCOORD);


	cout << "GGGGGGGGG   AAAAAAAAA   MM           MM  EEEEEEEEE" << endl<<
	        "G          A         A  M M         M M  E" << endl<<
			"G          A         A  M  M       M  M  E"   << endl<<
			"G   GGGGG  AAAAAAAAAAA  M   M     M   M  EEEEEEEEE" << endl<<
			"G       G  A         A  M    M   M    M  E" << endl<<
			"G       G  A         A  M     M M     M  E" << endl<<
			"GGGGGGGGG  A         A  M      M      M  EEEEEEEEE" << endl<<endl;

	cout << "OOOOOOOOO  V            V  EEEEEEEEE  RRRRRRR" << endl<<
	        "O       O   V          V   E          R       R" << endl<<
            "O       O    V        V    E          R        R"<<endl<<
		    "O       O     V      V     EEEEEEEEE  RRRRRRRRR"<<endl<<
		    "O       O      V    V      E          R      R  " << endl <<
		    "O       O       V  V       E          R       R" << endl <<
		    "OOOOOOOOO        VV        EEEEEEEEE  R        R" << endl<<endl<<endl;		
}

int Maze::getKey()
{
	int result = 0;
	while (!isSolved() && result == 0)
	{
		short MAX_SHORT = 0x7FFF; //111111111111111
		if (GetAsyncKeyState(VK_LEFT) & MAX_SHORT) {
			result = VK_LEFT;
		}
		else if (GetAsyncKeyState(VK_UP) & MAX_SHORT) {
			result = VK_UP;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & MAX_SHORT) {
			result = VK_RIGHT;
		}
		else if (GetAsyncKeyState(VK_DOWN) & MAX_SHORT) {
			result = VK_DOWN;
		}
	}
	return result;
}
