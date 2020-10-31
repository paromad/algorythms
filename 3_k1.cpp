#include <iostream>
#include <vector>
#include <unordered_map>
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

    inline T FindSet(T v) {
        T original_v = v;
        while (v != prev[v]) {
            v = prev[v];
        }
        while (original_v != v) {
            prev[original_v] = v;
            original_v = prev[original_v];
        }
        return v;
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
        if (X == Y) {
            exit(-1);
        }
        if (rank[X] < rank[Y]) {
            prev[X] = Y;
            rank[Y] += rank[X];
        } else {
            prev[Y] = X;
            rank[X] += rank[Y];
        }
    };
};

ull Kruscal_mst_weight (size_t vertex_count, const vector<Edge> &edges) {
    DSU<Vertex> dsu(vertex_count);

    ull MST_weight = 0;

    for (const Edge &edge : edges) {
        if (!dsu.InOneSet(edge.from_, edge.to_)) {
            MST_weight += edge.weight_;
            dsu.Union(edge.from_, edge.to_);
        }
    }

    return MST_weight;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    size_t vertex_count, edge_count;
    cin >> vertex_count >> edge_count;

    vector<Edge> edges;

    for (size_t i = 0; i < edge_count; ++i) {
        size_t from, to;
        ull weight;
        cin >> from >> to >> weight;
        edges.push_back(Edge(from, to, weight));
    }

    cout << Kruscal_mst_weight(vertex_count, edges);

    return 0;
}