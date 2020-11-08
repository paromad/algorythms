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

    virtual std::vector<Vertex> get_shortest_path(const Vertex &start, const Vertex &finish) const = 0;
};


void BFS(const Graph &graph, const Vertex &start, vector<size_t> &distance, vector<Vertex> &parents);


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

    std::vector<Vertex> get_shortest_path(const Vertex &start, const Vertex &finish) const override {
        vector<size_t> distance(vertex_count_ + 1, vertex_count_ + 1);
        vector<Vertex> parent(vertex_count_ + 1);

        BFS(*this, start, distance, parent);
        size_t dist = distance[finish];

        std::vector<Vertex> res;
        if (dist == vertex_count_ + 1) {
            return res;
        }
        res.resize(dist + 1);
        Vertex end = finish;
        res[dist] = end;
        for (size_t i = 1; i <= dist; ++i) {
            end = parent[end];
            res[dist - i] = end;
        }
        return res;
    }
};

void BFS(const Graph &graph, const Vertex &start, vector<size_t> &distance, vector<Vertex> &parents) {
    queue<Vertex> que;
    que.push(start);
    distance[start] = 0;
    while (!que.empty()) {
        Vertex v = que.front();
        que.pop();
        for (Vertex u : graph.get_neighbours(v)) {
            if (distance[u] > distance[v] + 1) {
                distance[u] = distance[v] + 1;
                parents[u] = v;
                que.push(u);
            }
        }
    }
};


int main() {
    size_t vertex_count, edge_count;
    Vertex start, finish;

    cin >> vertex_count >> edge_count;
    cin >> start >> finish;

    bool is_directed = false;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        Vertex first, second;
        cin >> first >> second;
        graph.add_edge(first, second);
    }

    vector<Vertex> res = graph.get_shortest_path(start, finish);

    if (!res.size()) {
        cout << -1;
        return 0;
    }

    cout << res.size() - 1 << "\n";

    for (Vertex vertex : res) {
        cout << vertex << " ";
    }

    return 0;
}