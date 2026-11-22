/*********************************************
TEAM ZA
Kaleb Parker, Ethan Garrigus, Jacob Blackmon
CSCEA311 Group Project
Date Completed: November 22, 2026
Description: An algorthm that tests and finds the fastest pathway from a starting position to an ending position.
Version: 1.0
*********************************************/

# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <vector>
# include <cmath>
# include <cstdlib>
# include <ctime>
# include <array>
# include <cctype>

#include "Node.h"
#include "Minheaptree.h"

using namespace std;

// Pathfinding prototype
void Pathfinding();
// addMaze prototype
void addMaze();
// Pathfind prototype
void Pathfind(vector<vector<char>> maze, int next_y, int next_x, int time, vector<vector<int>> path, Minheaptree& minheap);

// Maze vector
vector<vector<char>> the_maze;
//C heck to see if a maze has been imported
bool imported_maze = false;
// Integers to set the max indexes of the maze x and y
int max_x = 0;
int max_y = 0;

int main() {
    int choice = -1;
    
    while (choice != 0) {

        // USER MENU UI
        cout << "\n===== Maze Path Prioritization =====\n";
        cout << "1. Start Pathfinding\n";
        cout << "2. Add Maze Map\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        // CHOICES
        switch (choice) {

        // MENU OPTIONS
        case 1: 
            if (imported_maze) { // Only pathfind if a maze is selected
                Pathfinding();
            }
            else { 
                cout << "No maze has been imported yet."; 
            } 
            break;
        case 2: 
            addMaze(); // Imported_maze = true; 
            break;
        case 0: break; // EXIT AND CLOSE OPERATION
        default: cout << "Invalid option.\n";
        }
    }
    return 0;
}

void addMaze() { // Imports a maze over global the_maze
    cout << "Enter the txt file within the current directory of the maze you wish to import: ";
    string the_file;
    cin >> the_file;
    
    ifstream maze_file(the_file);
    if (!maze_file.is_open()) {
        cerr << "Error: File doesn't exist or is unable to be opened." << endl;
        return;
    }
    the_maze = {};

    // Gets each line from the file and puts it into the maze vector
    string line;
    while (getline(maze_file, line)) {
        vector<char> row(line.begin(), line.end());
        the_maze.push_back(row);
    }

    maze_file.close(); // Closes the file
    max_x = -1;
    max_y = -1;

    // Displays the maze and calculates the max indexes for x and y
    cout << "  ";
    for (int y = 0; y < the_maze[0].size(); y++) {
        cout << y % 10;
    }
    cout << endl;
    for (int y = 0; y < the_maze.size(); y++) {
        cout << y << " ";
        max_y += 1;
        for (int x = 0; x < the_maze[y].size(); x++) {
            cout << the_maze[y][x];
            if (max_y == 0) {
                max_x += 1;
            }
        }
        cout << endl;
    }
    imported_maze = true;
}

void Pathfinding() {
    Minheaptree the_heap; // Creates a minheap
    int start_y = -1;
    int start_x = -1;
    bool finish_exists = false;

    for (int y = 0; y < the_maze.size(); y++) { // Finds the starting position 'S'
        for (int x = 0; x < the_maze[y].size(); x++) {
            if (the_maze[y][x] == 'S') {
                start_y = y;
                start_x = x;
                break;
            }
        }
        if (start_y != -1) {
            break;
        }
    }

    for (int y = 0; y < the_maze.size(); y++) { // Finds the ending position 'F'
        for (int x = 0; x < the_maze[y].size(); x++) {
            if (the_maze[y][x] == 'F') {
                finish_exists = true;
                break;
            }
        }
        if (finish_exists == true) {
            break;
        }
    }

    if (start_y == -1 || start_x == -1) { // Stops the function if there is no starting position
        cout << "Error: No starting position found." << endl;;
        return;
    }
    if (finish_exists==false) { // Stops if no finish position found
        cout << "Error: No finishing position found." << endl;;
        return;
    }

    Pathfind(the_maze, start_y, start_x,0,{},the_heap); // Starts the recursive functions traversal
    cout << endl;
    the_heap.RemoveAndReturnFirstNode(); // Removes and prints the first node
}

void Pathfind(vector<vector<char>> maze, int next_y, int next_x, int time, vector<vector<int>> path, Minheaptree& minheap) {
    path.push_back({next_x,next_y}); // Adds current position to the path

    if (maze[next_y][next_x] == '.'|| maze[next_y][next_x] == 'F') { // Increment time by 1 on a period or 'F'
        time += 1;
    }
    else if(maze[next_y][next_x] == 'O') { // Increment time by 3 on an 'O'
        time += 3;
    }

    if (maze[next_y][next_x] == 'X') { // Stop current run if the current char is 'X'
        return;
    }
    else if (maze[next_y][next_x] == 'F') { // Stops current run and adds a node to the heap
        minheap.NewNode(path, time);
        return;
    }
    else { // Proceeds otherwise
        maze[next_y][next_x] = 'X'; // Mark current position as 'X', so it doesn't repeat this spot

        if (next_x+1 <= max_x) { // Go right
            Pathfind(maze,  next_y, next_x+1, time,  path, minheap);
        }
        if (next_y - 1 >= 0) { // Go up
            Pathfind(maze, next_y - 1, next_x , time, path, minheap);
        }
        if ( next_y + 1 <= max_y) { // Go down
            Pathfind(maze, next_y + 1, next_x , time, path, minheap);
        }
        if (next_x - 1 >= 0 ) { // Go left
            Pathfind(maze, next_y , next_x-1 , time, path, minheap);
        }
    }
}
