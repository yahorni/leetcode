#include <iostream>
#include <vector>
#include <set>
#include <cassert>

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

void check_strings(const vector<string>& a, const vector<string>& e) {
  assert(a == e);
}
