#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Solution {
private:
	deque<int> window;
	deque<int> indexInWindow;

	void pop_front() {
		window.pop_front();
		indexInWindow.pop_front();
	}
	int pop_back() {
		int result = window[window.size() - 1];
		window.pop_back();
		indexInWindow.pop_back();
		return result;
	}
	void push_back(int value, int index) {
		while(!window.empty()&&window.back() <= value) {
			pop_back();
		}
		window.push_back(value);
		indexInWindow.push_back(index);
	}
	void slideRight(unsigned front_index) {
		if (front_index == indexInWindow.front()) {
			pop_front();
		}
	}

public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		if (nums.empty() || k == 1) {
			return nums;
		} else{
			vector<int> result;
			for (int i = 0; i < k; ++i) {
				push_back(nums[i], i);
			}
			for (unsigned front_index = 0; front_index < nums.size() - k + 1; ++front_index) {
				result.push_back(window.front());
				if (front_index < nums.size() - k) {
					if (front_index == indexInWindow.front()) {
						pop_front();
					}
					push_back(nums[front_index + k], front_index + k);
				}
			}
			return result;
		}
	}
};

void main() {
	vector<int> input = { 1, 3, -1, -3, 5, 3, 6, 7 };
	Solution s;
	vector<int> result = s.maxSlidingWindow(input, 3);
	for (auto i : result) {
		cout << i << " ";
	}
	cout << endl;
	return;
}