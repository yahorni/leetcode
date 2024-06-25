// vim: ts=4 sts=4 sw=4 et

#include <cassert>
#include <climits>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep

using namespace std;
// using namespace std::literals;

// constraints:
// 0 <= s.length <= 200
// s consists of English letters (lower-case and upper-case), digits (0-9), ' ',
// '+', '-', and '.'.

class Solution {
public:
    int myAtoi(string s) {
    // int myAtoi_runtime(string s) {
        unsigned r = 0;

        bool pos = true;
        bool expect_num = false;

        for (const auto& c : s) {
            if (!expect_num && c == ' ') {
                continue;
            } else if (!expect_num && c == '-') {
                pos = false;
                expect_num = true;
                continue;
            } else if (!expect_num && c == '+') {
                expect_num = true;
                continue;
            } else if (c >= '0' && c <= '9') {
                expect_num = true;

                if (r > INT_MAX / 10) {
                    // multiplication overflow
                    r = (pos ? INT_MAX : INT_MIN);
                    break;
                }
                r *= 10;

                if ((pos && static_cast<unsigned>(c - '0') > INT_MAX - r) ||
                    (!pos && static_cast<unsigned>(c - '0') > INT_MAX - r + 1)) {
                    // addition overflow
                    r = (pos ? INT_MAX : INT_MIN);
                    break;
                }
                r += c - '0';

            } else {
                break;
            }
        }

        return pos ? r : -r;
    }

    // failed attempt to make it optimized by memory
    int myAtoi_memory(string s) {
        bool pos = true;
        unsigned char i = 0;

        while (i < s.size()) {
            if (s[i] == ' ') {
                i++;
                continue;
            } else if (s[i] == '-') {
                i++;
                pos = false;
                break;
            } else if (s[i] == '+') {
                i++;
                break;
            } else {
                break;
            }
        }

        unsigned r = 0;
        for (; i < s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                break;
            }

            if (r > INT_MAX / 10) {
                // multiplication overflow
                r = (pos ? INT_MAX : INT_MIN);
                break;
            }
            r *= 10;

            if ((pos && static_cast<unsigned>(s[i] - '0') > INT_MAX - r) ||
                (!pos && static_cast<unsigned>(s[i] - '0') > INT_MAX - r + 1)) {
                // addition overflow
                r = (pos ? INT_MAX : INT_MIN);
                break;
            }
            r += s[i] - '0';
        }

        return pos ? r : -r;
    }

        // cout << s << ": " << pos << " " << r << " " << (pos ? r : -r) << endl;
};

int main() {
    Solution s;
    assert(s.myAtoi("-") == 0);
    assert(s.myAtoi("+") == 0);
    assert(s.myAtoi("-7") == -7);
    assert(s.myAtoi("+7") == 7);
    assert(s.myAtoi("   +7") == 7);
    assert(s.myAtoi("7") == 7);
    assert(s.myAtoi("42") == 42);
    assert(s.myAtoi(" -042") == -42);
    assert(s.myAtoi("1337c0d3") == 1337);
    assert(s.myAtoi("0-1") == 0);
    assert(s.myAtoi("words and 987") == 0);

    assert(s.myAtoi(std::to_string(INT_MAX)) == INT_MAX);
    assert(s.myAtoi("+"s + std::to_string(INT_MAX)) == INT_MAX);
    assert(s.myAtoi("-"s + std::to_string(INT_MAX)) == -INT_MAX);

    assert(s.myAtoi(std::to_string(INT_MIN)) == INT_MIN);
    assert(s.myAtoi("+"s + std::to_string(INT_MIN)) == 0);
    assert(s.myAtoi(std::to_string(abs(static_cast<int64_t>(INT_MIN)))) == INT_MAX);
}
