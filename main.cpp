
#include <iostream>
#include "Graph.h"
//#include <conio.h>


int main() {
    int n = 5;

    auto *graph = new Graph();
    //std::cin>>n;
    //graph->generateAdjMatrix(n);

    if(!graph->loadFromFile("test.txt"))
        std::cout << "Blad odczytu pliku" << std::endl;

    std::cout << graph;

    graph->tspBranchAndBound(0);
    //unsigned int sum = graph->tspBruteforceTree(0);
    //unsigned int sum = graph -> tspBruteforcePerm();
    std::cout << graph;
    //std::cout << std::endl << sum << std::endl;

    for  (int i : graph->getPathMin())
        std::cout << i << ' ';

   // getch();
    delete graph;
    return 0;
}
