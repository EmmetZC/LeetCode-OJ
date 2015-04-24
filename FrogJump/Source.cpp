#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class FrogJump {
private:
	bool ValidInput(const vector<bool> stumps, const int min, const int max) {
		if (stumps.empty() || min <= 0 || max < min) {
			return false;
		}
		return true;
	}
	unsigned ClearNegative(int i) {
		if (i <= 0) return 0;
		return i;
	}
public:
	int Solution(const vector<bool> stumps, int min, int max) {
		if (!ValidInput(stumps, min, max)) {
			return -1;
		}
		vector<int> minRocks;
		minRocks.assign(stumps.begin(), stumps.end());
		minRocks.insert(minRocks.begin(), 0);

		for (unsigned i = min; i < minRocks.size(); ++i) {
			int minLast = 2147483647;
			for (unsigned j = ClearNegative(i - max); (int)i - min >= 0 && (int)j <= (int)i - min; ++j) {
				if (minRocks[j] < minLast) {
					minLast = minRocks[j];
				}
			}
			minRocks[i] += minLast;
		}
		return *minRocks.crbegin();
	}
};

void main() {
	FrogJump fJ;
	vector<bool> stumps{ true, false, false, true, true };
	cout << fJ.Solution(stumps, 1, 2);
}