//
// Created by Maciej Ciura on 12.11.2020.
//

#ifndef PEA_PROJEKT1_NODE_H
#define PEA_PROJEKT1_NODE_H

#include <vector>


class Node {

private:
    int index;
    int n;
    int **adjencyMatrix;
    unsigned int cost;
    int level;
    std::vector<int> path;

public:

    Node(int index, int n, int **parentMatrix);
    ~Node();
    unsigned int getIndex();
    unsigned int getCost();
    void reduceMatrix(int **matrix);
};


#endif //PEA_PROJEKT1_NODE_H
