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

// link: https://leetcode.com/problems/reverse-nodes-in-k-group
// name: 25. Reverse Nodes in k-Group
// constraints:
// The number of nodes in the list is n.
// 1 <= k <= n <= 5000
// 0 <= Node.val <= 1000

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
    ListNode* reverseKGroup(ListNode* head, const int k) {
        if (!head || !head->next) return head;

        ListNode dummy{0, head}, *tail{&dummy};
        ListNode *it{nullptr};
        int n{0};

        while (tail && tail->next) {
            head = tail->next;
            it = tail->next;
            n = 1;

            while (it->next && n < k) {
                it = it->next;
                n++;
            }

            if (n != k) break;

            tail->next = it;
            reverseList(it->next, head, it);
            tail = head;
        }

        return dummy.next;
    }

    void reverseList(ListNode *prev, ListNode *head, const ListNode *tail) {
        ListNode* next = head->next;

        while (next != tail->next) {
            head->next = prev;

            prev = head;
            head = next;
            next = next->next;
        }

        head->next = prev;
    }
};

int main() {
    Solution s;

    auto t1{list_util::create({1, 2, 3, 4, 5})};
    list_util::check(s.reverseKGroup(t1, 2), {2, 1, 4, 3, 5});

    auto t2{list_util::create({1, 2, 3, 4, 5})};
    list_util::check(s.reverseKGroup(t2, 3), {3, 2, 1, 4, 5});

    list_util::check(s.reverseKGroup(nullptr, 5), {});

    ListNode* t3{list_util::create({1})};
    list_util::check(s.reverseKGroup(t3, 1), {1});

    ListNode* t4{list_util::create({1, 2})};
    list_util::check(s.reverseKGroup(t4, 2), {2, 1});

    ListNode* t5{list_util::create({1, 2, 3})};
    list_util::check(s.reverseKGroup(t5, 3), {3, 2, 1});
}
