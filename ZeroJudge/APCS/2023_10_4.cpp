#include <iostream>
#include <vector>
#include <algorithm>
//#define int long long
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
    int n = read(), k = read();
    vector<int> profits(n);
    for (int &profit : profits)
        profit = read();
    int currSum = 0, maxSum = 0;
    for (int &profit : profits) {
        
    }
    write(maxSum);
	return 0;
}