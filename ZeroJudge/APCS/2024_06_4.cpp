#include <iostream>
#include <vector>
#include <utility>
// 對所有奇偶差添加偏移，避免負值索引的錯誤
#define OFFSET 2001
// 這三個 define 只是為了方便閱讀而已
#define parityGap first
#define idx first
#define sum second
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

// 底下東西略多，挪到外面放在 heap 以防 stack 爆炸
vector<int> a;
// 存前綴和後綴的總合及奇偶差
vector<pair<int, int>> prefix, suffix;
// 存特定奇偶差下的所有後綴終點及後綴和
vector<vector<pair<int, int>>> gapMap;

signed main() {
    int n = read(), k = read();
	a.resize(n + 1);
	prefix.resize(n + 2), suffix.resize(n + 2);
	gapMap.resize(4005);
	// 初始化歸零
	prefix[0].sum = 0, suffix[n + 1].sum = 0;
	// 在奇偶差為零的狀況下，還有後方完全不選任何一個數字的可能（記得添加偏移）
	gapMap[0 + OFFSET].push_back({n + 1, 0});
	// 製作前綴和
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		prefix[i].sum = prefix[i - 1].sum + a[i];
		prefix[i].parityGap = prefix[i - 1].parityGap + (a[i] & 1 ? 1 : -1);
	}
	// 製作後綴和
	for (int i = n; i >= 1; i--) {
		suffix[i].sum = suffix[i + 1].sum + a[i];
		suffix[i].parityGap = suffix[i + 1].parityGap + (a[i] & 1 ? 1 : -1);
		// 紀錄有哪些後綴區間的後綴奇偶差是這個數字
		// 方便待會直接查表（記得添加偏移）
		gapMap[suffix[i].parityGap + OFFSET].push_back({i, suffix[i].sum});
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		// 取得為了平衡奇偶所需的奇偶差
		int neededGap = -prefix[i].parityGap;
		// 取得所有具有該奇偶差的後綴區間（記得添加偏移）
		vector<pair<int, int>> &candidates = gapMap[neededGap + OFFSET];
		// 二分搜尋找第一個不與
		// 當前前綴區間重疊的後綴區間
		int l = 0, r = candidates.size();
		while (l < r) {
			int mid = (l + r) >> 1;
			if (candidates[mid].idx > i)
				l = mid + 1;
			else
				r = mid;
		}
		// 這裡出來的 l 是第一個不合法，會與當前前綴重疊的後綴區間
		// 令上界 r 等於 l，l 重設為 0
		// 所有 [l, r) 內的元素皆不會與當前前綴重疊
		r = l, l = 0;
		// 二分搜尋找總和不超過 k 的最大值
		while (l < r) {
			int mid = (l + r) >> 1;
			if (candidates[mid].sum + prefix[i].sum <= k)
				l = mid + 1;
			else
				r = mid;
		}
		// 若有找到結果且結果合法就嘗試更新答案
		if (l > 0 && candidates[l - 1].idx > i && candidates[l - 1].sum + prefix[i].sum <= k)
			ans = max(ans, candidates[l - 1].sum + prefix[i].sum);
	}
	write(ans);
	return 0;
}