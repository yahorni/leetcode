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

// link: https://leetcode.com/problems/merge-k-sorted-lists
// name: 23. Merge k Sorted Lists
// constraints:
// k == lists.length
// 0 <= k <= 10^4
// 0 <= lists[i].length <= 500
// -10^4 <= lists[i][j] <= 10^4
// lists[i] is sorted in ascending order.
// The sum of lists[i].length will not exceed 10^4.

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

#include "utils.cpp"

class Solution {
public:
    // O(kn*log(k)) - execution
    // O(k) - memory
    ListNode* mergeKLists_original(vector<ListNode*>& lists) {
        ListNode *head{}, *tail{};

        multimap<int, ListNode*> m;
        for (auto* l : lists) {
            if (l) {
                m.insert({l->val, l});
            }
        }

        while (!m.empty()) {
            auto [_, p] = *m.begin();
            m.erase(m.begin());

            if (p->next) {
                m.insert({p->next->val, p->next});
            }

            if (!head) {
                head = p;
                head->next = nullptr;
                tail = head;
            }

            tail->next = p;
            tail = p;
            tail->next = nullptr;
        }

        return head;
    }

    // O(kn*log(k)) - execution
    // O(1) - memory
    ListNode* mergeKLists(vector<ListNode*>& lists) { return divide_and_conquer(lists, 0, lists.size() - 1); }

    ListNode* divide_and_conquer(vector<ListNode*>& lists, size_t begin, size_t end) {
        size_t sz = end - begin + 1;
        cerr << "b " << begin << "; e " << end << "; sz " << sz << endl;
        if (sz > 2) {
            size_t split = sz / 2;
            ListNode* l1 = divide_and_conquer(lists, begin, begin+split);
            ListNode* l2 = divide_and_conquer(lists, begin+split+1, end);
            return merge2Lists(l1, l2);
        } else if (sz == 2) {
            return merge2Lists(lists[begin], lists[end]);
        } else if (sz == 1) {
            return lists[begin];
        } else {
            return {};
        }
    }

    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
        if (!l1 && !l2) {
            return {};
        }

        ListNode head{}, *tail{&head}, **less{};

        while (l1 && l2) {
            less = l1->val < l2->val ? &l1 : &l2;

            tail->next = *less;
            *less = (*less)->next;
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return head.next;
    }
};

int main() {
    Solution s;

    vector<ListNode*> t1;
    t1.push_back(list_util::create({1, 4, 5}));
    t1.push_back(list_util::create({1, 3, 4}));
    t1.push_back(list_util::create({2, 6}));
    list_util::check(s.mergeKLists(t1), {1, 1, 2, 3, 4, 4, 5, 6});

    vector<ListNode*> t2;
    list_util::check(s.mergeKLists(t2), {});

    vector<ListNode*> t3;
    t3.push_back(nullptr);
    list_util::check(s.mergeKLists(t3), {});

    vector<ListNode*> t4;
    t4.push_back(nullptr);
    t4.push_back(nullptr);
    list_util::check(s.mergeKLists(t4), {});

    vector<ListNode*> t5;
    t5.push_back(nullptr);
    t5.push_back(list_util::create({1}));
    list_util::check(s.mergeKLists(t5), {1});

    vector<ListNode*> t6;
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    t6.push_back(nullptr);
    list_util::check(s.mergeKLists(t6), {});
}
