#include <iostream>

using namespace std;

class MinStack {
private:
	int s[100000];
	int topIndex;
	int minIndex;
	int min[100000];
public:
	MinStack() : topIndex(0), minIndex(0)
	{
		min[minIndex] = (unsigned int)(-1) >> 1;
		minIndex++;
	}

	void push(int x) {
		s[topIndex] = x;
		topIndex++;
		if (getMin() >= x){
			min[minIndex] = x;
			minIndex++;
		}
	}

	void pop() {
		int a = top();
		topIndex--;
		if (getMin() == a){
			minIndex--;
		}
	}

	int top() {
		return s[topIndex - 1];
	}

	int getMin() {
		return min[minIndex - 1];
	}
};

int main()
{
	MinStack ms = MinStack();
	ms.push(1);
	ms.push(3);
	cout << ms.top();
	cout << ms.getMin();
	ms.push(-3);
	cout << ms.getMin();
	ms.pop();
	cout << ms.getMin();
}