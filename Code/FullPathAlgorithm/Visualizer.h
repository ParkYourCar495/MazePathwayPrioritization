#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class Visualizer {
public:
	Visualizer();
	void setMaze(std::vector<std::vector<char>> *maze);
	void setPosition(int y, int x);
	void begin();
	void end();
	void PrintMaze();
	void DrawOptimalPath(std::vector<std::vector<int>> &path);
	void updateStatus(bool count);
	~Visualizer();


private:
	std::vector<std::vector<char>>* Maze;
	int y_pos, x_pos, maze_height, maze_width, frameStart, rounds;
	bool status;
	std::string process_message;
	void drawStatusBar();
	

};
