#include "graph.h"

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

bool Graph::isEmpty()
{
    return numEdges == 0;
}
// time complexity: O(1)

bool Graph::insertEdge(int curr, int adj, int weight)
{
    if (curr >= numVertices || adj >= numVertices || curr == adj)
        return false;

    if (!adjacencyList[curr]->insertNode(adj, weight))
        return false;

    adjacencyList[adj]->insertNode(curr, weight);

    numEdges++;
    return true;
}
// time complexity: O(log a)

bool Graph::printAdjacent(int a)
{
    if (adjacencyList[a]->root == nullptr)
        return false;

    adjacencyList[a]->inOrder(adjacencyList[a]->root);
    return true;
}
// time complexity: O(a)

bool Graph::deleteVertex(int a)
{
    if (adjacencyList[a]->root == nullptr)
        return false;

    delete adjacencyList[a];          // O(a)
    adjacencyList[a] = new AVLTree(); // O(1)

    for (int i = 0; i < this->numVertices; i++) // O(n)
        if (adjacencyList[i]->root != nullptr)
            adjacencyList[i]->deleteNode(a); // O(log a)

    numEdges--;
    return true;
}
// time complexity: O(n log a)

void MST::primMST(Graph *graph)
{
    // initialize the visited vertices array
    if (this->visitedVertices != nullptr)
        delete[] this->visitedVertices; // O(n)
    this->visitedVertices = new bool[graph->numVertices];
    for (int i = 0; i < graph->numVertices; i++) // O(n)
        this->visitedVertices[i] = false;

    // initialize the MST
    if (this->mst != nullptr)
        delete this->mst;
    this->mst = new Graph(graph->numVertices);

    // start with vertex a
    int parent = 0;
    for (parent; parent < graph->numVertices; parent++) // O(n)
    {
        if (graph->adjacencyList[parent]->root != nullptr)
        {
            this->visitedVertices[parent] = true;
            break;
        }
    }

    this->mst->adjacencyList[parent]->insertNode(-1, 0);

    // initialize the queue
    if (this->pq != nullptr)
        delete this->pq;
    this->pq = new Heap(graph->numVertices); // O(1)

    // insert all the adjacent vertices of a into the queue
    this->pq->initialize(graph->adjacencyList[parent]->root, parent); // O(a)

    // while the queue is not empty
    while (!this->pq->isEmpty()) // O(n)
    {
        // get the vertex with the minimum cost
        tuple<int, int, int> minEdge = this->pq->extractMin(); // O(log a)
        int minWeight = get<0>(minEdge);
        int minVertex = get<1>(minEdge);
        parent = get<2>(minEdge);

        // if the vertex has already been visited, continue
        if (visitedVertices[minVertex] && visitedVertices[parent])
            continue;

        // add the vertex to the MST
        this->mst->adjacencyList[minVertex]->insertNode(parent, minWeight);
        this->visitedVertices[minVertex] = true;

        // insert all the adjacent vertices of the vertex into the queue
        this->pq->initialize(graph->adjacencyList[minVertex]->root, minVertex);
    }
}
// time complexity: O(n log a)

void MST::printMST()
{
    for (int i = 0; i < this->mst->numVertices; i++)
        if (this->mst->adjacencyList[i]->root != nullptr)
        {
            if (this->mst->adjacencyList[i]->root->vertex != -1)
                cout << this->mst->adjacencyList[i]->root->vertex + 1 << " " << i + 1 << " " << this->mst->adjacencyList[i]->root->weight + 1 << " ";
        }

    cout << endl;
}

int MST::getWeight()
{
    int weight = 0;
    for (int i = 0; i < this->mst->numVertices; i++)
        if (this->mst->adjacencyList[i]->root != nullptr)
            weight += this->mst->adjacencyList[i]->root->weight + 1;

    return weight - 1;
}