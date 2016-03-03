#include <string>
#include <cctype>
#include <iostream>

using namespace std;
/************************************************************************/
// Validate if a given string is numeric
// "0" => true
// " 0.1 " = > true
// "abc" = > false
// "1 a" = > false
// "2e10" = > true
/************************************************************************/

class Solution {
public:
	bool isNumber(string s) {
		unsigned lo = 0, hi = s.size();
		// Trim
		while (lo < hi && isspace(s[lo]))
			++lo;
		while (lo < hi && isspace(s[hi - 1]))
			--hi;

		// First sign
		if (s[lo] == '-' || s[lo] == '+')
			++lo;

		unsigned digits = 0;
		while (lo < hi && isdigit(s[lo])) {
			++digits;
			++lo;
		}
		if (lo < hi && s[lo] == '.') ++lo;
		while (lo < hi && isdigit(s[lo])) {
			++digits;
			++lo;
		}
		if (digits == 0) return false;
		if (s[lo] == 'e') {
			digits = 0;
			++lo;
			// Second sign
			if (s[lo] == '-' || s[lo] == '+')
				++lo;
			while (lo < hi && isdigit(s[lo])) {
				++digits;
				++lo;
			}
		}
		if (digits == 0) return false;
		return lo == hi;
	}
};

int main() {
}