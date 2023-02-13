#ifndef LAB33_GRAPH_ALGORITHMS_GRAPH_H
#define LAB33_GRAPH_ALGORITHMS_GRAPH_H

#include <iostream>
#include "vector"
#include "utility"
#include "algorithm"
#include "set"

const int INF = 32000;


template <typename T>
class Graph{
private:
    std::vector<T> _nodes;
    std::vector<std::vector<std::pair<int, int>>> _adjList; // adjacency list of pairs like (nodeIndex, weight)

    //=====================HIDDEN METHODS==========================//
    void TopSort(const int& startIndex, std::vector<bool>* visited, std::vector<int>* order){
        (*visited)[startIndex] = true;
        for (int i = 0; i < GetSize(); i++){
            if(!(*visited)[i] && GetEdgeWeight(startIndex, i) != INF){
                TopSort(i, visited, order);
            }
        }
        (*order).push_back(startIndex);
    }

    bool HasCycleRe(std::vector<bool>* visited, const int& nodeIndex) const{
        (*visited)[nodeIndex] = true;
        for (int i = 0; i < _adjList[nodeIndex].size(); i++){
            int nodeIndex2 = (_adjList[nodeIndex])[i].first;
            //cout << "iter " << i << endl;
            if (!(*visited)[nodeIndex2])
                return HasCycleRe(visited, nodeIndex2);
            else {
                return true;
            }
        }
        return false;
    }

public:
    //=======================CONSTRUCTORS==========================//

    Graph() {}
    Graph(int numberOfNodes) : _adjList(numberOfNodes), _nodes(numberOfNodes){}
    ~Graph() = default;

    //=========================METHODS===========================//

    void AddEdge(const int& firstNodeIndex, const int& secondNodeIndex, const int& weight = 0){
        if (firstNodeIndex < 0 || firstNodeIndex >= _nodes.size() ||
            secondNodeIndex < 0 || secondNodeIndex >= _nodes.size())
            throw "Incorrect Index";
        for (int i = 0; i < _adjList[firstNodeIndex].size(); i++){
            if (_adjList[firstNodeIndex][i].first == secondNodeIndex) throw "Edge already exists";
        }
        _adjList[firstNodeIndex].push_back(std::make_pair(secondNodeIndex, weight));
    }

    void ChangeEdgeWeight(const int& firstNodeIndex, const int& secondNodeIndex, const int& weight){
        for (auto it = _adjList[firstNodeIndex].begin(); it != _adjList[firstNodeIndex].end(); it++){
            if ((*it).first == secondNodeIndex) {
                (*it).second = weight;
                return;
            }
        }
        throw "No Edge";
    };

    void DeleteEdge(const int& firstNodeIndex, const int& secondNodeIndex){
        if (firstNodeIndex < 0 || firstNodeIndex >= _nodes.size())
            return;
        auto it = _adjList[firstNodeIndex].begin();
        while(it != _adjList[firstNodeIndex].end()){
            if ((*it).first == secondNodeIndex){
                _adjList[firstNodeIndex].erase(it);
                return;
            }
            it++;
        }
    }

    int GetEdgeWeight(const int& firstNodeIndex, const int& secondNodeIndex) const{
        if (firstNodeIndex == secondNodeIndex) return 0;
        for (auto it = _adjList[firstNodeIndex].begin(); it < _adjList[firstNodeIndex].end(); it++)
            if ((*it).first == secondNodeIndex)
                return (*it).second;
        return INF;
    }

    bool AreConnected(const int& firstNodeIndex, const int& secondNodeIndex){
        return (!(GetEdgeWeight(firstNodeIndex, secondNodeIndex)==INF));
    }

    void AddNode(const T& newNode = 0){
        _nodes.push_back(newNode);
        _adjList.resize(_adjList.size()+1);
    }

    void ChangeNode(const int& nodeIndex, const T& newNode){
        if (nodeIndex < 0 || nodeIndex >= _nodes.size())
            throw "Invalid Index";
        _nodes[nodeIndex] = newNode;
    }

    void DeleteNode(const int& nodeIndex){
        if (nodeIndex < 0 || nodeIndex >= _nodes.size())
            throw "Invalid Index";
        auto it1 = _nodes.begin();
        auto it2 = _adjList.begin();
        int counter = 0;
        while (it1 != _nodes.end()){
            if (counter == nodeIndex) {
                _nodes.erase(it1);
                _adjList.erase(it2);
                break;
            }
            counter++;
            it1++;
            it2++;
        }
        for (int i = 0; i < _adjList.size(); i++){
            auto it = _adjList[i].begin();
            while (it != _adjList[i].end()){
                if ((*it).first == nodeIndex) {
                    _adjList[i].erase(it);
                    continue;
                }
                if ((*it).first > nodeIndex)
                    (*it).first--;
                it++;
            }
        }
    }

    T GetNode(int nodeIndex) const{
        if (nodeIndex < 0 || nodeIndex >= _nodes.size()) throw "Incorrect Index";
        return _nodes[nodeIndex];
    }

    int GetSize() const{
        return _nodes.size();
    }

    void Print(){
        for (int i = 0; i < GetSize(); i++){
            std::cout << i << ": { ";
            for(int j = 0; j < _adjList[i].size(); j++){
                std::cout << "(" << (_adjList[i])[j].first << "," << (_adjList[i])[j].second << ") ";
            }
            std::cout << "};" << std::endl;
        }
        std::cout << std::endl;
    }

    void Clean(){
        for (int i = GetSize()-1; i >= 0; i--)
            DeleteNode(i);
    }

    //============================ALGORITHMS=========================//

    bool HasCycle(){
        auto visited = std::vector<bool> (GetSize(), false);
        for (int i = 0; i < GetSize(); i++)
            visited[i] = false;
        for (int i = 0; i < GetSize(); i++) {
            if (!visited[i]) {
                bool ans = HasCycleRe(&visited, i);
                if (ans) {
                    return true;
                }
            }
            for (int i = 0; i < GetSize(); i++)
                visited[i] = false;
        }
        return false;
    }

    std::vector<int> TopologicalSort(){
        auto visited = std::vector<bool>(GetSize(), false);
        auto order = std::vector<int>();

        for (int i = 0; i < GetSize(); i++){
            if (!visited[i]){
                TopSort(i, &visited, &order);
            }
        }
        std::reverse(order.begin(), order.end());
        return order;
    }

    std::vector<int> DijkstraShortestPaths(const int& startNodeIndex){
        auto paths = std::vector<int>(GetSize(), INF);
        auto visited = std::vector<bool>(GetSize(), false);
        paths[startNodeIndex] = 0;
        std::set<std::pair<int, int>> nodes;
        nodes.insert(std::make_pair(startNodeIndex, 0));
        while(!nodes.empty()){
            int nodeIndex = nodes.begin()->first;
            nodes.erase(nodes.begin());
            for (auto it = _adjList[nodeIndex].begin(); it < _adjList[nodeIndex].end(); it++){
                int nextNodeIndex = (*it).first;
                int nextNodeWeight = (*it).second;
                if (paths[nextNodeIndex] > paths[nodeIndex] + nextNodeWeight){
                    nodes.erase(std::make_pair(nextNodeIndex, paths[nextNodeIndex]));
                    paths[nextNodeIndex] = paths[nodeIndex] + nextNodeWeight;
                    nodes.insert(std::make_pair(nextNodeIndex, paths[nextNodeIndex]));
                }
            }
        }
        return paths;
    }

    std::vector<std::vector<int>> FloydWarshallShortestPaths(){
        auto paths = std::vector<std::vector<int>>(GetSize(), std::vector<int>(GetSize(), INF));
        for (int i = 0; i < GetSize(); i++)
            paths[i][i] = 0;
        for (int i = 0; i < GetSize(); i++)
            for (auto it = _adjList[i].begin(); it != _adjList[i].end(); it++)
                paths[i][(*it).first] = (*it).second;
        for (int throughNodeIndex = 0; throughNodeIndex < GetSize(); throughNodeIndex++)
            for (int startNodeIndex = 0; startNodeIndex < GetSize(); startNodeIndex++)
                for (int endNodeIndex = 0; endNodeIndex < GetSize(); endNodeIndex++)
                    if (paths[startNodeIndex][throughNodeIndex] != INF && paths[throughNodeIndex][endNodeIndex] != INF)
                        paths[startNodeIndex][endNodeIndex] = std::min(paths[startNodeIndex][endNodeIndex],
                                                                       paths[startNodeIndex][throughNodeIndex] +
                                                                       paths[throughNodeIndex][endNodeIndex]);

        return paths;
    }

    std::vector<int> FordBellmanShortestPaths(const int& startNodeIndex){
        auto paths = std::vector<int>(GetSize(), INF);
        paths[startNodeIndex] = 0;
        bool isChanged = true;
        while (isChanged){
            isChanged = false;
            for (int i = 0; i < GetSize(); i++){
                for (int j = 0; j < _adjList[i].size(); j++){
                    if (paths[_adjList[i][j].first] > paths[i] + _adjList[i][j].second && paths[i] != INF) {
                        paths[_adjList[i][j].first] = paths[i] + _adjList[i][j].second;
                        isChanged = true;
                    }
                }
            }
        }
        return paths;
    }

    //========================OPERATORS=========================//

    T& operator[] (int nodeIndex){
        if (nodeIndex < 0 || nodeIndex >= _nodes.size()) throw "Incorrect Index";
        return _nodes[nodeIndex];
    }

    friend std::ostream& operator<<(std::ostream& os, Graph<T>& graph) {
        int size = graph.GetSize();
        for (int i = 0; i < size; i++) {
            os << i << " : { ";
            for (int j = 0; j < size; j++) {
                if (graph.GetEdgeWeight(i, j) != INF)
                    os << "(" << j << "," << graph.GetEdgeWeight(i, j) << ") ";
            }
            os << "};\n";
        }
        return os;
    }
};

#endif //LAB33_GRAPH_ALGORITHMS_GRAPH_H
