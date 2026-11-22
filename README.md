# MazePathwayPrioritization
Before opening the application, the user must create a .txt file with a rectangular maze built according to the user's desire.
A maze is comprised of the chars "." "X" "O" "S" and "F"
- "X" denotes impassible walls of the maze. 
- "S" denotes where the pathfinding algorithm starts. There should only be 1 of this symbol.
- "F" denotes where the pathfinding algorithm ends and records its time.
- "O" denotes an obstruction that can be passed through, but it will add extra time to the pathfinding algorithm.
- "." should fill every remaining space within the maze, it denotes where the pathfinding algorithm can move.
Once the maze is written and saved to a .txt file, it must be placed into the main directory of the application folder.

Once in the application, the user is prompted with an integer-based menu. The user enters an integer according to which choice they want.
The user must first load a maze with choice 2, it will import whichever .txt file the user types in.
The user can then run the algorithm with choice 1. This will print the shortest recorded route's time from start to finish, as well as the coordinates taken to traverse that path.
The user can repeatedly load new mazes with choice 2, but only 1 maze can be loaded at a time.
The application can be terminated with choice 0.

# Requirements
- Visual Studio or Visual Studio Code
- C++ 11 Extension
