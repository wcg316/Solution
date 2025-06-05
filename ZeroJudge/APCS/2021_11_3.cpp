#include <iostream>
#include <vector>
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
	int n = read(), m = read();
	vector<int> workloads(n + 2, 0);
	while (m--) {
		int l = read(), r = read(), w = read();
		workloads[l] += w;
		workloads[r + 1] -= w;
	}
	for (int i = 1; i <= n; i++)
		workloads[i] += workloads[i - 1];
	sort(workloads.begin(), workloads.end(), [](int &a, int &b){ return a > b; });
	vector<int> timeTakes(n);
	for (int &t : timeTakes)
		t = read();
	sort(timeTakes.begin(), timeTakes.end());
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (!workloads[i])
			break;
		ans += workloads[i] * timeTakes[i];
	}
	write(ans);
	return 0;
}