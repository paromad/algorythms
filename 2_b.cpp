#include <iostream>
#include <vector>
#include <queue>

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

    size_t ger_edge_count() const {
        return edge_count_;
    };

    bool is_directed() const {
        return is_directed_;
    }

    virtual void add_edge(const Vertex &start, const Vertex &finish) = 0;

    virtual std::vector<Vertex> get_neighbours(Vertex v) const = 0;

    virtual std::vector<Vertex> get_shortest_path(const Vertex &v, size_t dist, const vector<Vertex> &parent) const = 0;
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

    std::vector<Vertex> get_neighbours(Vertex v) const override {
        return adj_list_[v];
    }

    std::vector<Vertex> get_shortest_path(const Vertex &v, size_t dist, const vector<Vertex> &parent) const override {
        std::vector<Vertex> res;
        if (dist == vertex_count_ + 1) {
            return res;
        }
        res.resize(dist + 1);
        Vertex finish = v;
        res[dist] = finish;
        for (size_t i = 1; i <= dist; ++i) {
            finish = parent[finish];
            res[dist - i] = finish;
        }
        return res;
    }

    bool is_bipart_bfs(const Vertex &start, vector<int> color) {
        queue<Vertex> que;
        que.push(start);
        color[start] = 1;
        while (!que.empty()) {
            Vertex v = que.front();
            que.pop();
            for (Vertex u : get_neighbours(v)) {
                if (color[u] == 0) {
                    color[u] = (color[v] == 1 ? 2 : 1);
                    que.push(u);
                } else {
                    if (color[u] == color[v]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool is_bipart() {
        vector<int> color(vertex_count_ + 1, 0);
        for (Vertex i = 1; i <= vertex_count_; ++i) {
            if (color[i] == 0) {
                if (!is_bipart_bfs(i, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};


int main() {
    size_t vertex_count, edge_count;

    cin >> vertex_count >> edge_count;

    bool is_directed = false;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        int first, second;
        cin >> first >> second;
        graph.add_edge(first, second);
    }

    cout << (graph.is_bipart() ? "YES" : "NO");

    return 0;
}