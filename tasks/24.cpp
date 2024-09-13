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

// link: https://leetcode.com/problems/swap-nodes-in-pairs
// name: 24. Swap Nodes in Pairs
// constraints:
// The number of nodes in the list is in the range [0, 100].
// 0 <= Node.val <= 100

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

#include "listnode.cpp"

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode dummy{0, head}, *tail{&dummy};
        head = head->next;

        while (tail->next && tail->next->next) {
            ListNode *tmp = tail->next;
            tail->next = tail->next->next;
            tmp->next = tail->next->next;
            tail->next->next = tmp;
            tail = tmp;
        }

        return head;
    }
};

int main() {
    Solution s;

    ListNode* t1{list_util::create({1, 2, 3, 4})};
    list_util::check(s.swapPairs(t1), {2, 1, 4, 3});

    list_util::check(s.swapPairs(nullptr), {});

    ListNode* t3{list_util::create({1})};
    list_util::check(s.swapPairs(t3), {1});

    ListNode* t4{list_util::create({1, 2})};
    list_util::check(s.swapPairs(t4), {2, 1});

    ListNode* t5{list_util::create({1, 2, 3})};
    list_util::check(s.swapPairs(t5), {2, 1, 3});

    ListNode* t6{list_util::create({1, 2, 3, 4, 5})};
    list_util::check(s.swapPairs(t6), {2, 1, 4, 3, 5});
}
