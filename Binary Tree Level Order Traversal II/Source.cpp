#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#include <algorithm>
struct QueueNode {
	TreeNode *node;
	int level;
	QueueNode(TreeNode *n, int i) : node(n), level(i) {}
};

class Solution {
private:
	QueueNode pop(vector<QueueNode> &list){
		QueueNode i = list.front();
		list.erase(list.begin());
		return i;
	}

	void push(vector<QueueNode> &list, QueueNode i){
		if (i.node != NULL){
			list.push_back(i);
		}
	}

public:
	vector<vector<int> > levelOrderBottom(TreeNode *root) {
		vector<vector<int> > result;
		vector<QueueNode> list;
		QueueNode qRoot = QueueNode(root, 0);
		push(list, qRoot);
		while (!list.empty()){
			QueueNode i = pop(list);
			while ((int)(result.size()) < (i.level+1)){
				vector<int> vTmp;
				result.push_back(vTmp);
			}
			result[i.level].push_back(i.node->val);
			push(list, QueueNode(i.node->left, i.level+1));
			push(list, QueueNode(i.node->right, i.level+1));
		}
		reverse(result.begin(), result.end());
	}
};

void main(){

}