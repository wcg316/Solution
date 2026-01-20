#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
//#define getchar getchar_unlocked
//#define putchar putchar_unlocked
using namespace std;

inline int read() {
    char ch = getchar();
    while (ch == ' ' || ch == '\n') ch = getchar();
    if (ch == EOF) return EOF;
    while (ch == ' ' || ch == '\n') ch = getchar();
    int r = 0;
    while ('0' <= ch && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r;
}

void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

signed main() {
	int n = read(), k = read();
    vector<int> vec(n);
    for (int &v : vec)
        v = read();
    int ans = 0;
    unordered_map<int, int> um;
    for (int l = 0, r = 0; r < n; r++) {
        if (um.size() < 2) {
            if (!um.count(vec[r]))
                um[vec[r]] = 1;
            else
                um[vec[r]]++;
        }
    }
	return 0;
}