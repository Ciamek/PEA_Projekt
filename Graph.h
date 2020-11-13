//
// Created by Maciej Ciura on 06.11.2020.
//

//#pragma once

#ifndef PEA_PROJEKT1_GRAPH_H
#define PEA_PROJEKT1_GRAPH_H

#include <string>
#include <vector>
#include "Node.h"

class Graph {

private:
    int n;
    int **adjencyMatrix;

    std::vector<int> path_min;


public:
    Graph();
    Graph(int n);
    ~Graph();
    int getSize();
    std::vector<int> getPathMin();

    bool loadFromFile(const std::string& file_name);
    void generateAdjMatrix(int n);

    unsigned int tspBruteforceTree(int node);
    void tspBruteforceTreeRec(int v, std::vector<int> path, bool *visited, unsigned int sum, unsigned int &sum_min);

    unsigned int tspBruteforcePerm();

    unsigned int tspBranchAndBoundRec(int node_index, bool *visited, unsigned int lowerBound, unsigned int upperBound);

    unsigned int tspBranchAndBound(int node);

    unsigned int dynamicProgramming_TSP(int node);

    friend std::ostream& operator <<(std::ostream& output, const Graph* g);
};

#endif //PEA_PROJEKT1_GRAPH_H
