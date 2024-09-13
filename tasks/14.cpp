// vim: ts=4 sts=4 sw=4 et

#include <algorithm>    // IWYU pragma: keep
#include <cassert>      // IWYU pragma: keep
#include <climits>      // IWYU pragma: keep
#include <iostream>     // IWYU pragma: keep
#include <string>       // IWYU pragma: keep
#include <string_view>  // IWYU pragma: keep
#include <vector>       // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://nor-blog.codeberg.page/posts/2021-10-26-gcc-optimization-pragmas/
// name: 14. Longest Common Prefix
// constraints:
// 1 <= strs.length <= 200
// 0 <= strs[i].length <= 200
// strs[i] consists of only lowercase English letters.

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
    string longestCommonPrefix(const vector<string>& strs) {
        std::string_view sv{strs[0]};

        for (int i = 1; i < std::ssize(strs); i++) {
            std::string_view sv2{strs[i].data(), min(strs[i].size(), sv.size())};
            if (sv.size() > sv2.size()) {
                sv.remove_suffix(sv.size() - sv2.size());
            }

            while (sv.size() > 0 && sv != sv2) {
                sv.remove_suffix(1);
                sv2.remove_suffix(1);
            }

            if (sv.empty()) {
                return {};
            }
        }

        return std::string{sv};
    }
};

int main() {
    Solution s;
    assert(s.longestCommonPrefix({"flower", "flow", "flight"}) == "fl");
    assert(s.longestCommonPrefix({"dog", "racecar", "car"}) == "");

    assert(s.longestCommonPrefix({"", "", ""}) == "");
    assert(s.longestCommonPrefix({"123456789", "123456789", "123456789"}) == "123456789");
    assert(s.longestCommonPrefix({"123456789", "123456789", "12345678"}) == "12345678");
    assert(s.longestCommonPrefix({"123456789", "12345678", "123456789"}) == "12345678");
    assert(s.longestCommonPrefix({"12345678", "123456789", "123456789"}) == "12345678");
    assert(s.longestCommonPrefix({"12345678", "", "123456789"}) == "");
    assert(s.longestCommonPrefix({"12345678"}) == "12345678");
    assert(s.longestCommonPrefix({""}) == "");
    assert(s.longestCommonPrefix({"", "1"}) == "");
    assert(s.longestCommonPrefix({"", "12345", "12345"}) == "");
}
