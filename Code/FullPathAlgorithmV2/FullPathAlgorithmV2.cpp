/*********************************************
TEAM ZA
Kaleb Parker, Ethan Garrigus, Jacob Blackmon
CSCEA311 Group Project
Date Completed: November 24, 2026
Description: [DESCRIPTION]
Version: 1.0
*********************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>
#include <cctype>
#include <limits>
#include <algorithm>
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

//Maze vector
vector<vector<char>> the_maze;

//Check to see if a maze has been imported
bool imported_maze = false;

//Time value of O spaces
int time_penalty = 3;

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
        std::cout << "4. Set time penalty for O space (it is currently " << time_penalty << ")\n";
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

        case 4:
        {
            cout << "Enter new value for O spaces (must be over 1): ";
            int int_input;
            cin >> int_input;
            if (int_input > 1)
            {
                time_penalty = int_input;
            }
            else
            {
                cout << "Error: Time penalty is not over 1.\n";
            }
            
        }
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


    //Displays the maze and calculates the max indexes for x and y
    cout << "  ";
    for (int y = 0; y < the_maze[0].size(); y++)
    {
        cout << y % 10;
    }
    std::cout << std::endl;
    for (int y = 0; y < the_maze.size(); y++)
    {
        cout << y % 10<< " ";

        for (int x = 0; x < the_maze[y].size(); x++)
        {
            cout << the_maze[y][x];

        }
        cout << std::endl;
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

    //Load Maze
    imported_maze = true;
}


void Pathfinding()
{
    //Sets maximum area pathfinding can traverse
    int height = the_maze.size();
    int width = the_maze[0].size();

    //Sets a constant integer equal to the maximum possible integer value
    const int infinity = numeric_limits<int>::max();

    //Makes a nested vector to be the lowest-known travel cost for each char/space/coordinate
    //They all start at infinity (or highest int value)
    vector<vector<int>> distances(height, vector<int>(width, infinity));

    //Creates a triple nested vector to remember the previous coordinate taken to reach a specific coordinate
    vector<vector<vector<int>>> parent(height, vector<vector<int>>(width, vector<int>(2, -1)));

    //Coordinates for S and F
    vector<int> start_position = { -1,-1 };
    vector<int> finish_position = { -1,-1 };

    //Finds the starting and ending positions
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (the_maze[y][x] == 'S')
            {
                start_position[0] = y;
                start_position[1] = x;
            }

            if (the_maze[y][x] == 'F')
            {
                finish_position[0] = y;
                finish_position[1] = x;
            }
        }
    }

    //returns and prints message if start and/or finish are not present in loaded maze
    if (start_position[0] == -1 || finish_position[0] == -1)
    {
        cout << "Starting and/or finishing positions not found in the current maze.\n";
        return;
    }

    //Make the shortest distance of the starting coordinate equal to zero
    distances[start_position[0]][start_position[1]] = 0;

    //Initializes a minheap object
    Minheaptree minheap;

    //Make the starting coordinate and its time the first node of the minheap
    minheap.NewNode(start_position[0], start_position[1], 0);

    //size 4 arrays indicating directions. right, up, down, left
    int directions_y[] = { 0, -1, 1, 0 };
    int directions_x[] = { 1, 0, 0, -1 };

    while (!minheap.IsEmpty())
    {
        //Removes the minheap's first node and loads its info
        Node* current = minheap.RemoveAndReturnFirstNode();
        int x = current->x;
        int y = current->y;
        int time = current->time;
        delete current;

        //Skip a node that doesn't have the current shortest time to a point
        if (time != distances[y][x])
        {
            continue;
        }

        //Breaks while-loop if the finish was reached
        if (y == finish_position[0] && x == finish_position[1])
        {
            break;
        }
        
        //iterates through the 4 directions
        for (int i = 0; i < 4; i++)
        {
            //saves the next coordinate according to the direction
            int new_x = x + directions_x[i];
            int new_y = y + directions_y[i];

            //skips iteration if out of bounds
            if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height)
                continue;

            //skips iteration if on a wall/X
            if (the_maze[new_y][new_x] == 'X')
                continue;

            //Adds the time cost of the next coordinate
            int cost = 0;
            if (the_maze[new_y][new_x] == 'O')
            {
                cost = time_penalty;
            }
            else
            {
                cost = 1;
            }
            int new_time = time + cost;

            //Saves calculated time to distances of the next coord
            //Saves current coord as a parent of the next coord
            //Saves the next coord as a new minheap node
            //ALL IF the newly calculated time is less than the next coord's current time
            if (new_time < distances[new_y][new_x])
            {
                distances[new_y][new_x] = new_time;
                parent[new_y][new_x] = { y, x };
                minheap.NewNode(new_y, new_x, new_time);
            }
        }
    }

    //Ends and prints basically nothing if the finish could not be reached (entirely blocked by walls)
    if (distances[finish_position[0]][finish_position[1]] == infinity)
    {
        cout << "No path found.\n";
        return;
    }

    //Reconstructs the path (from last coordinate to first/original coordinate)
    vector<vector<int>> path;
    vector<int> current_position = finish_position;
    while (current_position != start_position)
    {
        path.push_back(current_position);
        current_position = parent[current_position[0]][current_position[1]];
    }
    path.push_back(start_position);


    //Printing the traversed, shortest path (backwards, to be adjusted to how the path was reconstructed)
    //When running the program, the path is printed in correct start to finish order
    cout << "Shortest path time: " << distances[finish_position[0]][finish_position[1]] << endl;
    cout << "Shortest path coordinates: ";
    for (int i = path.size()-1; i >-1 ;i--)
    {
        cout << "(" << path[i][1] << "," << path[i][0] << ") ";
    }
    cout << endl;
}
