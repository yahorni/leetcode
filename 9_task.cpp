// vim: ts=4 sts=4 sw=4 et

#include <cassert>
#include <climits>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// constraints:
// -2^31 <= x <= 2^31 - 1

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        int y = x, z = 0;

        while (y > 0) {
            if (z > INT_MAX / 10) {
                return false;
            }
            z = z * 10 + y % 10;
            y /= 10;
        }

        cerr << z << endl;
        return z == x;
    }
};

int main() {
    Solution s;
    assert(s.isPalindrome(121));
    assert(!s.isPalindrome(-121));
    assert(!s.isPalindrome(10));

    assert(s.isPalindrome(0));
    assert(s.isPalindrome(1));
    assert(s.isPalindrome(11));
    assert(s.isPalindrome(2112));
    assert(s.isPalindrome(987656789));
    assert(!s.isPalindrome(987654678));
    assert(!s.isPalindrome(998765432));
    assert(s.isPalindrome(2147447412));
    assert(!s.isPalindrome(INT_MAX));
    assert(!s.isPalindrome(INT_MIN));
}
