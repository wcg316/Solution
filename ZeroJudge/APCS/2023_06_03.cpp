#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

int idx = 0;
string sequence;

struct loopData {
	int beginning, ending, dist;
};

int getNumberFrom(int idx) {
	return sequence[idx] * 10 + sequence[idx + 1] - '0' * 11;
}

loopData L() {
	int times = sequence[idx++] - '0';
	vector<int> numbers;
	numbers.reserve(10000);
	int distSum = 0;
	loopData result;
	while (idx < sequence.length()) {
		char ch = sequence[idx];
		if (ch == 'T') {
			idx++;
			int pos = getNumberFrom(idx);
			numbers.push_back(pos);
			idx += 2;
		} else if (ch == 'L') {
			idx++;
			loopData insideLoop = L();
			numbers.push_back(insideLoop.beginning);
			numbers.push_back(insideLoop.ending);
			result.dist += insideLoop.dist;
		} else if (ch == 'E') {
			idx++;
			result.beginning = numbers.front();
			result.ending = numbers.back();
			int i = 0;
			int middleMove = 0;
			while (i < numbers.size()) {
				middleMove += abs(numbers[i++] - numbers[i++]);
			}
			result.dist =
				middleMove * times +
				abs(numbers.back() - numbers.front()) * (times - 1);
			return result;
		}
		idx++;
	}
}

signed main() {
    sequence = read_line();
	write(L().dist);
	return 0;
}