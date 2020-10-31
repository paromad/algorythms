#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

typedef size_t Vertex;

struct Edge {
    Vertex from_;
    Vertex to_;
    size_t weight_;

    Edge() = default;

    Edge(Vertex from, Vertex to, size_t weight) : from_(from), to_(to), weight_(weight) {};

    bool operator>(const Edge &other) const {
        return weight_ > other.weight_;
    }
};

class Graph {
protected:
    size_t vertex_count_;
    size_t edge_count_;
    bool is_directed_;
public:
    Graph(size_t vertex_count, size_t edje_count, bool is_directed) : vertex_count_(vertex_count),
                                                                      edge_count_(edje_count),
                                                                      is_directed_(is_directed) {};

    size_t get_vertex_count() const {
        return vertex_count_;
    };

    size_t get_edge_count() const {
        return edge_count_;
    };

    bool is_directed() const {
        return is_directed_;
    }

    virtual void add_edge(const Edge &edge) = 0;

    const virtual std::vector<Edge> &get_neighbours(Vertex v) const = 0;
};


class AdjListGraph : public Graph {
    vector<vector<Edge>> adj_list_;
public:
    AdjListGraph(size_t vertex_count, size_t edge_count, bool is_directed) : Graph(vertex_count, edge_count,
                                                                                   is_directed) {
        adj_list_.resize(vertex_count + 1);
    };

    void add_edge(const Edge &edge) override {
        adj_list_[edge.from_].push_back(edge);
        if (!is_directed()) {
            adj_list_[edge.to_].push_back(Edge(edge.to_, edge.from_, edge.weight_));
        }
    }

    const std::vector<Edge> &get_neighbours(Vertex v) const override {
        return adj_list_[v];
    }

    size_t Prime_mst_weight(const Vertex &first) {
        unordered_set<Vertex> MST;

        priority_queue<Edge, std::vector<Edge>, std::greater<>> heap;

        size_t MST_weight = 0;

        MST.insert(first);
        for (const Edge &edge : get_neighbours(first)) {
            heap.push(edge);
        }
        for (size_t i = 1; i < vertex_count_; ++i) {
            bool find_edge = false;
            Edge e = heap.top();
            heap.pop();
            while (!find_edge) {
                if (MST.find(e.to_) == MST.end()) {
                    MST_weight += e.weight_;
                    MST.insert(e.to_);
                    find_edge = true;
                } else {
                    e = heap.top();
                    heap.pop();
                }
            }
            for (const Edge &edge : get_neighbours(e.to_)) {
                heap.push(edge);
            }
        }
        return MST_weight;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count, edge_count;

    cin >> vertex_count >> edge_count;

    bool is_directed = false;

    size_t from, to, weight;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        cin >> from >> to >> weight;
        graph.add_edge(Edge(from, to, weight));
    }

    cout << graph.Prime_mst_weight(1);

    return 0;
}