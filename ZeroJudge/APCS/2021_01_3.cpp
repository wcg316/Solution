#include <iostream>
#include <vector>
#include <set>
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
    //while (ch == ' ' || ch == '\n') ch = getchar();
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
    int n = read(), l = read();
    vector<int> cutPoints(n);
	set<int> s;
	// 先加入最初的端點，也就是木棍的頭尾
    s.insert(0), s.insert(l);
	// 讀取測資
    while (n--) {
        int cutPoint = read(), idx = read() - 1;
        cutPoints[idx] = cutPoint;
    }
    int ans = 0;
    for (auto &c : cutPoints) {
        s.insert(c);
        auto it = s.find(c);
		// 利用 next 和 prev 直接找到前後端點，並求得長度
        ans += *next(it) - *prev(it);
    }
    write(ans);
    return 0;
}