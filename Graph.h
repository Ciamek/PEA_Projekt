//
// Created by Maciej Ciura on 06.11.2020.
//

#pragma once

#ifndef PEA_PROJEKT1_GRAPH_H
#define PEA_PROJEKT1_GRAPH_H

#include <string>
#include <vector>

class Graph {

private:
    int n;
    int **adjencyMatrix;

    void bruteforceTSP_rec(int v, std::vector<int> path, bool *visited, unsigned int sum, unsigned int &sum_min);

public:
    Graph();
    Graph(int n);
    ~Graph();

    int getSize();

    bool loadFromFile(const std::string& file_name);
    void generateAdjMatrix(int n);

    unsigned int bruteforce_TSP(int node);
    unsigned int branchAndBound_TSP(int node);
    unsigned int dynamicProgramming_TSP(int node);

    friend std::ostream& operator <<(std::ostream& output, const Graph* g);

    std::vector<int> path_min;
};

#endif //PEA_PROJEKT1_GRAPH_H
