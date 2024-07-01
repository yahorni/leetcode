// vim: ts=4 sts=4 sw=4 et

#include <cassert>
#include <climits> // IWYU pragma: keep
// #include <string> // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/reverse-integer
// name: 7. Reverse Integer

class Solution {
public:
    int reverse(int x) {
        unsigned r = 0;
        bool s = (x >= 0);
        unsigned max = static_cast<unsigned>(INT_MAX) + 1 - s;

        unsigned v;
        if (x == INT_MIN)
            v = max;
        else
            v = (s ? x : -x);

        while (v > 0) {
            if (r > max / 10)
                return 0;

            char c = v % 10;
            v /= 10;
            r = r * 10 + c;
        }

        return s ? r : -r;
    }
};

int main() {
    Solution s;
    assert(s.reverse(-2147483412) == -2143847412);
    assert(s.reverse(1999999999) == 0);
    assert(s.reverse(1534236469) == 0);
    assert(s.reverse(123) == 321);
    assert(s.reverse(-123) == -321);
    assert(s.reverse(120) == 21);
    assert(s.reverse(INT_MAX) == 0);
    assert(s.reverse(INT_MIN) == 0);
    assert(s.reverse(0) == 0);
    assert(s.reverse(1) == 1);
    assert(s.reverse(-0) == 0);
    assert(s.reverse(-1) == -1);
}
