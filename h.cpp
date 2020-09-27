#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class UnorderedSet {
    static const size_t start_size_ = 100;
    static const size_t index_of_expansion = 2;
    vector<list<string>> strings_;
    size_t size_;

    void InsertElementsFromVector(const vector<list<string>> &strings) {
        for (const auto &i : strings) {
            for (const auto &j : i) {
                Insert(j);
            }
        }
    }

    size_t Hash(std::string x) {
        return std::hash<string>{}(x) % strings_.size();
    }

public:
    UnorderedSet() : strings_(vector<list<string>>(start_size_)), size_(0) {};

    void ChangeSize() {
        auto tmp = strings_;
        strings_ = vector<list<string>>(size_ * index_of_expansion);
        InsertElementsFromVector(tmp);
    };

    void Insert(const string &x) {
        ++size_;
        if (size_ == strings_.size()) {
            ChangeSize();
        }
        size_t hash = Hash(x);
        strings_[hash].push_back(x);
    }

    void Erase(const string &x) {
        size_t hash = Hash(x);
        strings_[hash].erase(std::find(strings_[hash].begin(), strings_[hash].end(), x));
        --size_;
    }

    bool Find(const string &x) {
        size_t hash = Hash(x);
        return std::find(strings_[hash].begin(), strings_[hash].end(), x) != strings_[hash].end();
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