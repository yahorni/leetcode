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

// link: https://leetcode.com/problems/3sum-closest
// name: 16. 3Sum Closest
// constraints:
// 3 <= nums.length <= 500
// -1000 <= nums[i] <= 1000
// -10^4 <= target <= 10^4

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
    int threeSumClosest(const vector<int>& nums, int target) {
        vector<int> v{nums.begin(), nums.end()};
        return _threeSumClosest(v, target);
    }

    int _threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        if (target < -3000) {
            return nums[0] + nums[1] + nums[2];
        }

        if (target > 3000) {
            return nums[nums.size() - 1] + nums[nums.size() - 2] + nums[nums.size() - 3];
        }

        int s = 0;
        int min_d = INT_MAX;

        for (auto v1 = nums.begin(); v1 != nums.end() - 2; v1++) {
            for (auto v2 = v1 + 1; v2 != nums.end() - 1; v2++) {
                int d = target - *v1 - *v2;

                auto v3 = lower_bound(v2 + 1, nums.end(), d);

                if (v3 == nums.end()) {
                    v3 = nums.end() - 1;
                } else if (v3 - 1 != v2) {
                    if (abs(*(v3 - 1) - d) < abs(*v3 - d)) {
                        v3 = v3 - 1;
                    }
                }

                int stmp = *v1 + *v2 + *v3;

                if (min_d > abs(target - stmp)) {
                    s = stmp;
                    min_d = abs(target - s);
                }
            }
        }

        return s;
    }
};

int main() {
    Solution s;
    assert(s.threeSumClosest({-1, 2, 1, -4}, 1) == 2);
    assert(s.threeSumClosest({0, 0, 0}, 1) == 0);

    assert(s.threeSumClosest({0, 3, 97, 102, 200}, 300) == 300);
    assert(s.threeSumClosest(
               {-13,  592,  -501, 770,  -952, -675, 322,  -829, -246, 657,  608,  485,  -112, 967,  -30,  182,  -969,
                559,  -286, -64,  24,   365,  -158, 701,  535,  -429, -217, 28,   948,  -114, -536, -711, 693,  23,
                -958, -283, -700, -672, 311,  314,  -712, -594, -351, 658,  747,  949,  70,   888,  166,  495,  244,
                -380, -654, 454,  -281, -811, -168, -839, -106, 877,  -216, 523,  -234, -8,   289,  -175, 920,  -237,
                -791, -976, -509, -4,   -3,   298,  -190, 194,  -328, 265,  150,  210,  285,  -176, -646, -465, -97,
                -107, 668,  892,  612,  -54,  -272, -910, 557,  -212, -930, -198, 38,   -365, -729, -410, 932,  4,
                -565, -329, -456, 224,  443,  -529, -428, -294, 191,  229,  112,  -867, -163, -979, 236,  -227, -388,
                -209, 984,  188,  -549, 970,  951,  -119, -146, 801,  -554, 564,  -769, 334,  -819, -356, -724, -219,
                527,  -405, -27,  -759, 722,  -774, 758,  394,  146,  517,  870,  -208, 742,  -782, 336,  -364, -558,
                -417, 663,  -914, 536,  293,  -818, 847,  -322, 408,  876,  -823, 827,  167},
               7175) == 2921);
    assert(s.threeSumClosest({-1000, -5, -5, -5, -5, -5, -5, -1, -1, -1}, -14) == -15);
    assert(s.threeSumClosest({0, 1, 2}, 0) == 3);

    assert(s.threeSumClosest({22, 36, -2, -7, -8}, 21) == 21);
    assert(s.threeSumClosest({1000, 1000, 1000, 999}, 10000) == 3000);
    assert(s.threeSumClosest({-1000, -1000, -1000, -999}, -10000) == -3000);
}
