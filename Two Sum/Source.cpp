#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
	int beSearch(vector<int> &sortedNumbers, int start, int end, int target){
		if (end - start <= 1 && target!=sortedNumbers[start]&&target!=sortedNumbers[end]){
			return -1;
		}
		int mid = (start + end) / 2;
		if (sortedNumbers[mid] == target){
			return mid;
		}
		else if (sortedNumbers[mid] < target){
			return beSearch(sortedNumbers, mid + 1, end, target);
		}
		else{
			return beSearch(sortedNumbers, start, mid - 1, target);
		}
		return -1;
	}

	int getNum(vector<int> &sortedNumbers, int target){
		int a = -1, b_index;
		for (unsigned int i = 0; i<sortedNumbers.size()-1 && sortedNumbers[i] <= target / 2; ++i){
			a = sortedNumbers[i];
			if (b_index = beSearch(sortedNumbers, i + 1, sortedNumbers.size() - 1, target - a) != -1){
				break;
			}
		}
		return a;
	}
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> sortedNumbers = numbers, twoSum;
		sort(sortedNumbers.begin(), sortedNumbers.end());
		int first = getNum(sortedNumbers, target);
		for (unsigned int i = 0; i<numbers.size(); ++i){
			if (numbers[i] == first || numbers[i] == target-first){
				twoSum.push_back(i + 1);
				int second = target - numbers[i];
				for (auto j = i + 1; j<numbers.size(); ++j){
					if (numbers[j] == second){
						twoSum.push_back(j + 1);
						return twoSum;
					}
				}
			}
		}
		return twoSum;
	}
};

int main(){
	Solution s;
	vector<int> numbers = { 3, 2, 4 };
	int target = 6;
	vector<int> indices = s.twoSum(numbers, target);
	for (auto i : indices){
		cout << i << endl;
	}
}