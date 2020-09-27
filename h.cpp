#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class UnorderedSet {
    static const size_t index_ = 2;
    vector<list<string>> arr_;
    size_t size_;
public:
    UnorderedSet() : arr_(vector<list<string>>(100)), size_(0) {};

    void ChangeSize() {
        auto tmp = arr_;
        arr_ = vector<list<string>>(size_ * index_);
        for (const auto &i : tmp) {
            for (const auto &j : i) {
                Insert(j);
            }
        }
    };

    void Insert(const string &x) {
        ++size_;
        if (size_ == arr_.size()) {
            ChangeSize();
        }
        size_t hash = std::hash<string>{}(x) % arr_.size();
        arr_[hash].push_back(x);
    }

    void Erase(const string &x) {
        size_t hash = std::hash<string>{}(x) % arr_.size();
        arr_[hash].erase(std::find(arr_[hash].begin(), arr_[hash].end(), x));
        --size_;
    }

    bool Find(const string &x) {
        size_t hash = std::hash<string>{}(x) % arr_.size();
        return std::find(arr_[hash].begin(), arr_[hash].end(), x) != arr_[hash].end() ? true : false;
    }
};

int main() {
    char command;
    std::string string;

    UnorderedSet set;

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