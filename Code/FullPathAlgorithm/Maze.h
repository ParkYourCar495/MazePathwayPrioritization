#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

class Maze {
public:
	Maze();
	Maze(int height, int width);
	void set_dimensions(int height, int width);
	void generate_maze();
	void initialize_maze();
	void print();
	std::vector<std::vector<char>> convertMazeToVector();

private:
	int MAZE_HEIGHT;
	int MAZE_WIDTH;
	int CX1 = 1, CY1 = 1, CX2 = 0, CY2 = 0;
	char maze[200][200];
	void get_next_corner(int& Y1, int& X1, int& Y2, int& X2, char dir);
	int get_random_position(int min, int max);
	int get_random_num(int min, int max);
	int check_space(int Y, int X, int dir);
	void generate_maze(int Y1, int X1, int Y2, int X2);
	void draw(int Y, int X, int dir);	
};
