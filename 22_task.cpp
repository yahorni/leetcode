// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <iterator>  // IWYU pragma: keep
#include <numeric>   // IWYU pragma: keep
#include <set>       // IWYU pragma: keep
#include <stack>     // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/generate-parentheses
// name: 22. Generate Parentheses
// constraints: 1 <= n <= 8

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

void check_strings(const vector<string>& a, const vector<string>& e) { assert(a == e); }

// size of the result is a sequence of Catalan numbers
// 1, 2, 5, 14, 42, 132, 429, 1430
// https://oeis.org/A000108
// https://en.wikipedia.org/wiki/Catalan_number

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> r;
        size_t sz;
        switch (n) {
            case 1: sz = 1; break;
            case 2: sz = 2; break;
            case 3: sz = 5; break;
            case 4: sz = 14; break;
            case 5: sz = 42; break;
            case 6: sz = 132; break;
            case 7: sz = 429; break;
            case 8: sz = 1430; break;
            default: sz = 0; break;
        }
        r.reserve(sz);

        string buf = std::string(n - 1, '(') + std::string(n - 1, ')');
        r.push_back(std::string("(") + buf + ")");

        short counter{};
        while (next_permutation(buf.begin(), buf.end())) {
            counter = 1;
            for (size_t i = 0; i < buf.size(); i++) {
                if (buf[i] == '(') counter++;
                else if (buf[i] == ')') counter--;

                if (counter < 0) break;
            }

            if (counter >= 0)
                r.push_back(std::string("(") + buf + ")");
        }

        return r;
    }
};

int main() {
    Solution s;
    check_strings(s.generateParenthesis(3), {"((()))", "(()())", "(())()", "()(())", "()()()"});
    check_strings(s.generateParenthesis(1), {"()"});

    check_strings(s.generateParenthesis(2), {"(())", "()()"});
}
