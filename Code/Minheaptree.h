#pragma once
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class Minheaptree {
public:
    void NewNode(std::vector<vector<int>> i_path, int i_time) {
        int count = minheap_array.size();
        Node* new_temp = new Node;
        new_temp->time = i_time;
        new_temp->path = i_path;

        if (count == 0)
        {
            minheap_array.push_back(new_temp);
        }
        else
        {
            minheap_array.push_back(new_temp);
            int iteration = count;
            while (minheap_array[iteration]->time < minheap_array[(iteration - 1) / 2]->time)
            {
                Node* temp = minheap_array[(iteration - 1) / 2];
                minheap_array[(iteration - 1) / 2] = minheap_array[iteration];
                minheap_array[iteration] = temp;

                iteration = (iteration - 1) / 2;

            }
        }
    }
    std::vector<vector<int>> RemoveAndReturnFirstNode() {
        if (minheap_array.size() == 0)
        {
            return { };
        }
        vector<vector<int>> return_path = minheap_array[0]->path;
        int count = minheap_array.size();
        delete minheap_array[0];
        minheap_array[0] = nullptr;
        minheap_array[0] = minheap_array[count - 1];
        //delete system[count - 1];
        minheap_array[count - 1] = nullptr;
        minheap_array.pop_back();
        int iteration = 0;
        while (minheap_array.size() > 2 * iteration + 2 && (minheap_array[iteration]->time > minheap_array[2 * iteration + 1]->time ||
            minheap_array[iteration]->time > minheap_array[2 * iteration + 2]->time))
        {
            //cout << "Iteration: " << iteration << endl;
            Node* temp = minheap_array[iteration];
            if (minheap_array[2 * iteration + 1]->time > minheap_array[2 * iteration + 2]->time)
            {
                minheap_array[iteration] = minheap_array[2 * iteration + 2];
                minheap_array[2 * iteration + 2] = temp;
                iteration = iteration * 2 + 2;
            }
            else
            {
                minheap_array[iteration] = minheap_array[2 * iteration + 1];
                minheap_array[2 * iteration + 1] = temp;
                iteration = iteration * 2 + 1;
            }
        }



        return return_path;
    }
    

private:
    vector<Node*> minheap_array;
};
