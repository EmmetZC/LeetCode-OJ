#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INTMAX ((unsigned int)(-1) >> 1)
#define INTMIN (INTMAX + 1)

class Solution {
private:
	int findInRange(const vector<int> &num, int start, int end){
		if (end == start){
			return start;
		}else if (end - start == 1){
			return (num[start] > num[end] ? start : end);
		}else{
			int mid = (start + end) / 2;
			if (num[mid - 1] > num[mid]){
				return findInRange(num, start, mid - 1);
			}else if (num[mid] < num[mid + 1]){
				return findInRange(num, mid + 1, end);
			}else{
				return mid;
			}
		}
	}
public:
	int findPeakElement(const vector<int> &num) {
		vector<int> N = num;
		N.push_back(INTMIN);
		N.insert(N.begin(), INTMIN);
		int peekIndex = findInRange(N, 1, (int)(num.size()) - 1);
		return N[peekIndex];
	}
};

int main()
{
	Solution s;
	int tmp;
	vector<int> num;
	while (cin >> tmp)
	{
		num.push_back(tmp);
	}
	cout << s.findPeakElement(num);
}