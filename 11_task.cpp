// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

static const bool _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return true;
}();

// link: https://leetcode.com/problems/container-with-most-water
// constraints:
// n == height.length
// 2 <= n <= 10^5
// 0 <= height[i] <= 10^4

class Solution {
public:
    // max((b.x - a.x) * min(a.y, b.y))

    // int maxArea(vector<int>& height) {
    int maxArea(const vector<int>& height) {
        int s = 0, ax = 0, bx = height.size() - 1;

        while (ax < bx) {
            int ay = height[ax], by = height[bx];
            s = max(s, (bx - ax) * min(ay, by));
            ay < by ? ax++ : bx--;
        }

        return s;
    }
};

int main() {
    Solution s;
    assert(s.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
    assert(s.maxArea({1, 1}) == 1);

    assert(s.maxArea({}) == 0);
    assert(s.maxArea({0}) == 0);
    assert(s.maxArea({1}) == 0);
    assert(s.maxArea({2}) == 0);
    assert(s.maxArea({1, 2}) == 1);
    assert(s.maxArea({2, 2}) == 2);
    assert(s.maxArea({1, 0, 0}) == 0);
    assert(s.maxArea({1, 0, 2}) == 2);
    assert(s.maxArea({3, 1, 2}) == 4);
    assert(s.maxArea({100000, 2, 1}) == 2);
}
