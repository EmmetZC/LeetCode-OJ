#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
	void reachNextLevel(unordered_set<string> &oneReach, unordered_set<string> &anoReach, unordered_set<string> &meet, unordered_map<string, vector<string>> &prev, unordered_set<string> &dict) {
		unordered_set<string> tmpReach;
		oneReach.swap(tmpReach);	// Now tmpReach stores last oneReach, oneReach is empty

		for (auto curStr : tmpReach) {
			for (unsigned i = 0; i < curStr.size(); ++i) {
				auto neighbor = curStr;
				for (neighbor[i] = 'a'; neighbor[i] <= 'z'; ++neighbor[i]) {
					if (neighbor != curStr) {
						if (oneReach.find(neighbor) != oneReach.end()) {	// Has been reached
							prev[neighbor].push_back(curStr);
						} else if (dict.erase(neighbor) != 0) {		// Still in dict, then erase it
							prev[neighbor].push_back(curStr);			//prev.emplace(neighbor, unordered_set<string>({ curStr }));
							oneReach.insert(neighbor);
						} else if (anoReach.find(neighbor) != anoReach.end()) {		// Has been reached by anoReach
							prev[neighbor].push_back(curStr);			//prev.emplace(neighbor, unordered_set<string>({ curStr }));
							oneReach.insert(neighbor);
							meet.insert(neighbor);
						}
					}
				}
			}
		}
	}

	void walk(vector<vector<string>> &ladders, unordered_map<string, vector<string>> prev, string destiny) {
		vector<vector<string>> tmpLadders;
		while (ladders.back().back() != destiny) {
			ladders.swap(tmpLadders);
			ladders.clear();
			for (auto partialLadder : tmpLadders) {
				auto prevWords = prev[partialLadder.back()];
				for (auto w : prevWords) {
					ladders.push_back(partialLadder);
					ladders.back().push_back(w);
				}
			}
		}
	}
public:
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		unordered_map<string, vector<string>> prevFromStart, prevFromEnd;
		unordered_set<string> reachFromStart({ start }), reachFromEnd({ end });
		unordered_set<string> meet;

		dict.erase(start);
		dict.erase(end);

		while (meet.empty() && !reachFromStart.empty() && !reachFromEnd.empty()) {
			if (reachFromStart.size() < reachFromEnd.size()) {
				reachNextLevel(reachFromStart, reachFromEnd, meet, prevFromStart, dict);
			} else {
				reachNextLevel(reachFromEnd, reachFromStart, meet, prevFromEnd, dict);
			}
		}
		if (meet.empty()) {		// Two BFS search never meet, no ladder
			return vector<vector<string>>();
		} else {				// `meet' stores the words that connect `start' and `end'
			vector<vector<string>> ladders;
			for (auto m : meet) {
				ladders.push_back({ m });
			}
			walk(ladders, prevFromStart, start);		// Walk to `start': meet --> start
			for (auto &l : ladders) {
				reverse(l.begin(), l.end());	// Reverse them as: start --> end
			}
			walk(ladders, prevFromEnd, end);			// Walk to `end' : start --> end
			return ladders;
		}
	}
};

void main() {
	string start = "a";
	string end = "b";
	unordered_set<string> dict = { "a", "b", "c", "d" };
	Solution s;
	vector<vector<string>> ladders = s.findLadders(start, end, dict);
	for (auto l : ladders) {
		for (auto str : l) {
			cout << str << " ";
		}
		cout << endl;
	}
}