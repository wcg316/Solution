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
		vector<int> b(n);
		for (auto& num : b) {
			num = read();
		}
		for (int i = 0; i < n; i++) {
			if (b[i] == 1) {
				break;
			} else if (b[i] == -1) {
				b[i] = 1;
				break;
			}
		}
		for (int i = n - 1; ~i; i--) {
			if (b[i] == 1) {
				break;
			} else if (b[i] == -1) {
				b[i] = 1;
				break;
			}
		}
		for (auto num : b) {
			write(num == -1 ? 0 : num);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}