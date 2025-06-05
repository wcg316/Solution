#include <iostream>
#include <algorithm>
#include <map>
#define int long long
//#define getchar getchar_unlocked  
//#define putchar putchar_unlocked
using namespace std;

inline int read() {
    char ch = getchar();
    while (ch == ' ' || ch == '\n') ch = getchar();
    if (ch == EOF) return EOF;
    int s = 1;
    while (ch < '0' || '9' < ch) {
        if (ch == '-') s = -1;
        ch = getchar();
    }
    int r = 0;
    while ('0' <= ch && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r * s;
}

void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

signed main() {
	int m = read(), n = read();
	map<int, int> CPs;
	for (int i = 0; i < n; i++) {
		char ch = getchar();
		int curr = 0;
		while (ch != EOF && ch != '\n') {
			int flipPos = ch >= 'A' && ch <= 'Z' ?
				ch - 'A' : ch - 'a' + 26;
			curr |= (1LL << flipPos);
			ch = getchar();
		}
		if (CPs.find(curr) == CPs.end())
			CPs[curr] = 1;
		else
			CPs[curr]++;
	}
	int ans = 0;
	int all = 0;
	for (int i = 0; i < m; i++) {
		all <<= 1LL;
		all++;
	}
	for (auto &CP : CPs) {
		int target = all ^ CP.first;
		auto it = CPs.find(target);
		if (it != CPs.end())
			ans += CP.second * it -> second;
	}
	write(ans >> 1);
	return 0;
}