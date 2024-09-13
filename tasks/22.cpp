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

// size of the result is a sequence of Catalan numbers
// 1, 2, 5, 14, 42, 132, 429, 1430
// https://oeis.org/A000108
// https://en.wikipedia.org/wiki/Catalan_number

class Solution {
public:
    size_t getSize(int n) {
        switch (n) {
            case 1: return 1;
            case 2: return 2;
            case 3: return 5;
            case 4: return 14;
            case 5: return 42;
            case 6: return 132;
            case 7: return 429;
            case 8: return 1430;
            default: return 0;
        }
    }

    vector<string> generateParenthesis_original(int n) {
        vector<string> r;
        r.reserve(getSize(n));

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

    vector<string> generateParenthesis(int n) {
        vector<string> r;
        r.reserve(getSize(n));
        string buf{"("s};
        recurse(r, buf, 1, n-1);
        return r;
    }

    void recurse(vector<string>& r, string& buf, int opened, int left_to_open) {
        // 0. nothing to add
        if (opened == 0 && left_to_open == 0) {
            r.push_back(buf);
            return;
        }

        // 1. add opened
        if (left_to_open > 0) {
            buf.push_back('(');
            recurse(r, buf, opened+1, left_to_open-1);
            buf.pop_back();
        }

        // 2. add closed
        if (opened != 0) {
            buf.push_back(')');
            recurse(r, buf, opened-1, left_to_open);
            buf.pop_back();
        }
    }
};

void check_strings(const vector<string>& a, const vector<string>& e) { assert(a == e); }

int main() {
    Solution s;
    check_strings(s.generateParenthesis(3), {"((()))", "(()())", "(())()", "()(())", "()()()"});
    check_strings(s.generateParenthesis(1), {"()"});

    check_strings(s.generateParenthesis(2), {"(())", "()()"});
}
