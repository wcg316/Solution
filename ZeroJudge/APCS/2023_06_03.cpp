#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
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

int idx = 0;
string sequence;

struct loop {
	// 用來回傳 loop 前的起點、
	// 經過 loop 後的終點、
	// 以及 loop 經過的總距離
	int beginning, ending, dist;
};

int getNumberFrom(int idx) {
	return sequence[idx] * 10 + sequence[idx + 1] - '0' * 11;
}

loop L(int times) {
	// 記錄所有經過的位置
	vector<int> path;
	// 用於回傳資料
	loop result;
	result.dist = 0;
	while (idx < sequence.length()) {
		char ch = sequence[idx];
		if (ch == 'T') {
			idx++;
			int pos = getNumberFrom(idx);
			path.push_back(pos);
			idx += 2;
		} else if (ch == 'L') {
			idx++;
			// 利用遞迴，先進行內部的 loop
			loop insideLoop = L(sequence[idx++] - '0');
			path.push_back(insideLoop.beginning);
			path.push_back(insideLoop.ending);
			// 再減掉起點終點的距離，
			// 是為了抵銷在後面計算外部 loop 的距離時多算一次
			result.dist += 
				insideLoop.dist - abs(insideLoop.beginning - insideLoop.ending);
		} else if (ch == 'E') {
			idx++;
			break;
		}
	}
	// 記錄 loop 後的起點終點
	result.beginning = path.front();
	result.ending = path.back();
	int middleMove = 0;
	for (int i = 0; i < path.size() - 1; i++)
		middleMove += abs(path[i] - path[i + 1]);
	result.dist =
		(middleMove + result.dist) * times +
		// 記得除了途中經過的位置，
		// 還要把終點接回起點的移動算進去
		abs(path.back() - path.front()) * (times - 1);
	return result;
}

signed main() {
    sequence = read_line();
	// 直接把整串測資當成一個 loop 1次的序列
	// 就不用在 main() 另外寫判斷了
	write(L(1).dist);
	return 0;
}