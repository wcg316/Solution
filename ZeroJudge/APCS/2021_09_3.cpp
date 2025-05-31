#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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

vector<int> a, prefix;
map<int, int> idx;

signed main() {
	int n = read();
    a.resize(n + 1), prefix.resize(n + 1);
    a[0] = prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        prefix[i] = prefix[i - 1] + a[i];
        idx[a[i]] = i;
    }
	// map 是遞增的，所以最小的點是第一個
    auto it = idx.begin();
	int l = 1, r = n;
    while (l < r) {
        int m = it++ -> second;
		// 如果當前最小的點已經被排除了，就依序找第二小的
        while (m < l || m > r)
            m = it++ -> second;
        int leftSum = prefix[m - 1] - prefix[l - 1];
        int rightSum = prefix[r] - prefix[m];
        if (leftSum > rightSum)
            r = m - 1;
        else
            l = m + 1;
    }
    write(a[l]);
	return 0;
}