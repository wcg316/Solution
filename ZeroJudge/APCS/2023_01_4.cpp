#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
// #define int long long
// #define getchar getchar_unlocked
// #define putchar putchar_unlocked
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

// 自訂結構存放每個活動的開始及結束時間
struct duration {
	int beginning, ending;
};

// 針對活動時程的自訂排序，嚴格遞增，
// 先依照結束時間排序，再依照開始時間排序
bool cmp (duration &a, duration &b) {
	if (a.ending != b.ending)
		return a.ending < b.ending;
	return a.beginning < b.beginning;
}

signed main() {
	int n = read(), k = read();
	vector<duration> activities(n);
	for (auto &activity : activities)
		activity.beginning = read();
	for (auto &activity : activities)
		activity.ending = read();
	// 為了使用貪婪演算法，依照活動結束時間做排序
	sort(activities.begin(), activities.end(), cmp);
	// 紀錄每臺機器的最後結束時間，也就是何時開始有空
	multiset<int> machines;
	// 加入 k 臺機器，初始化為 -1，表示其從時間 0 開始就有空
	for (int i = 0; i < k; i++)
		machines.insert(-1);
	int ans = 0;
	for (auto &activity : activities) {
		// 二分搜找到第一臺有空的機器
		auto it = machines.upper_bound(activity.beginning - 1);
		// it == .begin() 時，
		// 代表所有機器結束工作的時間皆大於該活動的起始時間，無法加入排程
		if (it != machines.begin()) {
			// 如果有找到，就嘗試更新答案
			it--;
			machines.erase(it);
			machines.insert(activity.ending);
			ans++;
		}
	}
	write(ans);
	return 0;
}