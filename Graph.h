#ifndef LAB33_GRAPH_ALGORITHMS_GRAPH_H
#define LAB33_GRAPH_ALGORITHMS_GRAPH_H

#include <iostream>
#include "vector"
#include "utility"
#include "algorithm"

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
        /*for (int i = 0; i < _nodes.size(); i++){
            std::cout << (*visited)[i] << " ";
        }
        std::cout << std::endl;
        std::cout << nodeIndex << " nodeIndex " << "\n";*/
        for (int i = 0; i < _adjList[nodeIndex].size(); i++){
            int nodeIndex2 = (_adjList[nodeIndex])[i].first;
            //cout << "iter " << i << endl;
            if (!(*visited)[nodeIndex2])
                return HasCycleRe(visited, nodeIndex2);
            else {
                //std::cout << nodeIndex2 << " found visited, returning true"<< std::endl;
                return true;
            }
        }
        return false;
    }
/*
    void topological_depth_search(const std::size_t &start_pos, array_sequence<bool> *is_used,
                                  array_sequence<std::size_t> *new_order) const noexcept {
        is_used->operator[](start_pos) = true;

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i) && this->get_edge_weight(start_pos, i) != SIZE_MAX_LOCAL) {
                topological_depth_search(i, is_used, new_order);
            }
        }

        new_order->append(start_pos);
    }*/

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
        for (auto it = _adjList[firstNodeIndex].begin(); it < _adjList[firstNodeIndex].end(); it++)
            if ((*it).first == secondNodeIndex)
                return (*it).second;
        return INF;
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

    //============================ALGORITHMS=========================//

    bool HasCycle(){
        auto visited = std::vector<bool> (GetSize(), false);
        for (int i = 0; i < GetSize(); i++)
            visited[i] = false;
        for (int i = 0; i < GetSize(); i++) {
            //std::cout << visited[i] << " visited \n========================="<< std::endl;
            if (!visited[i]) {
                //cout << HasCycleRe(visited, i) << endl;
                //HasCycleRe(visited, i);
                bool ans = HasCycleRe(&visited, i);
                //bool ans = 1;
                //std::cout << "---------------------------\n" << ans << " is returned\n---------------------"<< std::endl;
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

    /*array_sequence<std::size_t> *topological_sort() const noexcept {
        auto is_used = new array_sequence<bool>(_graph->get_size(), false);
        auto new_order_vertexes = new array_sequence<std::size_t>(_graph->get_size(), false);
        new_order_vertexes->erase_all();

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i)) {
                topological_depth_search(i, is_used, new_order_vertexes);
            }
        }

        delete is_used;

        std::reverse(new_order_vertexes->begin(), new_order_vertexes->end());

        return new_order_vertexes;
    }*/


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
            std::cout << i << ": { ";
            for(int j = 0; j < _adjList[i].size(); j++){
                std::cout << "(" << (_adjList[i])[j].first << "," << (_adjList[i])[j].second << ") ";
            }
            std::cout << "};" << std::endl;
        }
        std::cout << std::endl;
    }

};

#endif //LAB33_GRAPH_ALGORITHMS_GRAPH_H
