//
// Created by Maciej Ciura on 12.11.2020.
//

#include <cmath>
#include <iostream>
#include "Node.h"

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


Node::Node(int index, int n, int **parentMatrix) {
    this->index = index;
    this->n = n;


    this->adjencyMatrix = new int*[n];
    for (int i=0;i<n;i++)
    {
        this->adjencyMatrix[i] = new int[n];
        for (int j=0;j<n;j++)
            this->adjencyMatrix[i][j] = parentMatrix[i][j];
    }
    this->reduceMatrix(adjencyMatrix);
}

Node::~Node() {
    for (int i=0;i<this->n;i++)
        delete [] adjencyMatrix[i];
    delete [] adjencyMatrix;

}

unsigned int Node::getIndex() {
    return this->index;
}

unsigned int Node::getCost() {
    return this -> cost;
}

void Node::reduceMatrix(int **matrix) {
    int *minI = new int[this->n];
    int *minJ = new int[this->n];
    for (int i = 0; i < this->n; i++) {
        matrix[i][i] = INT_MAX;
        minI[i] = INT_MAX;
        minJ[i] = INT_MAX;
    }
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++)
            if (matrix[i][j] != INT_MAX) {
                minI[i] = std::min(matrix[i][j], minI[i]);
                minJ[j] = std::min(matrix[j][i], minJ[j]);
            }
    }

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            if (matrix[i][j] != INT_MAX)
            {
                matrix[i][j] -= (minI[i] + minJ[i]%minI[i]);
                this->cost += minI[i] + minJ[i]%minI[i];
            }
    delete[]minI;
    delete[]minJ;
}