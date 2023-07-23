#include "ads.h"

#include <iostream>
#include <tuple>

using namespace std;

/// @brief recursively finds the height of a node
/// @param node the node to find the height of
/// @return the height of the node, 0 if the node is null
int AVLTree::getHeight(Node *node)
{
    if (node == nullptr)
        return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return max(leftHeight, rightHeight) + 1;
}
// time complexity: O(log a)

int AVLTree::getBalance(Node *node)
{
    if (node == nullptr)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}
// time complexity: O(1)

/// @brief prints the tree in order
/// @param node the root of the tree
void AVLTree::inOrder(Node *node)
{
    if (node == nullptr)
        return;

    inOrder(node->left);
    cout << node->vertex + 1 << " ";
    inOrder(node->right);
}
// time complexity: O(a)

void AVLTree::rotateLeft(Node *node)
{
    Node *newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left != nullptr)
        newRoot->left->parent = node;

    newRoot->left = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (newRoot->parent != nullptr)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
    else
        this->root = newRoot;
}
// time complexity: O(1)

void AVLTree::rotateRight(Node *node)
{
    Node *newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right != nullptr)
        newRoot->right->parent = node;
    newRoot->right = node;

    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (newRoot->parent != nullptr)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
    else
        this->root = newRoot;
}
// time complexity: O(1)

Node *AVLTree::getSuccesor(Node *node)
{
    if (node == nullptr)
        return nullptr;

    Node *curr = node->right;
    while (curr->left != nullptr)
        curr = curr->left;
    return curr;
}
// time complexity: O(log a)

/// @brief balances AVL tree
/// @param node the node to start balancing from
void AVLTree::balanceTree(Node *node)
{
    if (node == nullptr)
        return;

    int balance = getBalance(node);
    int leftBalance = getBalance(node->left);
    int rightBalance = getBalance(node->right);

    if (balance > 1 && leftBalance >= 0)
    {
        rotateRight(node);
    }
    else if (balance > 1 && leftBalance < 0)
    {
        rotateLeft(node->left);
        rotateRight(node);
    }
    else if (balance < -1 && rightBalance <= 0)
    {
        rotateLeft(node);
    }
    else if (balance < -1 && rightBalance > 0)
    {
        rotateRight(node->right);
        rotateLeft(node);
    }
    else
        balanceTree(node->parent);
}
// time complexity: O(1)

bool AVLTree::insertNode(int vertex, int weight)
{
    if (this->root == nullptr)
    {
        this->root = new Node(vertex, weight, nullptr);
        return true;
    }

    Node *curr = this->root;
    Node *parent = nullptr;
    while (curr != nullptr)
    {
        parent = curr;
        if (vertex < curr->vertex)
            curr = curr->left;
        else if (vertex > curr->vertex)
            curr = curr->right;
        else
            return false;
    }

    curr = new Node(vertex, weight, parent);
    if (vertex < parent->vertex)
        parent->left = curr;
    else
        parent->right = curr;

    balanceTree(parent);

    return true;
}
// Time complexity: O(log a)

/// @brief deletes a node from the tree
/// @param vertex the vertex of the node to delete
/// @return true if the node was deleted, false if the node was not found
bool AVLTree::deleteNode(int vertex)
{
    if (this->root == nullptr)
        return false;

    Node *curr = this->root;
    Node *parent = nullptr;

    while (curr != nullptr)
    {
        parent = curr->parent;
        if (vertex < curr->vertex)
            curr = curr->left;
        else if (vertex > curr->vertex)
            curr = curr->right;
        else
            break;
    }

    if (curr == nullptr)
        return false;

    if (curr->left == nullptr && curr->right == nullptr)
    {

        delete curr;
        if (parent == nullptr)
            this->root = nullptr;
        else if (parent->left == curr)
            parent->left = nullptr;
        else // if (parent->right == curr)
            parent->right = nullptr;
    }
    else if (curr->left == nullptr || curr->right == nullptr)
    {

        Node *child = curr->left == nullptr ? curr->right : curr->left;
        curr->left != nullptr ? curr->left = nullptr : curr->right = nullptr;

        delete curr;
        child->parent = parent;
        if (parent == nullptr)
            this->root = child;
        else if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;
    }
    else // if (curr->left != nullptr && curr->right != nullptr)
    {

        Node *succesor = getSuccesor(curr);
        int newVertex = succesor->vertex;
        int newWeight = succesor->weight;
        deleteNode(succesor->vertex);

        curr->vertex = newVertex;
        curr->weight = newWeight;
    }

    balanceTree(parent);
    return true;
}
// time complexity: O(log a)

void Heap::heapify(int index)
{
    int left = this->left(index);
    int right = this->right(index);
    int smallest = index;

    if (left < this->size && get<0>(queue[left]) < get<0>(queue[index]))
        smallest = left;
    if (right < this->size && get<0>(queue[right]) < get<0>(queue[smallest]))
        smallest = right;

    if (smallest != index)
    {
        swap(queue[index], queue[smallest]);
        heapify(smallest);
    }
}
// time complexity: O(log a)

bool Heap::isEmpty()
{
    return this->size == 0;
}
// time complexity: O(1)

void Heap::initialize(Node *curr, int index)
{
    if (curr == nullptr)
        return;
    initialize(curr->left, index);
    initialize(curr->right, index);
    this->insert(curr->weight, curr->vertex, index);
}
// time complexity: O(a)

void Heap::insert(int weight, int vertex, int parent)
{
    if (this->size == this->maxSize)
        return;

    int index = this->size;

    while (index > 0 && get<0>(queue[this->parent(index)]) > weight)
    {
        swap(queue[index], queue[this->parent(index)]);
        index = this->parent(index);
    }

    queue[index] = make_tuple(weight, vertex, parent);
    this->size++;
}
// time complexity: O(log a)

tuple<int, int, int> Heap::extractMin()
{
    if (this->size == 0)
        return make_tuple(-1, -1, -1);

    tuple<int, int, int> min = queue[0];
    queue[0] = queue[this->size - 1];
    this->size--;
    heapify(0);
    return min;
}
// time complexity: O(log a)