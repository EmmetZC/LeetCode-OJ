#include <iostream>
#include <string>

using namespace std;

#define COUNT 26
#define FIRST 'a'
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
		decltype(W.size()) minWindow = MAXINT, endIndex = 0;
		int cs[COUNT] = { 0 }, cw[COUNT] = { 0 };
		cnt_s = cs;
		cnt_w = cw;

		/*Initialize cnt_s*/
		for (auto ch : Sub){
			cnt_s[ch - FIRST]++;
		}

		/*Shift Window*/
		for (decltype(W.size()) i = 0; i < Ori.size(); ++i){
			char ch = Ori[i];
			AppendW(ch);
			if (CheckWindow() && (W.size() < minWindow)){
				minWindow = W.size();
				endIndex = i;
			}
		}

		/*Output Minimum Window*/
		if (endIndex == 0) {
			return "";
		}
		else {
			return Ori.substr(endIndex - minWindow + 1, minWindow);
		}
	}
};


void Solution::AppendW(char ch){
	Solution::W += ch;
	Solution::cnt_w[ch - FIRST]++;
	Solution::ClearRedundancy();
}

void Solution::PopW(){
	Solution::cnt_w[W[0] - FIRST]--;
	Solution::W.erase(Solution::W.begin());
	Solution::ClearRedundancy();
}

void Solution::ClearRedundancy(){
	char ch = Solution::W[0];
	if (Solution::cnt_w[ch - FIRST] > Solution::cnt_s[ch - FIRST]){
		Solution::PopW();
	}
}

bool Solution::CheckWindow(){
	for (int i = 0; i < COUNT; ++i){
		if (Solution::cnt_w[i] < Solution::cnt_s[i]){
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