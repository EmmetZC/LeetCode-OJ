#include "Trie.h"

using namespace std;

Trie::Trie() {
	head = new TrieNode(0);
}

Trie::~Trie() {
}

void Trie::addWord(string w) {
	if (w.length() == 0) return;

	auto p = head;
	unsigned idx;
	for (idx = 0; idx < w.length(); ++idx) {
		auto c = w[idx];
		if (p->next[c - A]) {
			p = p->next[c - A];
		} else {
			p->next[c - A] = new TrieNode(c);
			p = p->next[c - A];
			break;
		}
	}
	for (idx++; idx < w.length(); ++idx) {
		auto c = w[idx];
		p->next[c - A] = new TrieNode(c);
		p = p->next[c - A];
	}
	p->isWord = true;
}