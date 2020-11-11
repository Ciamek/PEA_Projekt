
#include <iostream>
#include "Graph.h"
#include <conio.h>


int main() {

    int n = 5;

    auto *graph = new Graph();
    //std::cin>>n;
    //graph->generateAdjMatrix(n);

    if(!graph->loadFromFile("test.txt"))
        std::cout << "Blad odczytu pliku" << std::endl;

    unsigned int sum = graph->bruteforce_TSP(0);
    std::cout << graph;
    std::cout << std::endl << sum << std::endl;

    for  (int i : graph->path_min)
        std::cout << i << ' ';

    getch();
    delete graph;
    return 0;
}
