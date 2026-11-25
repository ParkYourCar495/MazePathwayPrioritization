#include "Visualizer.h"

Visualizer::Visualizer()
{
	Maze = nullptr;
	maze_height = 0;
	maze_width = 0;
	y_pos = 0;
	x_pos = 0;
	frameStart = 0;
	rounds = 0;
	process_message = "Processing |";
	status = true;
}

void Visualizer::setMaze(std::vector<std::vector<char>>* maze)
{
	Maze = maze;
	maze_height = Maze->size();
	maze_width = Maze->at(0).size();

}

void Visualizer::setPosition(int y, int x)
{
	y_pos = y;
	x_pos = x;
}

void Visualizer::drawStatusBar()
{
	if (!status) {
		return;
	}
	
	std::cout << std::endl;

	if (rounds >= 75) {
		if (process_message.length() >= 20) {
			process_message = "Processing |";
		
			//Clear line to reset Fake Status bar
			std::cout << "\033[2K";
		}

		else {
			process_message += "-";
			rounds = 0;
		}
	}
	
	std::cout << process_message;

}

void Visualizer::begin()
{
	frameStart = 1;
	process_message = "Processing |";
}

void Visualizer::end()
{
	frameStart = 0;
	process_message = "Processing |--------|";
	rounds = 0;
	//Show Cursor, Clear Line, Move Cursor To 1st Column
	std::cout << "\033[?25h\033[2K\033[1G";
	std::cout << process_message << std::endl;
}

void Visualizer::PrintMaze()
{

	if (frameStart == 1) {
		//Clear Screen
		std::cout << "\033[2J\033[3J\033[H";

		//Hide Cursor
		std::cout << "\x1b[?25l";
		frameStart = 0;
	}
	
	//Move cursor back to start
	std::cout << "\033[H";
	
	//Keeps track of of drawn frames
	rounds++;
	
	for (int i = 0; i < maze_height; i++) {
		for (int x = 0; x < maze_width; x++) {

			if (i == y_pos && x == x_pos) {
				std::cout << 'P';
			}
			else {
				std::cout << Maze->at(i).at(x);
			}
			
		}
		std::cout << std::endl;
	}
	
	drawStatusBar();
}

void Visualizer::DrawOptimalPath(std::vector<std::vector<int>> &path)
{
	setPosition(-1, -1);

	if (path.empty()) {
		PrintMaze();
		return;
	}

	int size = path.size();

	for (int i = 1; i < size - 2; i++) {
		Maze->at(path[i][1]).at(path[i][0]) = '0';
	}

	PrintMaze();
}

void Visualizer::updateStatus(bool count)
{
	status = count;
}

Visualizer::~Visualizer()
{
}
