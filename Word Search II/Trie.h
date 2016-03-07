#pragma once
#include <string>
#include <cassert>

#define CHN 26
#define A 'a'

#define UNREACHABLE(X) assert(false && X)

class Trie {
public:
	struct TrieNode {
		char ch;
		std::string word;
		TrieNode* next[CHN];

		TrieNode(char _ch) :ch(_ch), word("") {
			for (unsigned i = 0; i < CHN; ++i) {
				next[i] = nullptr;
			}
		}

		~TrieNode() {
		}
	};

private:
	TrieNode *head;
public:
	Trie() {
		head = new TrieNode(0);
	}
	~Trie() {}

	// Insert Word to Trie
	void addWord(std::string w) {
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
		p->word = w;
	}

	inline TrieNode* const getHead() {
		return head;
	}
};

