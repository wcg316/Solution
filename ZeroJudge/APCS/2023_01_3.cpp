#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#define int long long
//#define getchar getchar_unlocked  
//#define putchar putchar_unlocked
using namespace std;

inline string read_line() {
    string r = "";
    char ch = getchar();
    while (ch != '\n' && ch != EOF) r += ch, ch = getchar();
    return r;
}

void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

string calculation;

vector<string> split(string &orig, char target) {
	vector<string> results;
	string str = "";
	for (int i = 0; i < orig.size(); i++) {
		if (orig[i] == target) {
			results.push_back(str);
			str = "";
		} else {
			str += orig[i];
		}
	}
	if (str != "")
		results.push_back(str);
	return results;
}

int calc(string &calculation) {
	vector<string> addPart = split(calculation, '*');
	int product = 1;
	for (auto &part : addPart) {
		vector<string> numbers = split(part, '+');
		int sum = 0;
		for (auto &number : numbers)
			sum += stoll(number);
		product *= sum;
	}
	return product;
}

int f(string &content) {
	vector<string> calculations = split(content, ',');
	vector<int> numbers;
	for (auto &calculation : calculations)
		numbers.push_back(calc(calculation));
	return
		*max_element(numbers.begin(), numbers.end()) - *min_element(numbers.begin(), numbers.end());
}

signed main() {
	calculation = read_line();
	stack<int> left;
	int i = 0;
	while (i < calculation.length()) {
		if (calculation[i] == 'f')
			left.push(++i);
		if (calculation[i] == ')') {
			int leftPos = left.top();
			left.pop();
			int len = i - leftPos - 1;
			string content = calculation.substr(leftPos + 1, len);
			calculation =
				calculation.substr(0, leftPos - 1) + to_string(f(content)) + calculation.substr(i + 1);
			i = leftPos - 1;
		}
		i++;
	}
	write(calc(calculation));
	return 0;
}