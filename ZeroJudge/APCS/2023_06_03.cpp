#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
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

string sequence;

struct loop {
	bool finished;
	int times, beginning, ending, dist;
	vector<int> path;
	loop(int t) {
		finished = false;
		times = t;
		path.reserve(10000);
	}
};

int getNumberFrom(int idx) {
	return sequence[idx] * 10 + sequence[idx + 1] - '0' * 11;
}

signed main() {
    sequence = read_line();
	int idx = 0;
	stack<loop> s;
	loop *start = new loop(1);
	s.push(*start);
	while (!s.empty()) {
		loop &curr = s.top();
		if (!curr.finished) {
			while (idx < sequence.length()) {
				char ch = sequence[idx];
				if (ch == 'T') {
					idx++;
					int pos = getNumberFrom(idx);
					curr.path.push_back(pos);
					idx += 2;
				} else if (ch == 'L') {
					idx++;
					loop *insideLoop = new loop(sequence[idx++] - '0');
					s.push(*insideLoop);
					curr = s.top();
				} else if (ch == 'E') {
					idx++;
					curr.finished = true;
					break;
				}
			}
			curr.beginning = curr.path.front();
			curr.ending = curr.path.back();
			int middleMove = 0;
			for (int i = 0; i < curr.path.size() - 1; i++)
				middleMove += abs(curr.path[i] - curr.path[i + 1]);
			curr.dist =
				(middleMove + curr.dist) * curr.times +
				abs(curr.path.back() - curr.path.front()) * (curr.times - 1);
			if (s.size() == 1) {
				write(curr.dist);
				return 0;
			} else if (curr.finished) {
				int beginning = curr.beginning;
				int ending = curr.ending;
				int dist = curr.dist;
				s.pop();
				curr = s.top();
				curr.path.push_back(beginning);
				curr.path.push_back(ending);
				curr.dist += 
					dist - abs(beginning - ending);
			}
		}
	}
	return 0;
}