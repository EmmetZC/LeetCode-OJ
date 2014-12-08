#include <iostream>
#include <string>

using namespace std;

#define COUNT 127
#define FIRST 1
#define MAXINT ((unsigned int)(-1) >> 1)

class Solution
{
private:
	string W = "";
	int *cnt_s, *cnt_w;

	void AppendW(char);
	void PopW();
	void ClearRedundancy();
	bool CheckWindow();

public:
	string minWindow(string Ori, string Sub)
	{
		decltype(W.size()) minWindow = MAXINT, endIndex = -1;
		int cs[COUNT] = { 0 }, cw[COUNT] = { 0 };
		cnt_s = cs;
		cnt_w = cw;

		/*Initialize cnt_s*/
		for (auto ch : Sub){
			cnt_s[ch - FIRST]++;
		}

		/*Shift Window*/
		for (decltype(Ori.size()) i = 0; i < Ori.size(); ++i){
			char ch = Ori[i];
			AppendW(ch);
			if (CheckWindow() && (W.size() < minWindow)){
				minWindow = W.size();
				endIndex = i;
			}
		}

		/*Output Minimum Window*/
		if (endIndex == -1) {
			return "";
		}
		else {
			return Ori.substr(endIndex - minWindow + 1, minWindow);
		}
	}
};


void Solution::AppendW(char ch){
	W += ch;
	cnt_w[ch - FIRST]++;
	ClearRedundancy();
}

void Solution::PopW(){
	cnt_w[W[0] - FIRST]--;
	W.erase(W.begin());
	ClearRedundancy();
}

void Solution::ClearRedundancy(){
	if (W.empty()) {
		return;
	}
	char ch = W[0];
	if (cnt_w[ch - FIRST] > cnt_s[ch - FIRST]){
		PopW();
	}
}

bool Solution::CheckWindow(){
	for (int i = 0; i < COUNT; ++i){
		if (cnt_w[i] < cnt_s[i]){
			return false;
		}
	}
	return true;
}

int main(){
	string S, T;
	cin >> S >> T;

	Solution s;
	cout << s.minWindow(S, T);
}