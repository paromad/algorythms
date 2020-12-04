#include <iostream>
#include <vector>


using namespace std;


template<typename T>
class SegmentTree {
    vector<T> tree_;
    vector<size_t> counter_;

    void build(const vector<T> &array, size_t i, size_t L, size_t R) {
        if (L == R - 1) {
            tree_[i] = array[L];
            return;
        }
        build(array, 2 * i + 1, L, (L + R) / 2);
        build(array, 2 * i + 2, (L + R) / 2, R);
        T first = tree_[2 * i + 1], second = tree_[2 * i + 2];
        if (first > second) {
            counter_[i] = counter_[2 * i + 1];
        } else if (first < second) {
            counter_[i] = counter_[2 * i + 2];
        } else {
            counter_[i] = counter_[2 * i + 1] + counter_[2 * i + 2];
        }
        tree_[i] = max(first, second);
    }

public:
    SegmentTree() = delete;

    explicit SegmentTree(const vector<T> &array) {
        tree_.resize(array.size() * 4 - 1);
        counter_.resize(array.size() * 4 - 1, 1);
        build(array, 0, 0, array.size());
    }

    pair<T, size_t> query(size_t i, size_t L, size_t R, size_t l, size_t r) {
        if (R <= l || r <= L) {
            return {0, 0};
        }
        if (l <= L && R <= r) {
            return {tree_[i], counter_[i]};
        }
        pair<T, size_t> left = query(2 * i + 1, L, (L + R) / 2, l, r);
        pair<T, size_t> right = query(2 * i + 2, (L + R) / 2, R, l, r);
        size_t count;
        if (left.first > right.first) {
            count = left.second;
        } else if (left.first < right.first) {
            count = right.second;
        } else {
            count = left.second + right.second;
        }
        return {max(left.first, right.first), count};
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    size_t count;

    cin >> count;

    vector<size_t> array(count);

    for (size_t i = 0; i < count; ++i) {
        size_t awards_count;
        cin >> awards_count;
        array[i] = awards_count;
    }

    SegmentTree<size_t> tree(array);

    size_t query_count;

    cin >> query_count;

    for (size_t i = 0; i < query_count; ++i) {
        size_t l, r;
        cin >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        pair<size_t, size_t> ans = tree.query(0, 0, array.size(), l - 1, r);
        cout << ans.first << " " << ans.second << "\n";
    }

    return 0;
}