// vim: ts=4 sts=4 sw=4 et

#include "stdlib.hpp"
#include "utils.cpp"
#include <algorithm>
#include <iterator>
#include <numeric>

// link: https://leetcode.com/problems/trapping-rain-water
// name: 42. Trapping Rain Water
// constraints:
// n == height.length
// 1 <= n <= 2 * 10^4
// 0 <= height[i] <= 10^5

class Solution {
public:
    // int trap(vector<int>& height);
    int trap(const vector<int>& h) {
        int r = 0;
        auto m = max_element(h.rbegin(), h.rend());

        int mh = 0;
        for_each(h.begin(), m.base(),
                 [&mh, &r](auto v) mutable { mh = max(mh, v); r += mh - v; });

        mh = 0;
        for_each(h.rbegin(), m,
                 [&mh, &r](auto v) mutable { mh = max(mh, v); r += mh - v; });

        return r;
    }
};

int main() {
    Solution s;
    assert(s.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6);
    assert(s.trap({4, 2, 0, 3, 2, 5}) == 9);

    assert(s.trap({0, 1, 0, 2, 3, 1, 0, 1, 3, 2, 1, 2, 1}) == 9);
    assert(s.trap({0}) == 0);
    assert(s.trap({1}) == 0);
    assert(s.trap({2}) == 0);
    assert(s.trap({0, 1}) == 0);
    assert(s.trap({1, 0}) == 0);
    assert(s.trap({1, 1}) == 0);
    assert(s.trap({1, 0, 1}) == 1);
    assert(s.trap({1, 1, 1}) == 0);
    assert(s.trap({0, 1, 0}) == 0);
    assert(s.trap({1, 0, 0}) == 0);
    assert(s.trap({2, 0, 1}) == 1);
    assert(s.trap({1, 0, 1, 0, 1}) == 2);
    assert(s.trap({1, 4, 1, 4, 1}) == 3);

    vector<int> b(20000, 0);
    *b.begin() = 100000;
    *b.rbegin() = 100000;
    assert(s.trap(b) == 1999800000);
}
