#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		const auto M = dungeon.size();
		const auto N = dungeon[0].size();

		vector<vector<int>> minHPs(dungeon);
		for (auto i = M; i > 0;) {
			--i;
			for (auto j = N; j > 0;) {
				--j;
				if (i < M - 1 && j < N - 1) {
					int minRequiredHP = min(minHPs[i+1][j], minHPs[i][j+1]);
					minHPs[i][j] = max(0, minRequiredHP - dungeon[i][j]);
				} else if (i < M - 1) {
					minHPs[i][j] = max(0, minHPs[i + 1][j] - dungeon[i][j]);
				} else if (j < N - 1) {
					minHPs[i][j] = max(0, minHPs[i][j + 1] - dungeon[i][j]);
				} else {
					minHPs[i][j] = max(0, 0 - dungeon[i][j]);
				}
			}
		}
		return minHPs[0][0] + 1;
	}
};

vector<string> split(string str, string pattern) {
	string::size_type pos, i = 0;
	vector<string> result;
	str += pattern;
	while( i < str.size()) {
		pos = str.find(pattern, i);
		if (pos < str.size()) {
			string s = str.substr(i, pos - i);
			result.push_back(s);
		}
		i = pos + pattern.length();
	}
	return result;
}

int main() {
	ifstream fin("Input.txt");
	string sin;
	vector<vector<int>> dungeon;
	while (getline(fin, sin)) {
		vector<int> line;
		vector<string> str = split(sin, " ");
		for (auto c : str) {
			line.push_back(stoi(c));
		}
		dungeon.push_back(line);
	}
	Solution s;
	int minHP = s.calculateMinimumHP(dungeon);
	for(auto line:dungeon) {
		for (auto c : line) {
			cout << c << "\t";
		}
		cout << endl;
	}
	cout << minHP;
	return 0;
}