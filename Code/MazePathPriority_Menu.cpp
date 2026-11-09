/*********************************************
TEAM ZA
Kaleb Parker, E E, E E
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

using namespace std;

// TEMPLATE FUNCTION
void Pathfinding() {}

// TEMPLATE FUNCTION
void addMaze() {}

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
            case 1: Pathfinding(); break;
            case 2: addMaze(); break;
            
            // EXIT AND CLOSE OPERATION
            case 0: break;
            default: cout << "Invalid option.\n";
        }
    }

    return 0;
}