#include <cassert>
#include <string>
#include <iostream> // IWYU pragma: keep

using namespace std;
using namespace std::literals;

class Solution {
public:
  string convert(string s, int numRows) {
    int ssz = s.size();

    string result;
    result.reserve(ssz);

    int csz = 1;
    if (numRows > 1)
      csz = 2*(numRows-1);

    int cs = ssz / csz + (ssz % csz > 0);

    for (int k = 0; k < numRows; k++) {
      int i = 0;
      while (i < cs) {
        int f = i*csz + k;
        i++;

        if (f < ssz)
          result += s[f];
        else
          break;

        if (k == 0 || k == numRows - 1)
          continue;

        int n = f + csz - 2*k;
        if (n < ssz)
          result += s[n];
        else
          break;
      }
    }

    return result;
  }
};

int main() {
  Solution s;
  assert(s.convert("PAYPALISHIRING"s, 3) == "PAHNAPLSIIGYIR"s);
  assert(s.convert("PAYPALISHIRING"s, 4) == "PINALSIGYAHRPI"s);
  assert(s.convert("ABCDEF"s, 1) == "ABCDEF"s);
  assert(s.convert("AB"s, 1) == "AB"s);
  assert(s.convert("A"s, 10) == "A"s);
  assert(s.convert("A"s, 1) == "A"s);
}
