#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
//////////////////////////////////// 記得開 long long ////////////////////////////////////
#define int long long
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
    // 注意以下的 int 都是 long long
	int n = read();
    // a[] 紀錄數字，排序後用來確認數字大小順序
    // prefix[] 記錄前綴和，用來快速計算區區間和
    vector<int> a(n + 1), prefix(n + 1);
    // idx 記錄每個數字的位置，用來查詢數字原本的位置
    // key 是數字本身，value 是數字位置
    unordered_map<int, int> idx;
    // 初始化
    a[0] = prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        prefix[i] = prefix[i - 1] + a[i];
        // a[i] 的位置在 i
        idx[a[i]] = i;
    }
    // 排序，方便後續快速得知最小數字的位置
    sort(a.begin(), a.end());
    int i = 1;
	int l = 1, r = n;
    while (l < r) {
        int m = idx[a[i++]];
		// 如果當前最小的點已經被排除在區間外了，就依序找第二小的
        while (m < l || m > r)
            m = idx[a[i++]];
        int leftSum = prefix[m - 1] - prefix[l - 1];
        int rightSum = prefix[r] - prefix[m];
        if (leftSum > rightSum)
            r = m - 1;
        else
            l = m + 1;
    }
    write(prefix[l] - prefix[l - 1]);
	return 0;
}