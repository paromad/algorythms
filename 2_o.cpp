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

    size_t get_edge_count() const {
        return edge_count_;
    };

    bool is_directed() const {
        return is_directed_;
    }

    virtual void add_edge(const Vertex &start, const Vertex &finish) = 0;

    virtual std::vector<Vertex> get_neighbours(Vertex v) const = 0;
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

    friend AdjListGraph Reverse(const AdjListGraph &graph);
};

AdjListGraph Reverse(const AdjListGraph &graph) {
    AdjListGraph new_graph(graph.get_vertex_count(), graph.get_edge_count(), graph.is_directed());
    size_t size = graph.get_vertex_count() + 1;
    for (int i = 1; i < size; ++i) {
        for (int j : graph.get_neighbours(i)) {
            new_graph.adj_list_[j].push_back(i);
        }
    }
    return new_graph;
}

void DFS(const Graph &graph, const Vertex &v, vector<bool> &used, deque<int> &answer) {
    used[v] = true;
    for (Vertex u : graph.get_neighbours(v)) {
        if (!used[u]) {
            DFS(graph, u, used, answer);
        }
    }
    answer.push_front(v);
}

void TopSort(const Graph &graph, vector<bool> &used, deque<int> &answer) {
    for (int i = 1; i <= graph.get_vertex_count(); ++i) {
        if (!used[i]) {
            DFS(graph, i, used, answer);
        }
    }
}

void DFS(const Graph &graph, const Vertex &v, vector<bool> &used, vector<int> &number, size_t counter) {
    used[v] = true;
    number[v] = counter;
    for (Vertex u : graph.get_neighbours(v)) {
        if (!used[u]) {
            DFS(graph, u, used, number, counter);
        }
    }
}

vector<int> Casaraju(const AdjListGraph &graph, vector<bool> &used, size_t &counter) {
    deque<int> order;
    TopSort(graph, used, order);
    AdjListGraph transposed_graph = Reverse(graph);
    used = vector<bool>(graph.get_vertex_count() + 1, false);
    vector<int> number_of_component(graph.get_vertex_count() + 1);
    for (int i : order) {
        if (!used[i]) {
            ++counter;
            DFS(transposed_graph, i, used, number_of_component, counter);
        }
    }
    return number_of_component;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count, edge_count;

    cin >> vertex_count >> edge_count;

    bool is_directed = true;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 0; i < edge_count; ++i) {
        int first, second;
        cin >> first >> second;
        graph.add_edge(first, second);
    }

    vector<bool> used(vertex_count + 1, false);

    size_t counter = 0;

    vector<int> res = Casaraju(graph, used, counter);

    cout << counter << "\n";

    for (auto it = res.begin() + 1; it != res.end(); ++it) {
        cout << *it << " ";
    }

    return 0;
}