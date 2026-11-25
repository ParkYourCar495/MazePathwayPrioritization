#pragma once
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class Minheaptree {
public:
    void NewNode(int y, int x, int time)
    {
        Node* new_temp = new Node;

        new_temp->x = x;
        new_temp->y = y;
        new_temp->time = time;

        minheap_array.push_back(new_temp);

        int iteration = minheap_array.size() - 1;

        while (iteration > 0)
        {
            int parent = (iteration - 1) / 2;

            if (minheap_array[parent]->time <= minheap_array[iteration]->time)
                break;

            Node* temp = minheap_array[parent];
            minheap_array[parent] = minheap_array[iteration];
            minheap_array[iteration] = temp;

            iteration = parent;
        }
    }

    Node* RemoveAndReturnFirstNode()
    {
        if (minheap_array.empty())
            return nullptr;

        Node* result = minheap_array[0];

        minheap_array[0] = minheap_array.back();
        minheap_array.pop_back();

        int iteration = 0;

        while (true)
        {
            int left = iteration * 2 + 1;
            int right = iteration * 2 + 2;
            int smallest = iteration;

            if (left < minheap_array.size() && minheap_array[left]->time < minheap_array[smallest]->time)
            {
                smallest = left;
            }

            if (right < minheap_array.size() && minheap_array[right]->time < minheap_array[smallest]->time)
            {
                smallest = right;
            }

            if (smallest == iteration)
                break;

            Node* temp = minheap_array[smallest];
            minheap_array[smallest] = minheap_array[iteration];
            minheap_array[iteration] = temp;

            iteration = smallest;
        }

        return result;
    }
    ~Minheaptree()
    {
        for (Node* node : minheap_array)
        {
            delete node;
        }
        minheap_array.clear();
    }
    bool IsEmpty()
    {
        return minheap_array.empty();
    }

private:
    vector<Node*> minheap_array;
};
