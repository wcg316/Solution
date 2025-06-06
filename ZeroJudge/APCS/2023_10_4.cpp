#include <iostream>
#include <vector>
#include <algorithm>
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
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int dp[22][150009];

signed main() {
    int n = read(), k = read();
    k++;
    vector<int> profits(n + 1);
    profits[0] = 0;
    for (int i = 1; i <= n; i++)
        profits[i] = read();
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i][j - 1] + profits[j], dp[i - 1][j - 1]);
            ans = max(ans, dp[i][j]);
        }
    }
    write(ans);
	return 0;
}