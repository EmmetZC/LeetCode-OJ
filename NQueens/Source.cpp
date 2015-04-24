#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
	vector<int> rstInst;
	vector<vector<int>> solutions;
	int N;
	bool stop;
	void ClearAll() {
		rstInst.clear();
		solutions.clear();
		N = 0;
		btCounts = 0;
	}
	bool Safe(vector<int> v) {
		for (int i = 1; i < N; ++i) {
			if (v[i] == -1) {
				break;
			}
			for (int j = 0; j < i; ++j) {
				if ((v[i] == v[j]) || (v[i] - i == v[j] - j) || (v[i] + i == v[j] + j)) {
					return false;
				}
			}
		}
		return true;
	}
	void BackTrack(int n) {
		for (int i = 0; i < N; ++i) {
			rstInst[n] = i;
			btCounts++;
			if (Safe(rstInst)) {
				if (n == N - 1) {
					solutions.push_back(rstInst);
					stop = true;
					return;
				} else {
					BackTrack(n + 1);
					for (int j = n; j < N; ++j) {
						rstInst[j] = -1;
					}
				}
			}
		}
	}
public:
	int btCounts;
	Solution() {
		ClearAll();
	}
	vector<vector<int>> NQueen(int _N) {
		N = _N;
		rstInst.assign(N, -1);
		stop = false;
		BackTrack(0);
		return solutions;
	}
};

void main() {
	Solution s;
	auto r = s.NQueen(8);
	cout << "Solution Counts: " << r.size() << endl;
	cout << "BackTrack Counts: " << s.btCounts << endl;
}