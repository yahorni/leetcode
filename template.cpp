// vim: ts=4 sts=4 sw=4 et

#include <cassert>
#include <climits>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// constraints:

class Solution {
public:
    int method() {
        return 1;
    }
};

int main() {
    Solution s;
    assert(s.method() == 1);
}
