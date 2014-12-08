#include <iostream>
#include <vector>
#include <string>

using namespace std;



class Solution {
struct Count{
	int val;
	int count;
	Count(int v, int c) : val(v), count(c){}
};
private:
	Count getLongestSame(string last)
	{
		int val = last[0] - '0';
		int count = 0;
		for (; count < (int)last.size()&&(last[count]==last[0]); ++count){
		}
		return Count(val, count);
	}

	string getFromLast(string last)
	{
		string result="";
		while (last.size()>0){
			Count C = getLongestSame(last);
			result += to_string(C.count);
			result += to_string(C.val);
			last = last.substr(C.count, (int)(last.size()) - C.count);
		}
		return result;
	}

public:
	string countAndSay(int n) {
		if (n == 1)
		{
			return "1";
		}
		else
		{
			return getFromLast(countAndSay(n - 1));
		}
	}
};

void main()
{
	int n = 0;
	cin >> n;
	Solution s;
	for (int i = 1; i <= n; ++i){
		cout << s.countAndSay(i) << endl;
	}
}