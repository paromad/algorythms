#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

typedef size_t Vertex;
typedef unsigned long long ull;

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

template<typename T>
class DSU {
    unordered_map<T, T> prev;
    unordered_map<T, size_t> rank;

    T FindSet(T v) {
        if (v == prev[v]) return v;
        return prev[v] = FindSet(prev[v]);
    };
public:
    DSU() = default;

    DSU(size_t vertex_count) {
        for (size_t i = 1; i <= vertex_count; ++i) {
            prev[i] = i;
            rank[i] = 1;
        }
    }

    inline bool InOneSet(T x, T y) {
        return FindSet(x) == FindSet(y);
    };

    inline void Union(T x, T y) {
        T X = FindSet(x);
        T Y = FindSet(y);
        if (rank[X] < rank[Y]) {
            prev[X] = Y;
        } else if (rank[X] > rank[Y]) {
            prev[Y] = X;
        } else {
            prev[X] = Y;
            ++rank[Y];
        }
    };
};

class Graph {
protected:
    size_t vertex_count_;
    size_t edge_count_;
    bool is_directed_;
    vector<Edge> edges_;
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

    virtual void add_edge(const Edge &edge) {
        edges_.push_back(edge);
    };

    ull Kruscal_mst_weight () {
        DSU<Vertex> dsu(vertex_count_);

        ull MST_weight = 0;

        for (const Edge &edge : edges_) {
            if (!dsu.InOneSet(edge.from_, edge.to_)) {
                MST_weight += edge.weight_;
                dsu.Union(edge.from_, edge.to_);
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

    Graph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        size_t from, to, weight;
        cin >> from >> to >> weight;
        graph.add_edge(Edge(from, to, weight));
    }

    cout << graph.Kruscal_mst_weight();

    return 0;
}