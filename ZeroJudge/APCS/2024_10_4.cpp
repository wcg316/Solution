#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
//#define int long long
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
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

struct bus {
    int s, e, w = 0;
};

bool cmp(bus &a, bus &b) {
    if (a.e == b.e)
        return a.s < b.s;
    return a.e < b.e;
}

signed main() {
	int n = read(), m = read(), p = read();
    vector<bus> routes(n);
    for (auto &route : routes) {
        route.s = read();
        if (route.s == 0)
            route.w = 1;
    }
    for (auto &route : routes)
        route.e = read();
    sort(routes.begin(), routes.end(), cmp);
    for (auto &route : routes) {
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (route.s <= routes[mid].e && routes[mid].e < route.e)
                l = mid;
            else
                r = mid - 1;
        }
        bus lastCanTake = routes[l];
        l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (route.s <= routes[mid].e && routes[mid].e < route.e)
                r = mid;
            else
                l = mid + 1;
        }
        bus firstCanTake = routes[r];
        route.w = (lastCanTake.w + firstCanTake.w) % p;
    }
    int ans = 0;
    for (int i = n - 1; routes[i].e >= m; i--) {
        if (routes[i].e == m)
            ans = (ans + routes[i].w) % p;
    }
    write(ans);
	return 0;
}