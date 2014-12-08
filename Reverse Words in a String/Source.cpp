#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
	void split(string &s, char sep, vector<string> &v) {
		while (s != "") {
			int pos = s.find_first_of(sep, 0);
			if (pos != string::npos)
			{
				string sub = s.substr(0, pos);
				v.push_back(sub);
				s = s.substr(pos + 1, (int)s.size() - (pos - 1));
			}
			else
			{
				v.push_back(s);
				break;
			}
		}
	}

	void join(string &s, char sep, vector<string> &v) {
		auto i = v.size();
		while (i > 0){
			i--;
			if (v[i] == "") continue;
			s = v[i];
			break;
		}
		while (i > 0){
			i--;
			if (v[i] == "") continue;
			s += sep;
			s += v[i];
		}
	}
public:
	void reverseWords(string &s) {
		vector<string> v;
		split(s, ' ', v);
		join(s, ' ', v);
	}
};

int main(){
	Solution s;
	string S = "   a   b ";
	s.reverseWords(S);
	cout << S;
}