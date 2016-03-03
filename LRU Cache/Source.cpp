#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

class LRUCache {
private:

	struct Node {
		int key;
		int value;
		Node *l, *r;

		Node(int k, int v) :key(k), value(v), l(NULL), r(NULL) {}
	};

	int capacity;
	unordered_map<int, Node*> cache;
	Node *head, *tail;

	void unlinkNode(Node *p) {
		p->l->r = p->r;
		if (p->r)
			p->r->l = p->l;
	}

	void mvTail(Node *p) {
		if (p == tail) return;
		unlinkNode(p);
		tail->r = p;
		p->l = tail;
		tail = p;
	}

	void rmHead() {
		auto p = head->r;
		unlinkNode(p);
		cache.erase(cache.find(p->key));
		delete p;
	}

	void add(int key, int value) {
		auto p = new Node(key, value);
		tail->r = p;
		p->l = tail;
		tail = p;
		cache[key] = p;
	}

public:
	LRUCache(int _capacity) :capacity(_capacity) {
		cache = unordered_map<int, Node*>();
		head = new Node(-1, -1);
		tail = head;
	}

	int get(int key) {
		auto f = cache.find(key);
		if (f != cache.end()) {
			auto p = f->second;
			mvTail(p);
			return p->value;
		} else {
			return -1;
		}
	}

	void set(int key, int value) {
		auto f = cache.find(key);
		if (f != cache.end()) {
			auto p = f->second;
			p->value = value;
			mvTail(p);
		} else {
			if (cache.size() == capacity) {
				rmHead();
			}
			add(key, value);
		}
	}
};

int main() {

}