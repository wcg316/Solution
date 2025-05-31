#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
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
    int s, e;
};

bool cmp(bus &a, bus &b) {
    if (a.e == b.e)
        return a.s < b.s;
    return a.e < b.e;
}

unordered_map<int, int> waysToHere;
vector<int> prefix;
vector<bus> routes;

signed main() {
	int n = read(), m = read(), p = read();
    prefix.resize(n + 1);
    routes.resize(n + 1);
    prefix[0] = 0;
    routes[0] = {-1, -1};
    for (int i = 1; i <= n; i++)
        routes[i].s = read();
    for (int i = 1; i <= n; i++)
        routes[i].e = read();
    sort(routes.begin(), routes.end(), cmp);
    for (int i = 1; i <= n; i++) {
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (routes[mid].e >= routes[i].s)
                r = mid;
            else
                l = mid + 1;
        }
        int firstCanTake = r;
        l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (routes[mid].e < routes[i].e)
                l = mid + 1;
            else
                r = mid;
        }
        int lastCanTake = l - 1;
        int waysOfThisRoute = 0;
        if (firstCanTake <= lastCanTake)
        	waysOfThisRoute = (prefix[lastCanTake] - prefix[firstCanTake - 1] + p) % p;
        if (routes[i].s == 0)
            waysOfThisRoute++;
        if (waysToHere.find(routes[i].e) == waysToHere.end())
            waysToHere[routes[i].e] = 0;
        waysToHere[routes[i].e] = (waysOfThisRoute + waysToHere[routes[i].e]) % p;
        prefix[i] = (waysOfThisRoute + prefix[i - 1]) % p;
    }
    write(waysToHere[m]);
	return 0;
}