#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:
	enum Direction { NONE = 0, DIAG, UP, LEFT };

	string findLCS(string A, string B) {
		auto M = A.size(), N = B.size();
		vector<vector<int> > len(M + 1, vector<int>(N + 1, 0));
		vector<vector<Direction> > trace(M + 1, vector<Direction>(N + 1, NONE));
		for (unsigned i = 1; i <= M; ++i) {
			for (unsigned j = 1; j <= N; ++j) {
				if (A[i] == B[j]) {
					len[i][j] = len[i - 1][j - 1] + 1;
					trace[i][j] = DIAG;
				} else if (len[i - 1][j] >= len[i][j - 1]) {
					len[i][j] = len[i - 1][j];
					trace[i][j] = UP;
				} else {
					len[i][j] = len[i][j - 1];
					trace[i][j] = LEFT;
				}
			}
		}
		stack<char> reversedSeq;
		for (auto i = M, j = N; trace[i][j] != NONE;) {
			switch (trace[i][j]) {
			case DIAG:
				assert(A[i] == B[j] && "A[i]!=B[j]");
				reversedSeq.push(A[i]);
				--i;
				--j;
				break;
			case UP:
				--i;
				break;
			case LEFT:
				--j;
				break;
			default:
				assert(false && "Unreachable.");
			}
		}
		string lcs;
		while (!reversedSeq.empty()) {
			lcs += reversedSeq.top();
			reversedSeq.pop();
		}
		return lcs;
	}
};

int main() {
	Solution s;
}