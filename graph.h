#ifndef GRAPH_H
#define GRAPH_H

#include "ads.h"

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
public:
    AVLTree **adjacencyList;
    int numVertices;
    int numEdges;

    Graph(int numVertices) : numVertices(numVertices), numEdges(0)
    {
        adjacencyList = new AVLTree *[numVertices];
        for (int i = 0; i < numVertices; i++)
            adjacencyList[i] = new AVLTree();
    }

    ~Graph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            delete adjacencyList[i];
        }
        delete[] adjacencyList;
    }

    bool isEmpty();

    bool insertEdge(int curr, int adj, int weight);
    bool printAdjacent(int a);
    bool deleteVertex(int a);
};

class MST
{
private:
    Graph *mst;
    Heap *pq;
    bool *visitedVertices;

public:
    MST() : mst(nullptr), pq(nullptr), visitedVertices(nullptr) {}

    ~MST()
    {
        delete mst;
        delete pq;
        delete[] visitedVertices;
    }

    void primMST(Graph *graph);

    void printMST();
    int getWeight();
};

#endif // GRAPH_H