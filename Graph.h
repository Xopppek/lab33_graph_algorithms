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
    vector<T> _nodes;
    vector<vector<pair<int, int>>> _adjList; // adjacency list of pairs like (nodeIndex, weight)

    //=====================HIDDEN METHODS==========================//
    bool HasCycleRe(bool* visited, const int& nodeIndex) const{
        visited[nodeIndex] = true;
        /*for (int i = 0; i < _nodes.size(); i++){
            cout << visited[i] << " ";
        }
        cout << endl;
        cout << nodeIndex << " nodeIndex " << "\n";*/
        for (int i = 0; i < _adjList[nodeIndex].size(); i++){
            int nodeIndex2 = (_adjList[nodeIndex])[i].first;
            //cout << "iter " << i << endl;
            if (!visited[nodeIndex2])
                return HasCycleRe(visited, nodeIndex2);
            else {
                cout << nodeIndex2 << " found visited, returning true"<< endl;
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

    void AddEdge(const int& firstNodeIndex, const int& secondNodeIndex, const int& weight){
        if (firstNodeIndex < 0 || firstNodeIndex >= _nodes.size() ||
            secondNodeIndex < 0 || secondNodeIndex >= _nodes.size())
            throw "Incorrect Index";
        _adjList[firstNodeIndex].push_back(make_pair(secondNodeIndex, weight));
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
        for (auto it = _adjList[firstNodeIndex].begin(); it < _adjList[firstNodeIndex].end(); it++)
            if ((*it).first == secondNodeIndex)
                return (*it).second;
        return INF;
    }

    void AddNode(const T& newNode){
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
                //return;
                break;
            }
            counter++;
            it1++;
            it2++;
        }
        for (int i = 0; i < _adjList.size(); i++){
            auto it = _adjList[i].begin();
            while (it != _adjList[i].end()){
                //cout << (*it).first << " ";
                if ((*it).first == nodeIndex) {
                    _adjList[i].erase(it);
                    continue;
                }
                if ((*it).first == GetSize())
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

    bool HasCycle(){
        bool visited[_nodes.size()];
        for (int i = 0; i < _nodes.size(); i++)
            visited[i] = false;
        for (int i = 0; i < _nodes.size(); i++) {

            std::cout << visited[i] << " visited \n========================="<< endl;
            if (!visited[i]) {
                //cout << HasCycleRe(visited, i) << endl;
                //HasCycleRe(visited, i);
                bool ans = HasCycleRe(visited, i);
                //bool ans = 1;
                cout << "---------------------------\n" << ans << " is returned\n---------------------"<< endl;
                if (ans) {
                    cout << "aaaaaa" << endl;
                    return true;
                }
            }
        }
        return false;
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

    void Print(){
        for (int i = 0; i < GetSize(); i++){
            cout << i << ": { ";
            for(int j = 0; j < _adjList[i].size(); j++){
                cout << "(" << (_adjList[i])[j].first << "," << (_adjList[i])[j].second << ") ";
            }
            cout << "};" << endl;
        }
        cout << endl;
    }

};

#endif //LAB33_GRAPH_ALGORITHMS_GRAPH_H
