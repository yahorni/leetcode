// vim: ts=4 sts=4 sw=4 et

#include "includes.hpp"
#include <climits>

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/minimum-window-substring
// name: 76. Minimum Window Substring
// constraints:
// m == s.length
// n == t.length
// 1 <= m, n <= 10^5
// s and t consist of uppercase and lowercase English letters.

class Solution {
public:
    string minWindow(string s, string t) {
        struct counter {
            int required = 0;
            int obtained = 0;

            bool is_over() const { return obtained > required; }
        };
        // could be optimized with "std::array<58, int> required";
        std::unordered_map<char, counter> st;
        for (auto c : t)
            st[c].required++;

        size_t has_needed{};
        std::string_view r;

        size_t i = 0;
        while (i < s.size() && !st.count(s[i]))
            i++;
        if (i == s.size()) return {};
        size_t win = i;

        for (; i < s.size(); ++i) {
            if (!st.count(s[i])) continue;

            auto& stc = st[s[i]];
            stc.obtained++;

            if (!stc.is_over()) {
                has_needed++;
            } else if (s[win] == s[i]) {
                while (st[s[win]].is_over()) {
                    st[s[win]].obtained--;
                    while (!st.count(s[++win]));
                }
            }

            if (has_needed == t.size() && (r.empty() || i - win + 1 < r.size()))
                r = string_view{s.data() + win, i - win + 1};
        }

        return string{r};
    }
};

int main() {
    Solution s;
    assert(s.minWindow("ADOBECODEBANC", "ABC") == "BANC");
    assert(s.minWindow("a", "a") == "a");
    assert(s.minWindow("a", "aa") == "");

    assert(s.minWindow("ab", "a") == "a");

    assert(s.minWindow("abc--abc-cba----abc", "abcabc") == "abc-cba");
    assert(s.minWindow("abcd", "abcd") == "abcd");
    assert(s.minWindow("ab", "ab") == "ab");
    assert(s.minWindow("ab", "aa") == "");
}
