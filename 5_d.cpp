#include <iostream>
#include <vector>


using namespace std;


template<typename T>
class SparceTable {
    vector<vector<T>> table_;
    vector<size_t> log_;
public:
    SparceTable() = delete;

    explicit SparceTable(const vector<T> &array) {
        size_t n = array.size();
        log_.resize(n + 1, 0);
        log_[1] = 0;
        for (size_t i = 2; i <= n; ++i) {
            log_[i] = log_[i / 2] + 1;
        }

        table_ = std::vector<std::vector<T>>(n, std::vector<T>(log_[n] + 1));
        for (size_t i = 0; i < n; ++i) {
            table_[i][0] = array[i];
        }

        for (size_t j = 1; (1u << j) <= n; ++j) {
            for (size_t i = 0; i + (1u << (j - 1)) < n; ++i) {
                table_[i][j] = min(table_[i][j - 1], table_[i + (1u << (j - 1))][j - 1]);
            }
        }
    }

    T query(size_t left, size_t right) {
        size_t k = log_[right - left];
        return min(table_[left][k], table_[right - (1u << k)][k]);
    }
};


size_t next_growth(size_t growth) {
    return (23 * growth + 21563) % 16714589;
}


size_t next_l(size_t left, size_t ans, size_t i, size_t count) {
    return (17 * left + 751 + ans + 2 * i) % count + 1;
}


size_t next_r(size_t right, size_t ans, size_t i, size_t count) {
    return (13 * right + 593 + ans + 5 * i) % count + 1;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    size_t count, query_count, growth;

    cin >> count >> query_count >> growth;

    vector<size_t> array(count);

    for (size_t i = 0; i < count; ++i) {
        array[i] = growth;
        growth = next_growth(growth);
    }

    size_t size = 1;
    for (; size < count; size <<= 1u) {};
    array.resize(size, SIZE_MAX);

    SparceTable table(array);

    size_t left, right;

    cin >> left >> right;

    size_t ans;

    for (size_t i = 1; i < query_count; ++i) {
        ans = table.query(min(left, right) - 1, max(left, right));
        left = next_l(left, ans, i, count);
        right = next_r(right, ans, i, count);
    }

    ans = table.query(min(left, right) - 1, max(left, right));

    cout << left << " " << right << " " << ans;

    return 0;
}