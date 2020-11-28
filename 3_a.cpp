#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef size_t Vertex;

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

    virtual void add_edge(const Vertex &start, const Vertex &finish) = 0;

    const virtual std::vector<Vertex>& get_neighbours(Vertex v) const = 0;
};


class AdjListGraph : public Graph {
    vector<vector<Vertex>> adj_list_;
public:
    AdjListGraph(size_t vertex_count, size_t edge_count, bool is_directed) : Graph(vertex_count, edge_count,
                                                                                   is_directed) {
        adj_list_.resize(vertex_count + 1);
    };

    void add_edge(const Vertex &start, const Vertex &finish) override {
        adj_list_[start].push_back(finish);
        if (!is_directed()) {
            adj_list_[finish].push_back(start);
        }
    }

    const std::vector<Vertex>& get_neighbours(Vertex v) const override {
        return adj_list_[v];
    }
};

struct DFSData {
    vector<bool> used;
    vector<size_t> time_in;
    vector<size_t> time_up;
    vector<Vertex> parent;

    DFSData(size_t size) {
        vector<bool> used(size, false);
        vector<size_t> time_in(size);
        vector<size_t> time_up(size);
        vector<Vertex> parent(size, 0);
    }
};

void DFS(const Graph &graph, const Vertex &v, bool is_root, size_t &time, DFSData &data, vector<Vertex> &cut_vertex) {
    data.used[v] = true;
    data.time_in[v] = data.time_up[v] = ++time;
    size_t n_children = 0;
    bool is_cut_vertex = false;
    for (Vertex u : graph.get_neighbours(v)) {
        if (u != data.parent[v]) {
            if (data.used[u]) {
                data.time_up[v] = std::min(data.time_up[v], data.time_in[u]);
            }
            else {
                data.parent[u] = v;
                DFS(graph, u, false, time, data, cut_vertex);
                ++n_children;
                data.time_up[v] = std::min(data.time_up[v], data.time_up[u]);
                if (data.time_in[v] <= data.time_up[u] && !is_root) {
                    is_cut_vertex = true;
                }
            }
        }
    }
    if ((is_root && n_children >= 2) || is_cut_vertex) {
        cut_vertex.push_back(v);
    }
}

vector<Vertex> CutVertexes(const Graph &graph) {
    vector<Vertex> cut_vertexes;
    DFSData data(graph.get_vertex_count() + 1);
    size_t time = 0;
    for (size_t v = 1; v <= graph.get_vertex_count(); ++v) {
        if (!data.used[v]) {
            DFS(graph, v, true, time, data, cut_vertexes);
        }
    }
    return cut_vertexes;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count, edge_count;

    cin >> vertex_count >> edge_count;

    bool is_directed = false;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        Vertex first, second;
        cin >> first >> second;
        graph.add_edge(first, second);
    }

    vector<Vertex> res = CutVertexes(graph);

    cout << res.size() << "\n";

    std::sort(res.begin(), res.end());

    for (const Vertex &vertex : res) {
        cout << vertex << "\n";
    }

    return 0;
}