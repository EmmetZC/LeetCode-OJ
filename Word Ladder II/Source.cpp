#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
private:

public:
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		map<string, unordered_set<string>> prevMap;
		unordered_set<string> nDict(dict.begin(), dict.end());
		nDict.insert(end);
		queue<string> bfs;
		bool reachEnd = false;	// After reachEnd, no more level needs searching
		bfs.push("");
		bfs.push(start);

		unordered_set<string> toErase;

		while (bfs.size() > 1) {
			auto tmpStr = bfs.front();
			bfs.pop();

			if (tmpStr == "") {
				bfs.push("");
				if (reachEnd) {
					break;
				}
				for (auto str : toErase) {
					nDict.erase(str);
				}
				toErase.clear();
				continue;
			}
			for (unsigned i = 0; i < tmpStr.size(); ++i) {
				string neighbor = tmpStr;
				for (char c = 'a'; c <= 'z'; ++c) {
					neighbor[i] = c;
					if (reachEnd) {
						if (neighbor == end) {
							prevMap.at(end).insert(tmpStr);
						} else {
							// Do Nothing
						}
					} else {
						if (neighbor == end) {
							prevMap.emplace(end, unordered_set<string>({ tmpStr }));
							reachEnd = true;
						} else {
							if (neighbor != tmpStr && nDict.find(neighbor) != nDict.end()) {
								if (prevMap.find(neighbor) != prevMap.end()) {	// Already exists
									prevMap.at(neighbor).insert(tmpStr);
								} else {										// First time to get neighbor
									bfs.push(neighbor);
									toErase.insert(neighbor);
									prevMap.emplace(neighbor, unordered_set<string>({ tmpStr }));
								}
							}
						}
					}
				}
			}
		}
		
		if (prevMap.find(end) == prevMap.end()) {	// Cannot reach end
			return vector<vector<string>>();
		}
		
		vector<vector<string>> ladders(1, vector<string>({ end }));

		while (true) {
			auto iterLadder = ladders.begin();
			auto partLadder = *iterLadder;
			auto first = partLadder.front();

			if (first == start) {
				break;
			}

			ladders.erase(iterLadder);

			auto prev = prevMap.at(first);
			for (auto iterPrev = prev.begin(); iterPrev != prev.end(); ++iterPrev) {
				auto tmpLadder(partLadder);
				tmpLadder.insert(tmpLadder.begin(), *iterPrev);
				ladders.push_back(tmpLadder);
			}
		}

		return ladders;
	}
};

int main() {
	string start = "hit";
	string end = "cog";
	unordered_set<string> dict = { "hot", "dot", "dog", "lot", "log" };
	Solution s;
	vector<vector<string>> ladders = s.findLadders(start, end, dict);
	for (auto l : ladders)
	{
		for (auto str : l)
		{
			cout << str << " ";
		}
		cout << endl;
	}
}