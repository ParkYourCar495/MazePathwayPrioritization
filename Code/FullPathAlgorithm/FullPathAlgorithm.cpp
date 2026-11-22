/*********************************************
TEAM ZA
Kaleb Parker, Ethan Garrigus, E E
CSCEA311 Group Project
Date Completed: November 9, 2026
Description: [DESCRIPTION]
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
#include "Maze.h"

using namespace std;

// Pathfinding prototype
void Pathfinding();

// addMaze prototype
void addMaze();

// instantiateMazeObject prototype
void instantiateMazeObject();

// Pathfind prototype
void Pathfind(vector<vector<char>> maze, int next_y, int next_x, int time, vector<vector<int>> path, Minheaptree& minheap);

//Maze vector
vector<vector<char>> the_maze;
//Check to see if a maze has been imported
bool imported_maze = false;
//integers to set the max indexes of the maze x and y
int max_x = 0;
int max_y = 0;

//Random Maze Variables
int maze_Width = 0;
int maze_Height = 0;
Maze* maze = nullptr;


int main() {

    int choice = -1;

    //Intialize random seed
    std::srand(std::time(nullptr));

    while (choice != 0) {

        // USER MENU UI
        std::cout << "\n===== Maze Path Prioritization =====\n";
        std::cout << "1. Start Pathfinding\n";
        std::cout << "2. Add Maze Map\n";
        std::cout << "3. Generate Random Maze Map\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        // CHOICES
        switch (choice) {

            // MENU OPTIONS
        case 1: 
            if (imported_maze) //only pathfind if a maze is selected
            {
                Pathfinding();
            }
            else 
            { 
                std::cout << "No maze has been imported yet."; 
            } 
            break;
        case 2: 
            addMaze(); 
            //imported_maze = true; 
            break;

        case 3:
            instantiateMazeObject();
            
            break;

            // EXIT AND CLOSE OPERATION
        case 0: break;
        default: std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
void addMaze()//Imports a maze over global the_maze
{
    std::cout << "Enter the txt file within the current directory of the maze you wish to import: ";
    string the_file;
    std::cin >> the_file;
    
    
    
    ifstream maze_file(the_file);
    if (!maze_file.is_open())
    {
        cerr << "Error: File doesn't exist or is unable to be opened." << endl;
        return;
    }
    the_maze = {};

    //Gets each line from the file and puts it into the maze vector
    string line;
    while (getline(maze_file, line))
    {
        vector<char> row(line.begin(), line.end());
        the_maze.push_back(row);
    }


    //Closes the file
    maze_file.close();

    max_x = -1;
    max_y = -1;

    //Displays the maze and calculates the max indexes for x and y
    std::cout << "  ";
    for (int y = 0; y < the_maze[0].size(); y++)
    {
        std::cout << y % 10;
    }
    std::cout << std::endl;
    for (int y = 0; y < the_maze.size(); y++)
    {
        std::cout << y << " ";
        max_y += 1;
        for (int x = 0; x < the_maze[y].size(); x++)
        {
            std::cout << the_maze[y][x];
            if (max_y == 0)
            {
                max_x += 1;
            }
        }
        std::cout << std::endl;
    }
    imported_maze = true;
    
    
}

// Function to instantiate the maze object from user input
void instantiateMazeObject() {

    int userInput = 0;
    bool done = false;
    bool regenerate = true;

    while (regenerate) {

        //NOTE: maze is limited to a fixed size of 200x200
        //WARNING: Currently UNSTABLE for large values. HIGH chance of stack overflow as dimensions increase.
        //TODO: Implement Exception Handler --- Limit Max Dimensions

        std::cout << "Enter Maze Width: ";
        std::cin >> maze_Width;

        std::cout << "Enter Maze Height : ";
        std::cin >> maze_Height;
        std::cout << std::endl;

        done = false;
        
        while (!done) {
            
            if (regenerate) {

                if (maze != nullptr) {
                    delete maze;
                    maze = nullptr;
                }

                maze = new Maze(maze_Height, maze_Width);
                maze->generate_maze();
            }
            
            //Maze Generation UI
            std::cout << "---Maze Menu---" << std::endl;
            std::cout << "1. Regenerate Maze" << std::endl;
            std::cout << "2. Enter New Dimensions" << std::endl;
            std::cout << "3. Finalize Maze" << std::endl;
			std::cout << "Enter Selection: ";
            std::cin >> userInput;

            //NOTE: As of now, no functionality for 'O'. Maze will only generate walls and empty spaces.
            //**    Starting position is fixed at (1, 1). Finished position is randomly generated.
            //**    Maze will have to be regenerated each time to reposition 'F'
            //TODO: Add user options for customizing 'S' and 'F' locations

            switch (userInput) {
            case 1: 
                delete maze;
                maze = nullptr;
                regenerate = true;
                std::cout << std::endl;
                break;

            case 2:
                delete maze;
                maze = nullptr;
                regenerate = true;
                done = true;
                std::cout << std::endl;
                break;

            case 3:
                regenerate = false;
                done = true;
                break;

            default:
                done = false;
                regenerate = false;
				std::cout << "Invalid Input. Please Re-Enter Selection:\n" << std::endl;
            }       
        }
    }

    //Converts the maze from a 2D array into a 2D vector
    the_maze = maze->convertMazeToVector();

    //Delete the maze object to free memory
    delete maze;
    maze = nullptr;

	//Sets max maze indices 
    max_y = maze_Height - 1;
    max_x = maze_Width - 1;

    //Load Maze
    imported_maze = true;
}


void Pathfinding()
{
    Minheaptree the_heap; //Creates a minheap
    int start_y = -1;
    int start_x = -1;
    bool finish_exists = false;
    for (int y = 0; y < the_maze.size(); y++) //finds the starting position S
    {
        
        for (int x = 0; x < the_maze[y].size(); x++)
        {
            if (the_maze[y][x] == 'S')
            {
                start_y = y;
                start_x = x;
                break;
            }
        }
        if (start_y != -1)
        {
            break;
        }
    }
    for (int y = 0; y < the_maze.size(); y++) //finds the ending position F
    {

        for (int x = 0; x < the_maze[y].size(); x++)
        {
            if (the_maze[y][x] == 'F')
            {
                finish_exists = true;
                break;
            }
        }
        if (finish_exists == true)
        {
            break;
        }
    }
    if (start_y == -1 || start_x == -1) //Stops the function if there is no starting position
    {
        std::cout << "Error: No starting position found." << std::endl;;
        return;
    }
    if (finish_exists==false) //Stops if no finish position found
    {
        std::cout << "Error: No finishing position found." << std::endl;;
        return;
    }
    Pathfind(the_maze, start_y, start_x,0,{},the_heap); //Starts the recursive functions traversal
    std::cout << std::endl;
    the_heap.RemoveAndReturnFirstNode(); //Removes and prints the first node

    
}
void Pathfind(vector<vector<char>> maze, int next_y, int next_x, int time, vector<vector<int>> path, Minheaptree& minheap)
{
    path.push_back({next_x,next_y});//Adds current position to the path

    if (maze[next_y][next_x] == '.'|| maze[next_y][next_x] == 'F')//increment time by 1 on a period or F
    {
        time += 1;
    }
    else if(maze[next_y][next_x] == 'O') //increment time by 3 on an O
    {
        time += 3;
    }

    if (maze[next_y][next_x] == 'X') //Stop current run if the current char is X
    {
        return;
    }
    else if (maze[next_y][next_x] == 'F') //Stops current run and adds a node to the heap
    {
        minheap.NewNode(path, time);
        
        return;
    }
    else //Proceeds otherwise
    {
        maze[next_y][next_x] = 'X'; //Mark current position as X, so it doesn't repeat this spot


        if (next_x+1 <= max_x)//Go right
        {
            Pathfind(maze,  next_y, next_x+1, time,  path, minheap);
        }
        if (next_y - 1 >= 0)//Go up
        {
            Pathfind(maze, next_y - 1, next_x , time, path, minheap);
        }
        if ( next_y + 1 <= max_y)//Go down
        {
            Pathfind(maze, next_y + 1, next_x , time, path, minheap);
        }
        if (next_x - 1 >= 0 )//Go left
        {
            Pathfind(maze, next_y , next_x-1 , time, path, minheap);
        }
    }
}