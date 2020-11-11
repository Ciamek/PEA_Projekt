//
// Created by Maciej Ciura on 06.11.2020.
//

#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"

Graph::Graph() {
    n=0;
    adjencyMatrix = nullptr;
}

Graph::Graph(int n) {
    this->n = n;
    adjencyMatrix = new int *[n];
    for(int i=0; i<n; i++) {
        adjencyMatrix[i] = new int[n];
    }
}

Graph::~Graph() {
    for(int i=0; i<n; i++)
    {
        delete [] this->adjencyMatrix[i];
    }
    delete [] this->adjencyMatrix;
    this->adjencyMatrix = nullptr;
}

int Graph::getSize() {
    return this->n;
}

std::ostream &operator<<(std::ostream &output, const Graph *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            output << g->adjencyMatrix[i][j] << "  ";
        }
        output << std::endl;
    }
    return output;
}

bool Graph::loadFromFile(const std::string& file_name) {
    std::fstream file;
    file.open(file_name);

    if(!file.good()) {
        file.close();
        return false;
    }

    file >> this->n;
    if (n <= 0) {
        file.close();
        return false;
    }

    this->adjencyMatrix = new int*[n];
    for (int i = 0; i < n; i++) {
        this->adjencyMatrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            file >> adjencyMatrix[i][j];
        }
    }
    for (int i = 0; i < n; i++)
        adjencyMatrix[i][i] = 0;
    file.close();
    return true;
}

void Graph::generateAdjMatrix(int n) {
    this->n = n;
    auto seed = std::time(nullptr) ^ std::random_device()();
    static std::mt19937 mt{seed};
    std::uniform_int_distribution<int> dist{10, 99};

    adjencyMatrix = new int*[n];
    for(int i=0; i<n; i++) {
        adjencyMatrix[i] = new int[n];
        for(int j=0; j<n; j++) {
            adjencyMatrix [i][j] = dist(mt);
        }
        adjencyMatrix[i][i] = 0;
    }
}

unsigned int Graph::bruteforce_TSP(int node) {
    std::vector<int> path;
    bool *visited = new bool[this->n];
    for(int i=0; i<n; i++) visited [i] = false;
    unsigned int sum = 0, sum_min = 9999;

    bruteforceTSP_rec(node, path, visited, sum, sum_min);

    delete []visited;
    return sum_min;
}

void Graph::bruteforceTSP_rec(int v, std::vector<int> path, bool *visited, unsigned int sum, unsigned int &sum_min)
{
    int u;
    visited[v] = true;
    path.push_back(v);
    if(path.size() < this->n)
    {
        for(u=0; u < this->n; u++) {
            if(this->adjencyMatrix[v][u] && !visited[u])
            {
                sum += adjencyMatrix[v][u];
                bruteforceTSP_rec(u, path, visited, sum, sum_min);
                sum -= adjencyMatrix[v][u];
            }
        }
    }
    else if (this->adjencyMatrix[v][0])
    {
        sum += adjencyMatrix[v][0];
        if(sum < sum_min)
        {
            sum_min = sum;
            this->path_min = path;
        }
    }
    visited[v] = false;
    path.pop_back();
}

unsigned int Graph::branchAndBound_TSP(int node) {
    return 0;
}

unsigned int Graph::dynamicProgramming_TSP(int node) {
    return 0;
}
