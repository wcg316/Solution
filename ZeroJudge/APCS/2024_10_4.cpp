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
    int depart, end;
};

bool cmp(bus &a, bus &b) {
    if (a.end == b.end)
        return a.depart < b.depart;
    // 依照終點排序
    return a.end < b.end;
}

unordered_map<int, int> waysToHere;
vector<int> prefix;
vector<bus> routes;

signed main() {
    int n = read(), m = read(), p = read();
    // 為了方便對齊，兩個的長度都讓它是 n + 1
    prefix.resize(n + 1);
    routes.resize(n + 1);
    prefix[0] = 0;
    routes[0] = {-1, -1};
    for (int i = 1; i <= n; i++)
        routes[i].depart = read();
    for (int i = 1; i <= n; i++)
        routes[i].end = read();
    // 依照終點排序
    sort(routes.begin(), routes.end(), cmp);
    for (int i = 1; i <= n; i++) {
        // 第一次二分搜
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            // 如果符合條件就往前半縮，才會找到第一個
            if (routes[mid].end >= routes[i].depart)
                r = mid;
            else
                l = mid + 1;
        }
        // 取得第一個可以接上這條路線的車的序號
        int firstCanTake = r;
        // 第二次二分搜
        l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            // 如果符合條件就往後半縮，才會找到最後一個
            if (routes[mid].end < routes[i].end)
                l = mid + 1;
            else
                r = mid;
        }
        // 取得最後一個可以接上這條路線的車的序號
        // 因為 l 回傳的是第一個不符合條件的序號
        // 記得 l - 1 才會是最後一個可以接上這條路線的車
        int lastCanTake = l - 1;
        int waysOfThisRoute = 0;
        if (firstCanTake <= lastCanTake)
            waysOfThisRoute = (prefix[lastCanTake] - prefix[firstCanTake - 1] + p) % p;
            // 要加上一個 p 是為了避免可能在
            // firstCanTake - 1 到 lastCanTake 途中有被 p 整除過
            // 導致數字變小進而相減時出現負數
        if (routes[i].depart == 0)
            waysOfThisRoute++;
        if (waysToHere.find(routes[i].end) == waysToHere.end())
            waysToHere[routes[i].end] = 0;
        // 更新這個終點的抵達方法
        waysToHere[routes[i].end] = (waysOfThisRoute + waysToHere[routes[i].end]) % p;
        // 更新前綴和
        prefix[i] = (waysOfThisRoute + prefix[i - 1]) % p;
    }
    write(waysToHere[m]);
	return 0;
}