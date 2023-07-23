#include "graph.h"
#include "illegal_exception.h"

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_VERTICES = 50000;

bool validVertex(int);
bool validWeight(int);

int main()
{
    string cmd;
    Graph *Grid = new Graph(MAX_VERTICES);
    MST *mst = new MST();

    cin >> cmd;

    if (cmd == "LOAD")
    {
        string filename;
        cin >> filename;
        ifstream fin(filename.c_str());
        if (!fin)
        {
            cout << "Error: file not found" << endl;
            return EXIT_FAILURE;
        }

        int maxVertices;
        fin >> maxVertices;

        int a, b, w;
        while (fin >> a >> b >> w)
            Grid->insertEdge(a - 1, b - 1, w - 1);

        cout << "success" << endl;
        fin.close();
    }

    while (cmd != "END")
    {
        if (cmd == "INSERT") // insert a new edge into the graph from
        {                    // vertex a to vertex b with weight w.
            int a, b, w;
            cin >> a >> b >> w;

            if (!validVertex(a) || !validVertex(b) || !validWeight(w))
            {
                try
                {
                    throw illegal_exception("illegal argument");
                }
                catch (illegal_exception &e)
                {
                    e.outputMessage();
                    cin >> cmd;
                    continue;
                }
            }

            Grid->insertEdge(a - 1, b - 1, w - 1) ? cout << "success" << endl : cout << "failure" << endl;
        }
        else if (cmd == "PRINT") // print all vertices adjacent to vertex a
        {
            int a;
            cin >> a;

            if (!validVertex(a))
            {
                try
                {
                    throw illegal_exception("illegal argument");
                }
                catch (illegal_exception &e)
                {
                    e.outputMessage();
                    cin >> cmd;
                    continue;
                }
            }

            Grid->printAdjacent(a - 1) ? cout << endl : cout << "failure" << endl;
        }
        else if (cmd == "DELETE") // delete the vertex 'a' and all edges incident
        {                         // to 'a' from the graph
            int a;
            cin >> a;

            if (!validVertex(a))
            {
                try
                {
                    throw illegal_exception("illegal argument");
                }
                catch (illegal_exception &e)
                {
                    e.outputMessage();
                    cin >> cmd;
                    continue;
                }
            }

            Grid->deleteVertex(a - 1) ? cout << "success" << endl : cout << "failure" << endl;
        }
        else if (cmd == "MST") // Compute the minimum spanning tree of the graph
        {                      // uses Prim's algorithm
            if (Grid->isEmpty())
            {
                cout << "failure" << endl;
                cin >> cmd;
                continue;
            }

            mst->primMST(Grid);
            mst->printMST();
        }
        else if (cmd == "COST") // Determine the cost (the sum of the weights)
        {                       // of the power grid computed via the MST
            if (Grid->isEmpty())
            {
                cout << "cost is 0" << endl;
            }
            else
            {
                mst->primMST(Grid);
                cout << "cost is " << mst->getWeight() << endl;
            }
        }

        cin >> cmd;
    }

    delete Grid;
    delete mst;
    return EXIT_SUCCESS;
}

bool validVertex(int v)
{
    if (v <= 0 || v > MAX_VERTICES)
        return false;
    else
        return true;
}

bool validWeight(int w)
{
    if (w <= 0)
        return false;
    else
        return true;
}