#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	int longestValidParentheses(string s) {
		s = '|' + s; // sentry
		unsigned N = s.size(), Max = 0;
		vector<unsigned> len(N, 0);

		for (unsigned i = 2; i < N; ++i) {
			if (s[i] == ')') {
				if (s[i - 1] == '(') {
					len[i] = len[i - 2] + 2;
				} else if (s[i - len[i - 1] - 1] == '(') {
					len[i] = len[i - 1] + 2 + len[i - len[i - 1] - 2];
				}
			} else {
				len[i] = 0;
			}
			if (Max < len[i]) Max = len[i];
		}

		return (int)Max;
	}
};

int main() {
	Solution s;
	cout << s.longestValidParentheses("()(())") << endl;
}