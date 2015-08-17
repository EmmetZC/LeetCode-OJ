#include <string>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
	int minDistance(string w1, string w2) {
		// Initialization
		vector<vector<int>> D;
		typedef decltype(D.size()) SizeType;

		for (SizeType i = 0; i <= w1.length(); ++i) {
			vector<int> d(w2.length() + 1, 0);
			D.push_back(d);
		}
		for (SizeType i = 0; i < D.size(); ++i) {
			D[i][0] = i;
		}
		for (SizeType j = 0; j < D[0].size(); ++j) {
			D[0][j] = j;
		}

		// Dynamic Programming
		for (SizeType i = 1; i <= w1.length(); ++i) {
			for (SizeType j = 1; j <= w2.length(); ++j) {
				if (w1[i - 1] == w2[j - 1]) {
					D[i][j] = D[i - 1][j - 1];
				} else {
					int minDist = D[i - 1][j - 1];
					int minId = 0;					// Replace
					if (minDist > D[i - 1][j]) {
						minDist = D[i - 1][j];
						minId = 1;					// Delete
					}
					if (minDist > D[i][j - 1]) {
						minDist = D[i][j - 1];
						minId = 2;					// Insert
					}
					D[i][j] = minDist + 1;
				}
			}
		}
		return D[w1.length()][w2.length()];
	}
};

void main() {
	Solution s;
	cout << s.minDistance("thanks", "thins") << endl;
}