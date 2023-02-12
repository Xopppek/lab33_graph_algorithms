#ifndef LAB33_GRAPH_ALGORITHMS_GRAPH_H
#define LAB33_GRAPH_ALGORITHMS_GRAPH_H

#include <iostream>
#include "vector"
#include "utility"

const int INF = 32000;

using namespace std;

template <typename T>
class Graph{
private:
    int _numberOfNodes;
    vector<T> _nodes;
    vector<vector<pair<int, int>>> _adjList; // adjacency list of pairs like (nodeIndex, weight)
public:
    //=======================CONSTRUCTORS==========================//

    Graph() {_numberOfNodes = 0;}
    Graph(int numberOfNodes) : _numberOfNodes(numberOfNodes), _adjList(numberOfNodes), _nodes(numberOfNodes){}
    ~Graph() = default;

    //======================GRAPH METHODS===========================//

    void addEdge(const int& firstNodeIndex, const int& secondNodeIndex, const int& weight){
        _adjList[firstNodeIndex].push_back(make_pair(secondNodeIndex, weight));
    }

    void addNode(const T& newNode){
        _nodes.push_back(newNode);
        _numberOfNodes++;
        _adjList.resize(_adjList.size()+1);
    }

    int getEdgeWeight(const int& firstNodeIndex, const int& secondNodeIndex) const{
        for (auto it = _adjList[firstNodeIndex].begin(); it < _adjList[firstNodeIndex].end(); it++)
            if ((*it).first == secondNodeIndex)
                return (*it).second;
        return INF;
    }

    T getNode(int nodeIndex) const{
        if (nodeIndex < 0 || nodeIndex >= _nodes.size()) throw "incorrect index";
        return _nodes[nodeIndex];
    }

    int GetSize() const{
        return _numberOfNodes;
    }

    //========================OPERATORS=========================//

    T& operator[] (int nodeIndex){
        if (nodeIndex < 0 || nodeIndex >= _nodes.size()) throw "incorrect index";
        return _nodes[nodeIndex];
    }

    friend std::ostream& operator<<(std::ostream& os, Graph<T>& graph) {
        int size = graph.GetSize();
        for (int i = 0; i < size; i++) {
            os << i << " : { ";
            for (int j = 0; j < size; j++) {
                if (graph.getEdgeWeight(i, j) != INF)
                    os << "(" << j << "," << graph.getEdgeWeight(i, j) << ") ";
            }
            os << "};\n";
        }
        return os;
    }
};

#endif //LAB33_GRAPH_ALGORITHMS_GRAPH_H
