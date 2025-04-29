#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
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
    for (auto &coord :coords)
        coord = {read(), read()};
    // 依照 x 座標做排序
    sort(coords.begin(), coords.end());
    // 開始尋找 LIS 的長度
    vector<int> dp;
    for (auto &coord : coords) {
        // 由於題目要求的是 「不小於」
        // 所以記得改用 >=
        // 二分搜也改用 upper_bound
        // 確保不會跳過選取 y 相等的座標
        if (dp.empty() || coord.second >= dp.back())
        	dp.push_back(coord.second);
        else
        	*upper_bound(dp.begin(), dp.end(), coord.second) = coord.second;
    }
    write(dp.size());
	return 0;
}