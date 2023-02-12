#include <iostream>
#include "Graph.h"
using namespace std;
int main() {
    Graph<char> graph = Graph<char>(4);
    graph[0] = 'a';
    graph[1] = 'b';
    graph[2] = 'c';
    graph[3] = 'd';
    graph.addEdge(0, 1, 13);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 1, 9);
    //cout << graph.getNode(0);
    cout << graph << endl;

    return 0;
}
