#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

template<typename T>
class UnorderedSet {
    static const size_t START_SIZE = 100;
    static const size_t INDEX_OF_EXPLANSION = 2;
    vector<list<T>> elements_;
    size_t size_;

    void InsertElementsFromVector(const vector<list<T>> &strings) {
        for (const auto &i : strings) {
            for (const auto &j : i) {
                Insert(j);
            }
        }
    }

    size_t Hash(T x) {
        return std::hash<T>{}(x) % elements_.size();
    }

public:
    UnorderedSet() : elements_(vector<list<T>>(START_SIZE)), size_(0) {};

    void ChangeSize() {
        auto tmp = elements_;
        elements_ = vector<list<T>>(size_ * INDEX_OF_EXPLANSION);
        InsertElementsFromVector(tmp);
    };

    void Insert(const T &x) {
        ++size_;
        if (size_ == elements_.size()) {
            ChangeSize();
        }
        size_t hash = Hash(x);
        elements_[hash].push_back(x);
    }

    void Erase(const T &x) {
        size_t hash = Hash(x);
        elements_[hash].erase(std::find(elements_[hash].begin(), elements_[hash].end(), x));
        --size_;
    }

    bool Find(const T &x) {
        size_t hash = Hash(x);
        return std::find(elements_[hash].begin(), elements_[hash].end(), x) != elements_[hash].end();
    }
};

int main() {
    char command;
    std::string string;

    UnorderedSet<std::string> set;

    cin >> command;
    while (command != '#') {
        cin >> string;

        switch (command) {
            case '+' :
                set.Insert(string);
                break;
            case '-' :
                set.Erase(string);
                break;
            case '?' :
                cout << (set.Find(string) ? "YES\n" : "NO\n");
                break;
        }

        cin >> command;
    }

    return 0;
}