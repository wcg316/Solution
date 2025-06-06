#include <iostream>
#include <vector>
#include <algorithm>
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
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int pre[150009], curr[150009];

signed main() {
    int n = read(), k = read();
    k++;
    memset(pre, 0, sizeof(pre));
    vector<int> profits(n + 1);
    profits[0] = 0;
    for (int i = 1; i <= n; i++)
        profits[i] = read();
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            curr[j] = max(curr[j - 1] + profits[j], pre[j - 1]);
            ans = max(ans, curr[j]);
        }
        swap(pre, curr);
    }
    write(ans);
	return 0;
}