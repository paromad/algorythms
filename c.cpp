#include <iostream>
#include <vector>

using namespace std;

struct Enrollee {
    std::string surname_;
    std::string name_;
    int points_;

    Enrollee() = default;

    Enrollee(const std::string &surname, const std::string &name, int inf_point, int math_points, int rus_points)
            : surname_(surname), name_(name), points_(inf_point + math_points + rus_points) {};

    bool operator>=(const Enrollee &other) const {
        return points_ >= other.points_;
    }

    friend ostream &operator<<(ostream &os, const Enrollee &enrollee) {
        os << enrollee.surname_ << " " << enrollee.name_;
        return os;
    }
};

void read_arr(vector<Enrollee> &arr) {
    size_t n;
    cin >> n;
    arr.reserve(n);
    std::string name, surname;
    int inf_points, math_points, rus_points;
    for (size_t i = 0; i < n; ++i) {
        cin >> surname >> name >> inf_points >> math_points >> rus_points;
        arr.emplace_back(Enrollee(surname, name, inf_points, math_points, rus_points));
    }
}

void merge(vector<Enrollee> &arr, size_t left, size_t mid, size_t right) {
    vector<Enrollee> result;
    result.reserve(right - left + 1);
    size_t i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] >= arr[j]) {
            result.emplace_back(arr[i]);
            ++i;
        } else {
            result.emplace_back(arr[j]);
            ++j;
        }
    }
    while (i <= mid) {
        result.emplace_back(arr[i]);
        ++i;
    }
    while (j <= right) {
        result.emplace_back(arr[j]);
        ++j;
    }
    for (i = left; i <= right; ++i) {
        arr[i] = result[i - left];
    }
}

void merge_sort(vector<Enrollee> &arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<Enrollee> arr;
    read_arr(arr);

    merge_sort(arr, 0, arr.size() - 1);

    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << "\n";
    }

    arr.clear();

    return 0;
}