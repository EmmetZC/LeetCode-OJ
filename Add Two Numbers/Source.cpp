#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	inline int getVal(ListNode *p) {
		if (p != NULL) return p->val;
		return 0;
	}
	inline ListNode* getNext(ListNode *p) {
		if (p != NULL) return p->next;
		return NULL;
	}
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = new ListNode(-1);
		ListNode* p = head;
		int c = 0;
		while (l1 || l2 || c) {
			p->next = new ListNode(0);
			p = p->next;
			p->val = getVal(l1) + getVal(l2) + c;
			c = p->val >= 10;
			p->val = p->val - c * 10;
			l1 = getNext(l1);
			l2 = getNext(l2);
		}
		p = head->next;
		delete head;
		return p;
	}
};