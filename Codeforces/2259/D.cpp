#include <iostream>
#include <vector>
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

inline string read_line() {
    string r = "";
    char ch = getchar();
    while (ch != '\n' && ch != EOF) r += ch, ch = getchar();
    return r;
}

void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

inline void write_line(string str) {
    for (int i = 0; i < str.length(); i++) putchar(str[i]);
}

signed main() {
    int t = read();
	while (t--) {
		int n = read();
		vector<int> a(n);
		int zeroCount = 0;
		for (auto& num : a) {
			num = read();
			if (!num) {
				zeroCount++;
			}
		}
		if (zeroCount == 1) {
			write_line("NO\n");
		} else {
			write_line("YES\n");
			for (auto num : a) {
				if (!num) {
					if (zeroCount > 1) {
						putchar('A');
						zeroCount--;
					} else {
						putchar('B');
					}
				} else {
					putchar('C');
				}
			}
			putchar('\n');
		}
	}
	return 0;
}