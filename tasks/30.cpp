// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
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

// link: https://leetcode.com/problems/substring-with-concatenation-of-all-words
// name: Substring with Concatenation of All Words
// constraints:
// 1 <= s.length <= 10^4
// 1 <= words.length <= 5000
// 1 <= words[i].length <= 30
// s and words[i] consist of lowercase English letters.

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
    vector<int> findSubstring(string s, const vector<string>& words) {
        size_t ss = s.size(), ks = words.size(), ws = words[0].size();

        if (ss < ws) return {};

        vector<int> r;

        map<string, pair<int, int>, std::less<>> w;
        for (auto& word : words)
            w[word].first++;

        string_view sv{s};

        for (size_t i{0}; i < ws; i++) {
            size_t wleft{ks};
            size_t shift{0};
            for (auto& [_, p] : w)
                p.second = 0;

            for (size_t j{i}; j < ss - ws + 1; j += ws) {
                if (!w.count(sv.substr(j, ws))) {
                    wleft = ks;
                    shift = 0;
                    for (auto& [_, p] : w)
                        p.second = 0;
                    continue;
                }

                auto& p = w.find(sv.substr(j, ws))->second;
                if (p.first == p.second) {
                    w.find(sv.substr(j - (ks - wleft) * ws, ws))->second.second--;
                    shift++;
                    wleft++;
                    j -= ws;
                } else {
                    p.second++;
                    wleft--;
                }

                if (wleft == 0) {
                    r.push_back(j - (ks - 1) * ws);
                }
            }
        }

        return r;
    }
};

#include "utils.cpp"

int main() {
    Solution s;
    check_vectors(s.findSubstring("barfoothefoobarman", vector<string>{"foo", "bar"}), {0, 9});
    check_vectors(s.findSubstring("wordgoodgoodgoodbestword", vector<string>{"word", "good", "best", "word"}), {});
    check_vectors(s.findSubstring("barfoofoobarthefoobarman", vector<string>{"bar", "foo", "the"}), {6, 9, 12});

    check_vectors(s.findSubstring("wordgoodbestwordword", vector<string>{"word", "good", "best", "word"}), {0, 4});
    check_vectors(s.findSubstring("iwordgoodbestwordword", vector<string>{"word", "good", "best", "word"}), {1, 5});
    check_vectors(
        s.findSubstring("aslkdjiwordgoodbestwordwordaslkjdash", vector<string>{"word", "good", "best", "word"}),
        {7, 11});
    check_vectors(s.findSubstring("asl", vector<string>{"word", "good", "best", "word"}), {});

    check_vectors(s.findSubstring("aa", vector<string>{"aa"}), {0});
    check_vectors(s.findSubstring("abab", vector<string>{"ab"}), {0, 2});
    check_vectors(s.findSubstring("aa", vector<string>{"a"}), {0, 1});
    check_vectors(s.findSubstring("a", vector<string>{"a"}), {0});

    check_vectors(s.findSubstring("aaaaaaaaaaaaaa", vector<string>{"aa", "aa"}), {0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9});
}
