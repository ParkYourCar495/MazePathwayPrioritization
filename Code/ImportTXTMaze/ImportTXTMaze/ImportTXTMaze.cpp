#include <iostream> //Allows input/output
#include <fstream> //Allows importing files
#include <vector> //Allows vectors
#include <string> //Allows strings
using namespace std; //Convenience
int main()
{
    vector<vector<char>> the_maze; //The maze for the algorithm to traverse. For now, it is a 2D vector.

    //Opens the file
    //For now, I've put the TXT file into the main directory of the visual studio project. (Just put it into the project folder's first layer)
    //Change the name of what's in the quotation marks to choose a different TXT file to use
    ifstream maze_file("Maze1.txt");
    

    //Gets each line from the file and puts it into the maze vector
    string line;
    while (getline(maze_file, line)) 
    {
        vector<char> row(line.begin(), line.end());
        the_maze.push_back(row);
    }


    //Closes the file
    maze_file.close();

    //Displays the maze (test for right now, can be removed later if desired)
    for (int y = 0; y < the_maze.size(); y++)
    {
        for (int x = 0; x < the_maze[y].size(); x++)
        {
            cout << the_maze[y][x];
        }
        cout << endl;
    }
}
