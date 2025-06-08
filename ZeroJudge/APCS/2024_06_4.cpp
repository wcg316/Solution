#include <iostream>
#include <vector>
#include <algorithm>
#define OFFSET 2001
#define idx first
#define sum second
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

struct GapAndSum {
	int parityGap = 0, sum = 0;
};

signed main() {
    int n = read(), k = read();
	vector<int> a(n + 1);
    vector<GapAndSum> prefix(n + 2), suffix(n + 2);
	vector<vector<pair<int, int>>> gapMap(4005);
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		prefix[i].sum = prefix[i - 1].sum + a[i];
		prefix[i].parityGap = prefix[i - 1].parityGap + (a[i] & 1 ? 1 : -1);
	}
	for (int i = n; i >= 1; i--) {
		suffix[i].sum = suffix[i + 1].sum + a[i];
		suffix[i].parityGap = suffix[i + 1].parityGap + (a[i] & 1 ? 1 : -1);
		gapMap[suffix[i].parityGap + OFFSET].push_back({i, suffix[i].sum});
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int neededGap = -prefix[i].parityGap;
		vector<pair<int, int>> &candidates = gapMap[neededGap + OFFSET];
		int l = 0, r = candidates.size();
		while (l < r) {
			int mid = (l + r) >> 1;
			if (candidates[mid].idx < i)
				l = mid + 1;
			else
				r = mid;
		}
	}
	write(ans);
	return 0;
}