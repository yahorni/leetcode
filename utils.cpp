#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

void print_matrix(const vector<vector<int>>& a) {
    cerr << "{";
    for (const auto& v : a) {
        cerr << "{";
        for (const auto& i : v) {
            cerr << i << ",";
        }
        cerr << "},";
    }
    cerr << "}";
}

void check_matrices(const vector<vector<int>>& a, const vector<vector<int>>& e) {
    print_matrix(a);
    cerr << " == ";
    print_matrix(e);
    cerr << endl;
    multiset<vector<int>> as{a.begin(), a.end()}, es{e.begin(), e.end()};
    assert(as == es);
}

void check_strings(const vector<string>& a, const vector<string>& e) {
  assert(a == e);
}

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

namespace list_util {

ListNode* create(const vector<int>& l) {
    ListNode* head{nullptr};

    for (auto it = l.rbegin(); it != l.rend(); it++) {
        head = new ListNode{*it, head};
    }

    return head;
}

void print(ListNode* l) {
    cerr << "{";
    while (l != nullptr) {
        cerr << l->val;
        l = l->next;
        if (l) {
            cerr << ",";
        }
    }
    cerr << "}" << endl;
}

void clear(ListNode* l) {
    while (l) {
        auto n = l->next;
        delete l;
        l = n;
    }
}

void check(ListNode* a, const vector<int>& e) {
    static int test_n = 0;
    cerr << "test: " << ++test_n << endl;

    print(a);

    ListNode* p = a;
    for (size_t i = 0; i < e.size(); i++, p = p->next) {
        cerr << "p->val = " << p->val << "; e[i] = " << e[i] << endl;
        assert(p != nullptr);
        assert(p->val == e[i]);
    }

    assert(p == nullptr);

    clear(a);
}

}
