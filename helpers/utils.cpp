#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include <span>

using namespace std;

void print_matrix(const vector<vector<int>>& a) {
    cerr << "{";
    for (const auto& v : a) {
        cerr << "{";
        for (const auto& i : v) {
            cerr << i << ",";
        }
        cerr << "},";
    }
    cerr << "}";
}

void check_matrices(const vector<vector<int>>& a, const vector<vector<int>>& e) {
    print_matrix(a);
    cerr << " == ";
    print_matrix(e);
    cerr << endl;
    multiset<vector<int>> as{a.begin(), a.end()}, es{e.begin(), e.end()};
    assert(as == es);
}

template<typename T>
void print_vector(const vector<T>& v) {
    cerr << "{";
    for (const auto& e : v) cerr << e << ",";
    cerr << "}";
}

template<typename T>
void print_span(span<const T> s) {
    cerr << "{";
    for (const auto& e : s) cerr << e << ",";
    cerr << "}";
}

template<typename T>
void check_vectors(const vector<T>& a, const vector<T>& e) {
    static int t{};
    std::cout << "test: " << ++t << endl;
    print_vector(a);
    cerr << " == ";
    print_vector(e);
    cerr << endl << endl;
    assert(a == e);
}
