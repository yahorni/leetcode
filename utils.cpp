#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

void print_vector(const vector<vector<int>>& a) {
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

void check_vectors(const vector<vector<int>>& a, const vector<vector<int>>& e) {
    print_vector(a);
    cerr << " == ";
    print_vector(e);
    cerr << endl;
    multiset<vector<int>> as{a.begin(), a.end()}, es{e.begin(), e.end()};
    assert(as == es);
}

