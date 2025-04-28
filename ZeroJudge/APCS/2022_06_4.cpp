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

signed main() {
	int n = read(), m = read();
	vector<int> a, b;
	// 為了方便起見，在此刻意讓 n 較大， m 較小
	// a[] 固定是較長的陣列
	// 而 b[] 是較短的陣列
	if (n < m) {
		a.resize(m);
		b.resize(n);
		for (int &_b : b)
			_b = read();
		for (int &_a : a)
			_a = read();
		// 記得交換，讓 n 是比較大的
		swap(n, m);
	} else {
		a.resize(n);
		b.resize(m);
		for (int &_a : a)
			_a = read();
		for (int &_b : b)
			_b = read();
	}
	// 開始尋找最大區間內積
	int maxSum = INT_MIN;
	// 記得外層要從 -m + 1 開始找，而不是 0
	// 不然會漏掉 b[] 尾部 + a[] 頭部的配對
	for (int i = -m + 1; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m && j + i < n; j++) {
			// 避免 i 太小導致超出陣列範圍
			if (j + i < 0)
				continue;
			sum += a[j + i] * b[j];
			maxSum = max(maxSum, sum);
			sum = max(sum, 0);
		}
	}
	// 反轉之後再找一次
	reverse(a.begin(), a.end());
	for (int i = -m + 1; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m && j + i < n; j++) {
			if (j + i < 0)
				continue;
			sum += a[j + i] * b[j];
			maxSum = max(maxSum, sum);
			sum = max(sum, 0);
		}
	}
	// 輸出答案
	write(maxSum);
	return 0;
}