//
// Created by Maciej Ciura on 06.11.2020.
//

#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "Graph.h"
#include "Node.h"

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


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

std::vector<int> Graph::getPathMin() {
    return this -> path_min;
}

std::ostream &operator<<(std::ostream &output, const Graph *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            output << g->adjencyMatrix[i][j]%INT_MAX << "  ";
        }
        output << std::endl;
    }
    return output;
}

bool Graph::loadFromFile(const std::string& file_name) {

    for(int i=0; i<n; i++)
    {
        delete [] this->adjencyMatrix[i];
    }
    delete [] this->adjencyMatrix;
    this->adjencyMatrix = nullptr;

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

unsigned int Graph::tspBruteforceTree(int node) {
    std::vector<int> path;
    bool *visited = new bool[this->n];
    for(int i=0; i<n; i++) visited [i] = false;
    unsigned int sum = 0, sum_min = 9999;
    int i=0;
    tspBruteforceTreeRec(node, path, visited, sum, sum_min);

    delete []visited;
    std::cout << i << std::endl;
    return sum_min;
}

void Graph::tspBruteforceTreeRec(int v, std::vector<int> path, bool *visited, unsigned int sum, unsigned int &sum_min)
{
    int u;
    path.push_back(v);

    if(path.size() < this->n - 1)
    {
        visited[v] = true;
        for(u=0; u < this->n; u++) {
            if(this->adjencyMatrix[v][u] && !visited[u])
            {
                sum += adjencyMatrix[v][u];
                tspBruteforceTreeRec(u, path, visited, sum, sum_min);
                sum -= adjencyMatrix[v][u];
            }
        }
        visited[v] = false;
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
    path.pop_back();
}


unsigned int Graph::tspBruteforcePerm() {
    int sum, sum_min = 9999;
    std::vector<int> path;
    for(int i=0; i<this -> n; i++)
        path.push_back(i);
    do{
        sum = 0;
        for(int i=0; i < this->n-1; i++)
        {
            sum += this -> adjencyMatrix[path[i]][path[i+1]];
        }
        sum += this->adjencyMatrix[path[n-1]][0];
        if(sum < sum_min)
        {
            sum_min = sum;
            this-> path_min = path;
        }
    }while (std::next_permutation(path.begin()+1, path.end()));

    return sum_min;
}

unsigned int Graph::dynamicProgramming_TSP(int start_node) {
    return 0;
}


unsigned int Graph::tspBranchAndBound(int start_node) {
    std::vector<int> path;
    bool *visited = new bool[this->n];
    for(int i=0; i<n; i++) visited [i] = false;
    unsigned int lowerBound = 0, upperBound = 9999;

    Node *node = new Node(start_node, this->n, this->adjencyMatrix);
    //znajdz upper bound
    //tspBranchAndBoundRec(node->getIndex(), visited, lowerBound, upperBound);

    delete node;
    delete []visited;
    return upperBound;
}


unsigned int Graph::tspBranchAndBoundRec(int node_index, bool *visited, unsigned int lowerBound, unsigned int upperBound) {
    unsigned int u, lowestCostNodeIndex, minCost = 0;
    Node *node;
    //koszt nołda
    for (u = 0; u < this->n; u++)
        if(this->adjencyMatrix[node_index][u] && !visited[u])
        {
            node = new Node(u, this->n, this->adjencyMatrix);
            //sprawdz wierzchoł
            if(node->getCost() < upperBound)
            {
                lowestCostNodeIndex = node -> getIndex();
                minCost = node -> getCost();
            }
            delete node;
        }
    upperBound += minCost;
    tspBranchAndBoundRec(node_index, visited, lowerBound, upperBound);


    return 0;
}


