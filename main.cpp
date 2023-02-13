#include <iostream>
#include "Graph.h"
#include "cassert"
using namespace std;
int main() {
    Graph<char> graph = Graph<char>();

    std::cout << "ADDING NODE TEST" << std::endl;
    char c = 0;
    graph.AddNode();
    assert(graph[0] == c && graph.GetSize() == 1);
   // std::cout << "Checkpoint 1 passed" << std::endl;
    graph.AddNode('a');
    assert(graph[1]=='a' && graph.GetSize() == 2);
   // std::cout << "Checkpoint 2 passed" << std::endl;
    graph.AddNode('q');
    assert(graph[2]=='q' && graph.GetSize() == 3);
   // std::cout << "Checkpoint 3 passed" << std::endl;
    graph.AddNode('g');
    assert(graph[3]=='g' && graph.GetSize() == 4);
   // std::cout << "Checkpoint 4 passed" << std::endl;

    std::cout << "Test passed" << std::endl;

    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;

    //=============================================
    std::cout << "ADDING EDGE TEST" << std::endl;
    graph.AddEdge(0, 1, 3);
    assert(graph.AreConnected(0, 1) && graph.GetEdgeWeight(0, 1) == 3);
    //std::cout << "Checkpoint 1 passed" << std::endl;
    graph.AddEdge(0, 2);
    assert(graph.AreConnected(0, 2) && graph.GetEdgeWeight(0, 2) == 0);
   // std::cout << "Checkpoint 2 passed" << std::endl;
    graph.AddEdge(1, 3, 5);
    assert(graph.AreConnected(1, 3) && graph.GetEdgeWeight(1, 3) == 5);
  //  std::cout << "Checkpoint 3 passed" << std::endl;

    std::cout << "Test passed" << std::endl;
    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;

    //=============================================

    std::cout << "DELETING NODE TEST" << std::endl;

    graph.DeleteNode(2);

    assert(((graph[0] == c) && (graph[1] == 'a') && (graph[2] == 'g') && (graph.GetSize() == 3)));
   // std::cout << "Checkpoint 1 passed" << std::endl;
    graph.DeleteNode(0);
    assert(((graph[0] == 'a') && (graph[1] == 'g') && (graph.GetSize() == 2)));
   // std::cout << "Checkpoint 2 passed" << std::endl;

    std::cout << "Test passed" << std::endl;
    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;

    graph.Clean();

    //============================================

    std::cout << "TOPOLOGICAL SORTING TEST" << std::endl;
    for (int i = 0; i < 6; i++)
        graph.AddNode();
    graph.AddEdge(5, 2);
    graph.AddEdge(5, 0);
    graph.AddEdge(4, 0);
    graph.AddEdge(4, 1);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 1);
    auto sorted = graph.TopologicalSort();
    bool p1 = sorted[0] == 5 && sorted[1] == 4 || sorted[0] == 4 && sorted[1] == 5;
    bool p2 = sorted[2] == 2 && sorted[3] == 3 && sorted[4] == 1 && sorted[5] == 0;
    bool p3 = sorted[2] == 0 && sorted[3] == 2 && sorted[4] == 3 && sorted[5] == 1;
    assert(p1 && (p2 || p3));
    std::cout << "Test passed" << std::endl;

    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;

    graph.Clean();

    //============================================

    std::cout << "DIJKSTRA ALGORITHM TEST" << std::endl;
    for (int i = 0; i < 5; i++)
        graph.AddNode();
    graph.AddEdge(3, 1, 5);
    graph.AddEdge(3, 2, 6);
    graph.AddEdge(2, 1, 7);
    graph.AddEdge(2, 4, 3);
    graph.AddEdge(4, 3, 8);

    auto dij = graph.DijkstraShortestPaths(4);
    int a[] = {INF, 13, 14, 8, 0};
    for (int i = 0; i < dij.size(); i++)
        assert(dij[i] == a[i]);
    std::cout << "Test passed" << std::endl;
    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;
    graph.Clean();

    //============================================

    std::cout << "FLOYD ALGORITHM TEST" << std::endl;
    for (int i = 0; i < 3; i++)
        graph.AddNode();
    graph.AddEdge(0, 1, 5);
    graph.AddEdge(0, 2, 6);
    graph.AddEdge(2, 1, 7);
    graph.AddEdge(2, 0, 3);
    graph.AddEdge(1, 2, 8);

    auto floyd = graph.FloydWarshallShortestPaths();
    auto b = vector<vector<int>>(3, vector<int>(3));
    b[0][0] = 0;
    b[0][1] = 5;
    b[0][2] = 6;
    b[1][0] = 11;
    b[1][1] = 0;
    b[1][2] = 8;
    b[2][0] = 3;
    b[2][1] = 7;
    b[2][2] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            assert(floyd[i][j] == b[i][j]);
    std::cout << "Test passed" << std::endl;
    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;
    graph.Clean();

    //============================================

    std::cout << "FORD ALGORITHM TEST" << std::endl;
    for (int i = 0; i < 5; i++)
        graph.AddNode();
    graph.AddEdge(3, 1, 5);
    graph.AddEdge(3, 2,6);
    graph.AddEdge(2, 1, 7);
    graph.AddEdge(2, 4, 3);
    graph.AddEdge(4, 3,8);
    auto ford = graph.FordBellmanShortestPaths(4);
    int d[] = {INF, 13, 14, 8, 0};
    for (int i = 0; i < graph.GetSize(); i++)
        assert(ford[i] == d[i]);
    std::cout << "Test passed" << std::endl;
    for(int i = 0; i < 30; i++)
        std::cout << "=";
    std::cout << std::endl;
    graph.Clean();


    /* graph.AddNode('c');
     graph.AddNode('w');
     graph.AddNode('p');
     graph.AddEdge(2, 3, 5);
     graph.AddEdge(1, 4, 7);
     graph.AddEdge(0, 2, 3);
     graph.AddEdge(1, 3, 2);
     graph.AddEdge(3, 4, 2);
     graph.DeleteNode(2);

     graph.Print();*/

    //graph.Clean();
    //graph.Print();

    /*if (!graph.HasCycle()) {
        auto a = graph.TopologicalSort();
        for (int i = 0; i < a.size(); i++)
            cout << a[i] << " ";
        cout << endl;
    }
    cout << endl;

    auto path = graph.DijkstraShortestPaths(0);
    int counter = 0;
    for (auto it = path.begin(); it != path.end(); it++){
        cout << counter << ": " << (*it) << endl;
        counter++;
    }
    cout << "Dijkstra\n\n";


    auto path2 = graph.FloydWarshallShortestPaths();
    counter = 0;
    for (auto it = path2.begin(); it != path2.end(); it++){
        cout << counter << ": ";
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            if (*it2 == INF)
                cout << " INF";
            else
                printf("%4d", *it2);
        }
        cout << endl;
        counter++;
    }
    cout << "Floyd\n\n";

    auto path3 = graph.FordBellmanShortestPaths(0);
    counter = 0;
    for (auto it = path3.begin(); it != path3.end(); it++){
        cout << counter << ": " << (*it) << endl;
        counter++;
    }
    cout << "Ford\n\n";*/

    //cout << graph.HasCycle() << endl;
    //cout << graph << endl;
/*
    graph.ChangeEdgeWeight(0, 2, 5);
    graph.AddNode('n');*/

    //cout << graph << endl;


    return 0;
}
