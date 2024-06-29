// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/integer-to-roman
// constraints:
// 1 <= num <= 3999
//
// I 1
// V 5
// X 10
// L 50
// C 100
// D 500
// M 1000

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

static const bool _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return true;
}();

class Solution {
public:
    string intToRoman(int num) {
        string r;
        char ns[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        char* p = ns;

        while (num > 0) {
            switch (num % 10) {
                case 3:
                    r += p[0];
                case 2:
                    r += p[0];
                case 1:
                    r += p[0];
                    break;
                case 8:
                    r += p[0];
                case 7:
                    r += p[0];
                case 6:
                    r += p[0];
                case 5:
                    r += p[1];
                    break;
                case 4:
                    r += std::string{p[1]} + p[0];
                    break;
                case 9:
                    r += std::string{p[2]} + p[0];
                    break;
                default:
                    break;
            }
            p += 2;
            num /= 10;
        }

        return {r.rbegin(), r.rend()};
    }
};

int main() {
    Solution s;
    assert(s.intToRoman(3749) == "MMMDCCXLIX");
    assert(s.intToRoman(58) == "LVIII");

    assert(s.intToRoman(1) == "I");
    assert(s.intToRoman(2) == "II");
    assert(s.intToRoman(4) == "IV");
    assert(s.intToRoman(9) == "IX");
    assert(s.intToRoman(1994) == "MCMXCIV");
    assert(s.intToRoman(3999) == "MMMCMXCIX");
    assert(s.intToRoman(3888) == "MMMDCCCLXXXVIII");
}
