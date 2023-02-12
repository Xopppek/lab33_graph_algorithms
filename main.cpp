#include <iostream>
#include "Graph.h"
using namespace std;
int main() {
    Graph<char> graph = Graph<char>();
    //graph[0] = 'a';
    //graph[1] = 'b';
    //graph[2] = 'c';
    //graph[3] = 'd';
    graph.AddNode('a');
    graph.AddNode('b');
    graph.AddNode('c');
    graph.AddNode('d');
    graph.AddEdge(0, 1, 13);
    graph.AddEdge(0, 2, 4);
    graph.AddEdge(1, 3, 10);
    graph.AddEdge(2, 1, 9);
    graph.AddEdge(3, 0, 2);
    //cout << graph.getNode(0);
   // cout << graph << endl;
   //graph.Print();


    //graph.DeleteEdge(3, 0);
    //graph.ChangeNode(3, 'l');

    //cout << graph << endl;


    graph.DeleteEdge(3, 0);
    //graph.DeleteNode(3);
   /* graph.DeleteEdge(0, 1);
    graph.DeleteEdge(3, 0);
    graph.AddEdge(1, 0, 4);
    graph.DeleteNode(3);*/
    //graph.DeleteEdge(2, 1);
    graph.Print();

    if (!graph.HasCycle()) {
        auto a = graph.TopologicalSort();
        for (int i = 0; i < a.size(); i++)
            cout << a[i] << " ";
        cout << endl;
    }

    //cout << graph.HasCycle() << endl;
    //cout << graph << endl;
/*
    graph.ChangeEdgeWeight(0, 2, 5);
    graph.AddNode('n');*/

    //cout << graph << endl;


    return 0;
}
