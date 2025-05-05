#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
//#define getchar getchar_unlocked  
//#define putchar putchar_unlocked
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// 下面的 read() 和 write() 是我自訂的讀寫函式 ////////////////////////
/////////////////////////////// 功能就只是讀取測資和輸出答案 ////////////////////////////////
////////////////////////////////// 礙眼的話可以摺疊起來 ////////////////////////////////////

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

struct building {
	int money, days;
};

bool cmp(building a, building b) {
	return a.days * b.money < b.days * a.money;
}

signed main() {
	int n = read();
	vector<building> buildings(n);
	int totalMoney = 0;
	for (auto &b : buildings) {
		b = {read(), read()};
		totalMoney += b.money;
	}
	sort(buildings.begin(), buildings.end(), cmp);
	int cost = 0;
	for (const auto &b : buildings) {
		cost += totalMoney * b.days;
		totalMoney -= b.money;
	}
	write(cost);
	return 0;
}