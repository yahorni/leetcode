// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <cmath>
#include <iostream>   // IWYU pragma: keep
#include <iterator>   // IWYU pragma: keep
#include <map>        // IWYU pragma: keep
#include <numeric>    // IWYU pragma: keep
#include <set>        // IWYU pragma: keep
#include <span>       // IWYU pragma: keep
#include <stack>      // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/remove-duplicates-from-sorted-array
// name: 26. Remove Duplicates from Sorted Array
// constraints:
// 1 <= nums.length <= 3 * 10^4
// -100 <= nums[i] <= 100
// nums is sorted in non-decreasing order.

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
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        size_t k = 1;
        for (size_t i = 1; i < nums.size(); ++i) {
            while (i < nums.size() - 1 && nums[i] == nums[i+1]) ++i;
            if (nums[i] > nums[k-1]) {
                nums[k] = nums[i];
                k++;
            }
        }
        return k;
    }
};

void check(vector<int>& an, int ak, const vector<int>& en, int ek) {
    assert(ak == ek);

    for (int i = 0; i < ek; i++) {
        assert(an[i] == en[i]);
    }
}

int main() {
    Solution s;

    vector<int> t1{1,1,2};
    check(t1, s.removeDuplicates(t1), {1,2}, 2);

    vector<int> t2{0,0,1,1,1,2,2,3,3,4};
    check(t2, s.removeDuplicates(t2), {0,1,2,3,4}, 5);
}
