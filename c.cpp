#include <iostream>
#include <vector>

using namespace std;

struct Enrollee {
    std::string surname_;
    std::string name_;
    size_t points_;

    Enrollee() = default;

    Enrollee(const std::string &surname, const std::string &name, int inf_point, int math_points, int rus_points)
            : surname_(surname), name_(name), points_(inf_point + math_points + rus_points) {};

    bool operator>(const Enrollee &other) const {
        return points_ > other.points_;
    }

    bool operator==(const Enrollee &other) const {
        return points_ == other.points_;
    }

    friend ostream &operator<<(ostream &os, const Enrollee &enrollee) {
        os << enrollee.surname_ << " " << enrollee.name_;
        return os;
    }
};

void read_arr(vector<Enrollee> &enrollees) {
    size_t n;
    cin >> n;
    enrollees.reserve(n);
    std::string name, surname;
    int inf_points, math_points, rus_points;
    for (size_t i = 0; i < n; ++i) {
        cin >> surname >> name >> inf_points >> math_points >> rus_points;
        enrollees.emplace_back(Enrollee(surname, name, inf_points, math_points, rus_points));
    }
}

template<class RandomIt>
void add_in_result (RandomIt& enrollee, vector<Enrollee> &result) {
    result.emplace_back(*enrollee);
    ++enrollee;
}

template<class RandomIt, typename Comp>
void merge(RandomIt left, RandomIt mid, RandomIt right, Comp comp) {
    vector<typename std::iterator_traits<RandomIt>::value_type> result;
    result.reserve(right - left);
    RandomIt i = left, j = mid;
    while (i < mid && j < right) {
        if (comp(*j, *i)) {
            add_in_result(j, result);
        } else {
            add_in_result(i, result);
        }
    }
    while (i < mid) {
        add_in_result(i, result);
    }
    while (j < right) {
        add_in_result(j, result);
    }
    std::copy(result.begin(), result.end(), left);
}

template <class RandomIt, typename Comp = std::less<>>
void merge_sort(RandomIt left, RandomIt right, Comp comp = Comp()) {
    if (right - left > 1) {
        RandomIt mid = left + (right - left) / 2;
        merge_sort(left, mid, comp);
        merge_sort(mid, right, comp);
        merge(left, mid, right, comp);
    }
}

int main() {
    vector<Enrollee> enrollees;
    read_arr(enrollees);

    merge_sort(enrollees.begin(), enrollees.end(), std::greater<>());

    for (Enrollee enrollee : enrollees) {
        cout << enrollee << "\n";
    }

    enrollees.clear();

    return 0;
}