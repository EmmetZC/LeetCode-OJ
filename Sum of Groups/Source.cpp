#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
	int sumOfRange(const unsigned start, const unsigned end, const vector<int> nums) {
		int sum = 0;;
		for (auto i = start; i <= end; ++i) {
			sum += nums[i];
		}
		return sum;
	}

public:
	int maxSum(unsigned M, unsigned K, vector<int> &nums) {
		auto N = nums.size();
		if (N < M*K) {
			return 0;
		} else if (N == M*K) {
			return sumOfRange(0, N - 1, nums);
		}

		vector<vector<int>> sums(M + 1, vector<int>(N + 1, 0));

		for (auto m = 1u; m <= M; ++m) {
			for (auto n = K; n <= N; ++n) {
				sums[m][n] = max(sums[m - 1][n - K] + sumOfRange(n - K, n - 1, nums), sums[m][n - 1]);
			}
		}

		return sums[M][N];
	}
};

void main() {
	Solution s;
	const unsigned M = 5;
	const unsigned K = 4;
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	cout << s.maxSum(M, K, nums) << endl;
}