#include <iostream>
#include <vector>
#include <string>
#include "Trie.h"

using namespace std;

static const int MOV[4][2] = {
	{ -1, 0 }, { 1, 0 },
	{ 0, -1 }, { 0, 1 }
};

class Solution {
	unsigned M, N;
	Trie t;
	vector<string> found;

	typedef vector<vector<char>> BD;
	typedef pair<unsigned, unsigned> POS;

	void buildTrie(vector<string>& Ws) {
		for (auto w : Ws) {
			t.addWord(w);
		}
	}

	bool outOfRange(unsigned x, unsigned y) {
		return x < 0
			|| x >= M
			|| y < 0
			|| y >= N;
	}

	void findFrom(BD& Bd, Trie::TrieNode* h, const unsigned x, const unsigned y) {
		auto &ch = Bd[x][y];
		
		if (ch < 0) return;

		h = h->next[ch - A];
		if (h == nullptr) {
			return;
		} else {
			ch = -ch;
			if (h->word != "") {
				found.push_back(h->word);
				h->word = "";
			}
		}

		for (unsigned i = 0; i < 4; ++i) {
			unsigned nx = x + MOV[i][0], ny = y + MOV[i][1];
			if (!outOfRange(nx, ny)) {
				findFrom(Bd, h, nx, ny);
			}
		}

		ch = -ch;
	}
public:
	vector<string> findWords(vector<vector<char>>& Bd, vector<string>& Ws) {
		found = vector<string>();

		M = Bd.size();
		if (M == 0 || Ws.size() == 0) return found;
		N = Bd[0].size();
		if (N == 0) return found;

		buildTrie(Ws);

		for (unsigned i = 0; i < M; ++i) {
			for (unsigned j = 0; j < N; ++j) {
				findFrom(Bd, t.getHead(), i, j);
			}
		}
		return found;
	}
};

int main() {
	vector<vector<char>> bd = {
		{'o', 'a', 't', 'p'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'e', 'r'},
		{'i', 'f', 'l', 'v'}
	};
	vector<string> ws = {"oath", "pea", "eat", "rain"};

	Solution s;
	auto result = s.findWords(bd, ws);
	for (auto s : result) {
		cout << s << endl;
	}
}