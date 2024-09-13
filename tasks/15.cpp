// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <map>        // IWYU pragma: keep
#include <set>        // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/3sum
// name: 15. 3Sum
// constraints:
// 3 <= nums.length <= 3000
// -105 <= nums[i] <= 105

#ifdef __GNUC__
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

static const bool _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return true;
}();

class Solution {
public:
    vector<vector<int>> threeSum(const vector<int>& nums) {
        vector<vector<int>> r;

        map<int, int> m;
        for (size_t i = 0; i < nums.size(); i++) {
            m[nums[i]]++;
        }

        if (m.count(0) && m[0] > 2) {
            r.push_back({0, 0, 0});
        }

        auto b = m.begin();

        while (b->first < 0) {
            auto e = std::prev(m.end());
            while (e->first > 0) {
                int d = -(b->first + e->first);

                if (d >= b->first && d <= e->first && m.count(d)) {
                    if ((d == b->first && m[d] > 1) || (d == e->first && m[d] > 1) ||
                        (d != b->first && d != e->first && m[d] > 0)) {
                        r.push_back({b->first, d, e->first});
                    }
                }
                std::advance(e, -1);
            }
            std::advance(b, 1);
        }

        return r;
    }
};

void print(const vector<vector<int>>& a) {
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

void check(const vector<vector<int>>& a, const vector<vector<int>>& e) {
    print(a);
    cerr << " == ";
    print(e);
    cerr << endl;
    multiset<vector<int>> as{a.begin(), a.end()}, es{e.begin(), e.end()};
    assert(as == es);
}

int main() {
    Solution s;

    check(s.threeSum({-1, 0, 1, 2, -1, -4}), {{-1, -1, 2}, {-1, 0, 1}});
    check(s.threeSum({0, 1, 1}), {});
    check(s.threeSum({0, 0, 0}), {{0, 0, 0}});

    check(s.threeSum({1, 2, -2, -1}), {});
    check(s.threeSum({3, 0, -2, -1, 1, 2}), {{-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}});
    check(s.threeSum({-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4}), {{-4, 0, 4},
                                                               {-4, 1, 3},
                                                               {-3, -1, 4},
                                                               {-3, 0, 3},
                                                               {-3, 1, 2},
                                                               {-2, -1, 3},
                                                               {-2, 0, 2},
                                                               {-1, -1, 2},
                                                               {-1, 0, 1}});

    check(s.threeSum({-1, 0, -1, -5, 0, -5, -5, 5, 5, 0, 1, 2, -1, -4}),
          {{0, 0, 0}, {-1, -1, 2}, {-1, 0, 1}, {-4, -1, 5}, {-5, 0, 5}});
}
