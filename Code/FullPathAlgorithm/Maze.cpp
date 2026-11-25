#include "Maze.h"

Maze::Maze()
{
	MAZE_HEIGHT = 20;
	MAZE_WIDTH = 20;
	CX2 = MAZE_WIDTH - 2;
	CY2 = MAZE_HEIGHT - 2;
	initialize_maze();
}

Maze::Maze(int height, int width)
{
	MAZE_HEIGHT = height;
	MAZE_WIDTH = width;
	CX2 = MAZE_WIDTH - 2;
	CY2 = MAZE_HEIGHT - 2;
	initialize_maze();
}

void Maze::set_dimensions(int height, int width)
{
	MAZE_HEIGHT = height;
	MAZE_WIDTH = width;
	CX2 = MAZE_WIDTH - 2;
	CY2 = MAZE_HEIGHT - 2;
	initialize_maze();
}


void Maze::initialize_maze()
{

	int X = 0, Y = 0;

	while (Y != MAZE_HEIGHT) {
		if (Y == 0 || Y == (MAZE_HEIGHT - 1)) {
			while (X != MAZE_WIDTH) {
				maze[Y][X] = 'X';
				X++;
			}
			X = 0;
			Y++;
			continue;
		}
		else {
			while (X != MAZE_WIDTH) {
				maze[Y][X] = '.';
				X++;
			}
			maze[Y][0] = 'X';
			maze[Y][MAZE_WIDTH - 1] = 'X';
			X = 0;
			Y++;
		}

	}
}


void Maze::print()
{
	int Y = 0; int X = 0;

	std::cout << "\x1B[2J\x1B[H";

	while (Y != MAZE_HEIGHT) {
		while (X != MAZE_WIDTH) {
			std::cout << maze[Y][X];
			X++;
			
		}
		std::cout << std::endl;
		X = 0;
		Y++;
	}
	std::cout << std::endl;
}


std::vector<std::vector<char>> Maze::convertMazeToVector()
{
	std::vector<std::vector<char>> convertedMaze;
	std::vector<char> row;

	for (int i = 0; i < MAZE_HEIGHT; i++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			row.push_back(maze[i][x]);
		}
		convertedMaze.push_back(row);
		row.clear();
	}
	
	return convertedMaze;
}


void Maze::generate_maze()
{
	//srand(time(NULL));
	int Slice_height = (CY2 - CY1) + 1;
	int Slice_width = (CX2 - CX1) + 1;

	if (Slice_height <= 2 || Slice_width <= 2) {
		return;
	}

	if (Slice_height >= Slice_width) {

		int Y = get_random_position(CY1 + 1, CY2 - 1);
		draw(Y, CX1, 0);

		int new_Y1 = Y - 1;
		int new_Y2 = Y;

		get_next_corner(new_Y1, CX1, new_Y2, CX2, 'u');
		generate_maze(new_Y1, CX1, new_Y2, CX2);

		new_Y1 = Y;

		get_next_corner(new_Y1, CX1, CY2, CX2, 'd');
		generate_maze(new_Y1, CX1, CY2, CX2);

	}

	if (Slice_height < Slice_width) {
		int X = get_random_position(CX1 + 1, CX2 - 1);
		draw(CY2, X, 1);

		int new_X1 = CX1;
		int new_X2 = X;
		
		get_next_corner(CY1, new_X1, CY2, new_X2, 'l');
		generate_maze(CY1, new_X1, CY2, new_X2);

		new_X1 = X;
		new_X2 = X + 1;

		get_next_corner(CY1, new_X1, CY2, new_X2, 'r');
		generate_maze(CY1, new_X1, CY2, new_X2);
	}
	
	maze[1][1] = 'S';
	maze[get_random_num(1, MAZE_HEIGHT - 1)][get_random_num(1, MAZE_WIDTH - 1)] = 'F';
	print();
	
}


void Maze::generate_maze(int Y1, int X1, int Y2, int X2)
{
	int Slice_height = (Y2 - Y1) + 1;
	int Slice_width = (X2 - X1) + 1;

	if (Slice_height <= 2 || Slice_width <= 2) {
		return;
	}

	if (Slice_height >= Slice_width) {

		int Y = get_random_position(Y1 + 1, Y2 - 1);
		draw(Y, X1, 0);

		int new_Y1 = Y - 1;
		int new_Y2 = Y;

		get_next_corner(new_Y1, X1, new_Y2, X2, 'u');
		generate_maze(new_Y1, X1, new_Y2, X2);

		new_Y1 = Y;

		get_next_corner(new_Y1, X1, Y2, X2, 'd');
		generate_maze(new_Y1, X1, Y2, X2);

	}

	if (Slice_height < Slice_width) {
		int X = get_random_position(X1 + 1, X2 - 1);
		draw(Y2, X, 1);

		int new_X1 = X1;
		int new_X2 = X;

		get_next_corner(Y1, new_X1, Y2, new_X2, 'l');
		generate_maze(Y1, new_X1, Y2, new_X2);

		new_X1 = X;
		new_X2 = X + 1;

		get_next_corner(Y1, new_X1, Y2, new_X2, 'r');
		generate_maze(Y1, new_X1, Y2, new_X2);
	}
}


void Maze::draw(int Y, int X, int dir)
{
	int length = 0;
    int can_write = check_space(Y, X, dir);

	switch (dir) {
		case 0:
			while (can_write && X >= 1) {
				if (can_write == 2) {
					X--;
					maze[Y][X] = '.';
					break;
				}

				maze[Y][X] = 'X';
				X++;
				length++;
				can_write = check_space(Y, X, dir);
			}

			X = get_random_position((X - length), X);
			maze[Y][X] = '.';
			break;


		case 1:
			while (can_write && Y >= 1) {
				if (can_write == 2) {
					Y++;
					maze[Y][X] = '.';
					break;
				}

				maze[Y][X] = 'X';
				Y--;
				length++;
				can_write = check_space(Y, X, dir);

			}

			Y = get_random_position(Y, Y + length);
			maze[Y][X] = '.';
			break;

	}
}


void Maze::get_next_corner(int &Y1, int &X1, int &Y2, int &X2, char dir)
{
	switch (dir) {
		case 'u':
			while (check_space(Y1, X1, 1) && Y1 > 0) {
				--Y1;
			}
			Y1++;
			Y2--;
			break;

		case 'd':
			if (Y1 != (MAZE_HEIGHT - 2)) {
				Y1++;
				break;
			}

		case 'l':
			while (maze[Y1][X1] != 'X') {
				--X1;
			}
			X1++;
			X2--;
			break;

		case 'r':
			while (check_space(Y2, X2, 0)) {
				if (check_space(Y2, X2, 0 == 2)) {
					if (maze[Y2 + 1][X2] == 'X' && maze[Y2 - 1][X2] == 'X') {
						break;
					}
				}
				++X2;
			}
			X2--;
			X1++;
	}
}


int Maze::get_random_position(int min, int max)
{
	if ((max - min) == 2) {
		return (max - 1);
	}

	int rnd_num = (rand() % (max - min + 1)) + min;

	while ((rnd_num == min || rnd_num == max) || (rnd_num > max || rnd_num < min)) {
		if (min == max || (abs(min - max)) == 1) {
			return max;
			break;
		}
		rnd_num = (rand() % (max - min + 1)) + min;
	}

	if (rnd_num <= 0)
		return 1;

	else {

		return rnd_num;

	}
}

int Maze::get_random_num(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}


int Maze::check_space(int Y, int X, int dir)
{
	char up = maze[Y - 1][X];
	char down = maze[Y + 1][X];
	char left = maze[Y][X - 1];
	char right = maze[Y][X + 1];
	char cur_pos = maze[Y][X];


	if (Y <= 0 || Y >= (MAZE_HEIGHT - 1)) {
		return false;
	}

	if (X <= 0 || X >= (MAZE_WIDTH - 1)) {
		return false;
	}

	switch (dir) {
	case 0:
		if ((up == 'X' || down == 'X') && cur_pos == '.') {
			return 2;
		}

		if ((up == 'X' || down == 'X') || cur_pos == 'X') {
			return false;
		}

		if (cur_pos == '.') {
			return true;
		}

		break;

	case 1:
		if ((left == 'X' || right == 'X') && cur_pos == '.') {
			return 2;

		}
		if ((left == 'X' || right == 'X') || cur_pos == 'X') {
			return false;
		}

		if (cur_pos == '.') {
			return true;
		}

		break;
	}
}
