#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
void BFS(const vector<vector<T>> &graph, T start, vector<int> &distance, vector<T> &parents) {
    queue<T> que;
    que.push(start);
    distance[start] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (size_t u : graph[v]) {
            if (distance[u] > distance[v] + 1) {
                distance[u] = distance[v] + 1;
                parents[u] = v;
                que.push(u);
            }
        }
    }
}

int main() {
    size_t n, m, start, finish;

    cin >> n >> m;
    cin >> start >> finish;

    --start;
    --finish;

    vector<vector<int>> graph(n);

    for (size_t i = 0; i < m; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first - 1].push_back(second - 1);
        graph[second - 1].push_back(first - 1);
    }

    vector<int> distance(n, n + 1);
    vector<int> parents(n, -1);

    BFS<int>(graph, start, distance, parents);

    int dist = distance[finish];
    if (dist == n + 1) {
        cout << "-1";
        return 0;
    }

    cout << dist << "\n";

    vector<int> res(dist + 1);

    res[dist--] = finish;

    while (dist >= 0) {
        finish = parents[finish];
        res[dist--] = finish;
    }

    for (int i : res) {
        cout << i + 1 << " ";
    }

    return 0;
}