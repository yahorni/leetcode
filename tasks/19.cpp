// vim: ts=4 sts=4 sw=4 et

#include <algorithm>  // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <iterator>   // IWYU pragma: keep
#include <numeric>    // IWYU pragma: keep
#include <set>        // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

using namespace std;
using namespace std::literals;

// link: https://leetcode.com/problems/remove-nth-node-from-end-of-list
// name: 19. Remove Nth Node From End of List
// constraints:
// The number of nodes in the list is sz.
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz

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

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0),
          next(nullptr) {}
    ListNode(int x)
        : val(x),
          next(nullptr) {}
    ListNode(int x, ListNode* next)
        : val(x),
          next(next) {}
};

void check(ListNode* a, const vector<int> e) {
    static int test_n = 0;
    test_n++;
    cerr << "test: " << test_n << endl;

    ListNode* p = a;
    for (size_t i = 0; i < e.size(); i++, p = p->next) {
        // cerr << "p->val = " << p->val << "; e[i] = " << e[i] << endl;
        assert(p != nullptr);
        assert(p->val == e[i]);
    }

    assert(p == nullptr);
}

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head->next == nullptr) {
            return nullptr;
        }

        ListNode* p1 = head;
        for (int i = 0; i < n; i++) {
            p1 = p1->next;
        }

        if (p1 == nullptr) {
            return head->next;
        }

        ListNode* p2 = head;

        while (p1->next) {
            p1 = p1->next;
            p2 = p2->next;
        }

        p2->next = p2->next->next;

        return head;
    }
};

int main() {
    Solution s;

    // Input: head = [1,2,3,4,5], n = 2
    // Output: [1,2,3,5]
    ListNode a5{5};
    ListNode a4{4, &a5};
    ListNode a3{3, &a4};
    ListNode a2{2, &a3};
    ListNode a1{1, &a2};
    check(s.removeNthFromEnd(&a1, 2), {1, 2, 3, 5});

    // Input: head = [1], n = 1
    // Output: []
    ListNode b1{1};
    check(s.removeNthFromEnd(&b1, 1), {});

    // Input: head = [1,2], n = 1
    // Output: [1]
    ListNode c2{2};
    ListNode c1{1, &c2};
    check(s.removeNthFromEnd(&c1, 1), {1});

    ListNode d3{3};
    ListNode d2{2, &d3};
    ListNode d1{1, &d2};
    check(s.removeNthFromEnd(&d1, 3), {2, 3});

    ListNode e3{3};
    ListNode e2{2, &e3};
    ListNode e1{1, &e2};
    check(s.removeNthFromEnd(&e1, 1), {1, 2});

    ListNode f2{2};
    ListNode f1{1, &f2};
    check(s.removeNthFromEnd(&f1, 1), {1});

    ListNode g2{2};
    ListNode g1{1, &g2};
    check(s.removeNthFromEnd(&g1, 2), {2});

    ListNode a5_1{5};
    ListNode a4_1{4, &a5_1};
    ListNode a3_1{3, &a4_1};
    ListNode a2_1{2, &a3_1};
    ListNode a1_1{1, &a2_1};
    check(s.removeNthFromEnd(&a1_1, 5), {2, 3, 4, 5});

    ListNode a5_2{5};
    ListNode a4_2{4, &a5_2};
    ListNode a3_2{3, &a4_2};
    ListNode a2_2{2, &a3_2};
    ListNode a1_2{1, &a2_2};
    check(s.removeNthFromEnd(&a1_2, 1), {1, 2, 3, 4});
}
