#ifndef ADS_H
#define ADS_H

#include <iostream>
#include <tuple>
using namespace std;

class Node
{
public:
    int vertex;
    int weight;
    Node *left;
    Node *right;
    Node *parent;

    Node(int vertex, int weight, Node *parent)
    {
        this->vertex = vertex;
        this->weight = weight;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node()
    {
        delete this->left;
        delete this->right;
    }
};

class AVLTree
{
private:
public:
    Node *root;
    AVLTree() : root(nullptr){};
    ~AVLTree() { delete this->root; };

    int getHeight(Node *node);
    int getBalance(Node *node);

    void inOrder(Node *node);

    void rotateLeft(Node *node);
    void rotateRight(Node *node);
    Node *getSuccesor(Node *node);
    void balanceTree(Node *node);

    bool insertNode(int vertex, int weight);
    bool deleteNode(int vertex);
};

class Heap
{
private:
    tuple<int, int, int> *queue; // key, value
    int size;
    const int maxSize;

public:
    Heap(int maxSize) : size(0), maxSize(maxSize) { queue = new tuple<int, int, int>[maxSize]; }

    ~Heap() { delete[] queue; }

    int parent(int index) { return (index - 1) / 2; }
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }

    void heapify(int index);
    bool isEmpty();

    void initialize(Node *curr, int index);
    void insert(int weight, int vertex, int parent);
    tuple<int, int, int> extractMin();
};

#endif // ADS_H