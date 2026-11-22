#pragma once
#include <vector>
#include <iostream>

#include "Node.h"

using namespace std;

class Minheaptree {
public:
    void NewNode(std::vector<vector<int>> i_path, int i_time) {
        if (minheap_array.size() > 0) { // Skip if the requested node would have a time larger than the current smallest node
            if (i_time>= minheap_array[0]->time) {
                return;
            }
        }

        int count = minheap_array.size();
        Node* new_temp = new Node;
        new_temp->time = i_time;
        new_temp->path = i_path;

        if (count == 0) {
            minheap_array.push_back(new_temp);
        }
        else {
            minheap_array.push_back(new_temp);
            int iteration = count;
            while (minheap_array[iteration]->time < minheap_array[(iteration - 1) / 2]->time) {
                Node* temp = minheap_array[(iteration - 1) / 2];
                minheap_array[(iteration - 1) / 2] = minheap_array[iteration];
                minheap_array[iteration] = temp;

                iteration = (iteration - 1) / 2;
            }
        }
    }

    void RemoveAndReturnFirstNode() {
        if (minheap_array.size() == 0) {
            cout << "No paths detected in the minheap." << endl;
            return;
        }

        vector<vector<int>> return_path = minheap_array[0]->path;
        int return_time = minheap_array[0]->time;
        int count = minheap_array.size();
        delete minheap_array[0];
        minheap_array[0] = nullptr;
        minheap_array[0] = minheap_array[count - 1];
        minheap_array[count - 1] = nullptr;
        minheap_array.pop_back();
        int iteration = 0;

        while (minheap_array.size() > 2 * iteration + 2 && (minheap_array[iteration]->time > minheap_array[2 * iteration + 1]->time ||
            minheap_array[iteration]->time > minheap_array[2 * iteration + 2]->time)) {
            Node* temp = minheap_array[iteration];
            if (minheap_array[2 * iteration + 1]->time > minheap_array[2 * iteration + 2]->time) {
                minheap_array[iteration] = minheap_array[2 * iteration + 2];
                minheap_array[2 * iteration + 2] = temp;
                iteration = iteration * 2 + 2;
            }
            else {
                minheap_array[iteration] = minheap_array[2 * iteration + 1];
                minheap_array[2 * iteration + 1] = temp;
                iteration = iteration * 2 + 1;
            }
        }

        // Print the former first node's stats
        cout << "The time of the shortest path is " << return_time << "."<<endl;
        cout << "The coordinates of an applicable shortest path is: ";
        for (int i = 0; i < return_path.size(); i++) {
            cout << "("<<return_path[i][0] << "," << return_path[i][1] << ") ";
        }
    }

private:
    vector<Node*> minheap_array;
};
