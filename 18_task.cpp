// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <iterator>   // IWYU pragma: keep
#include <numeric>    // IWYU pragma: keep
#include <set>        // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/4sum
// name: 18. 4Sum
// constraints:
// indices: 0 <= a, b, c, d < n
// indices: a, b, c, and d are distinct.
// indices: nums[a] + nums[b] + nums[c] + nums[d] == target
//
// 1 <= nums.length <= 200
// -10^9 <= nums[i] <= 10^9
// -10^9 <= target <= 10^9

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
    vector<vector<int>> fourSum_original(const vector<int>& _nums, int target) {
        vector<int> nums{_nums.begin(), _nums.end()};
        // start

        if (nums.size() < 4) {
            return {};
        }

        set<vector<int>> r;
        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < nums.size() - 3; i++) {
            for (size_t j = i + 1; j < nums.size() - 2; j++) {
                for (size_t k = j + 1; k < nums.size() - 1; k++) {
                    long s = static_cast<long>(nums[i]) + nums[j] + nums[k];
                    long d = target - s;
                    if (d >= nums[k + 1] && d <= 1000'000'000 && find(nums.begin(), nums.end(), d) != nums.end()) {
                        r.insert({nums[i], nums[j], nums[k], static_cast<int>(d)});
                    }
                }
            }
        }

        return {r.begin(), r.end()};
    }

    vector<vector<int>> fourSum(const vector<int>& _nums, int target) {
        vector<int> nums{_nums.begin(), _nums.end()};
        // start

        if (nums.size() < 4) {
            return {};
        }

        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        long tl = static_cast<long>(target);

        for (size_t i = 0; i < nums.size() - 3; i++) {
            for (size_t j = i + 1; j < nums.size() - 2; j++) {
                size_t l = j+1, r = nums.size() - 1;
                long t2 = tl - nums[i] - nums[j];

                while (l < r) {
                    if (nums[l] + nums[r] < t2) {
                        l++;
                    } else if (nums[l] + nums[r] > t2) {
                        r--;
                    } else {
                        res.push_back({nums[i], nums[j], nums[l], nums[r]});

                        while (l+1 < r && nums[l+1] == nums[l]) l++;
                        while (l < r-1 && nums[r-1] == nums[r]) r--;

                        l++;
                        r--;
                    }
                }

                while (j < l + 1 && j < nums.size() - 2 && nums[j+1] == nums[j]) j++;
            }
            while (i < nums.size() - 3 && nums[i+1] == nums[i]) i++;
        }

        return res;
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

#include <iostream>

int main() {
    Solution s;

    check(s.fourSum({1, 0, -1, 0, -2, 2}, 0), {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}});
    check(s.fourSum({2, 2, 2, 2, 2}, 8), {{2, 2, 2, 2}});

    check(s.fourSum({1000000000,1000000000,1000000000,1000000000}, 0), {});

    check(s.fourSum({2}, 2), {});
    check(s.fourSum({2, 2}, 2), {});
    check(s.fourSum({2, 2, 2}, 2), {});
    check(s.fourSum({2, 2, 2, 2}, 2), {});
    check(s.fourSum({1, 1, 2, 3, 4, 4}, 10), {{1, 1, 4, 4}, {1, 2, 3, 4}});
    check(s.fourSum({1, 1, 2, 3, 4, 4}, 0), {});
    check(s.fourSum({1, -1, 2, 3, 4, -4}, 0), {{-4, -1, 1, 4}, {-4, -1, 2, 3}});
}
