#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
//#define int long long
//#define getchar getchar_unlocked
//#define putchar putchar_unlocked
using namespace std;

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
	if (n < m) {
		a.resize(m);
		b.resize(n);
		for (int &_b : b)
			_b = read();
		for (int &_a : a)
			_a = read();
		swap(n, m);
	} else {
		a.resize(n);
		b.resize(m);
		for (int &_a : a)
			_a = read();
		for (int &_b : b)
			_b = read();
	}
	int maxSum = INT_MIN;
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
	write(maxSum);
	return 0;
}