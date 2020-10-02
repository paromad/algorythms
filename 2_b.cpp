#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
bool BFS(const vector<vector<T>> &graph, T start, vector<int> &colors) {
    queue<T> que;
    que.push(start);
    colors[start] = 1;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (size_t u : graph[v]) {
            if (colors[u] == 0) {
                colors[u] = colors[v] == 1 ? 2 : 1;
                que.push(u);
            } else {
                if (colors[u] == colors[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    size_t n, m;

    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (size_t i = 0; i < m; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first - 1].push_back(second - 1);
        graph[second - 1].push_back(first - 1);
    }

    vector<int> distance(n, n + 1);
    vector<int> colors(n, 0);

    bool flag = true;

    for (size_t i = 0; i < n; ++i) {
        if (colors[i] == 0) {
            if (!BFS<int>(graph, i, colors)) {
                flag = false;
                break;
            };
        }
    }

    cout << (flag ? "YES" : "NO");

    return 0;
}