#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
//#define int long long
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
	int n = read();
    vector<pair<int, int>> coords(n);
	for (auto &coord :coords) coord = {read(), read()};
    sort(coords.begin(), coords.end());
    vector<int> dp;
    for (auto &coord : coords) {
        if (dp.empty() || coord.second >= dp.back()) dp.push_back(coord.second);
        else *upper_bound(dp.begin(), dp.end(), coord.second) = coord.second;
    }
    write(dp.size());
	return 0;