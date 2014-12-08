#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	void getCoordinate(int id, int (&coor)[2], vector<vector<int> > &matrix){
		int m = (int)matrix.size();
		int n = (int)matrix[0].size();
		coor[0] = id / n;
		coor[1] = id - coor[0] * n;
	}

	bool searchInRange(int start, int end, vector<vector<int> > &matrix, int target){
		int coor[2] = { 0 };
		getCoordinate((start + end) / 2, coor, matrix);
		int mid = matrix[coor[0]][coor[1]];
		if (target == mid){
			return true;
		}else if (start >= end) {
			return false;
		}else if (target > mid){
			return searchInRange((start + end) / 2 + 1, end, matrix, target);
		}else{
			return searchInRange(start, (start + end) / 2 - 1, matrix, target);
		}
	}
public:
	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		int m = (int)(matrix.size());
		int n = (int)(matrix[0].size());
		if (matrix[0][0] > target || target > matrix[m - 1][n - 1]) return false;
		return searchInRange(0, m*n - 1, matrix, target);
	}
};


int main(){
	vector<vector<int> > matrix = { { 1, 1 }, { 3, 3 } };

	Solution s;
	cout << (s.searchMatrix(matrix, 2)?"T":"F");
	return 0;
}