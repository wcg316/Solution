#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
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
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

struct crood {
	int y, x;
};

const vector<vector<crood>> openings = {
	{{-1, 0}, {0, 1}, {1, 0}, {0, -1}},
	{{-1, 0}, {1, 0}},
	{{0, 1}, {0, -1}},
	{{-1, 0}, {0, 1}},
	{{1, 0}, {0, -1}},
	{{0, 1}, {1, 0}},
	{{-1, 0}, {0, -1}}
};
const vector<vector<vector<int>>> targets {
	{{0, 1, 4, 5}, {0, 2, 4, 6}, {0, 1, 3, 6}, {0, 2, 3, 5}},
	{{0, 1, 4, 5}, {0, 1, 3, 6}},
	{{0, 2, 4, 6}, {0, 2, 3, 5}},
	{{0, 1, 4, 5}, {0, 2, 4, 6}},
	{{0, 1, 3, 6}, {0, 2, 3, 5}},
	{{0, 2, 4, 6}, {0, 1, 3, 6}},
	{{0, 1, 4, 5}, {0, 2, 3, 5}},
};

int n, m;
bool visited[501][501];
vector<vector<int>> maze;

bool isValid(int nx, int ny, int type, int dir) {
	return
		nx >= 0 && nx < m && ny >= 0 && ny < n &&
		!visited[ny][nx] && maze[ny][nx] != -1 &&
		any_of(targets[type][dir].begin(), targets[type][dir].end(), [&](int t){
			return maze[ny][nx] == t;
		});
}

signed main() {
	n = read(), m = read();
	maze.resize(n, vector<int>(m));
	memset(visited, false, sizeof(visited));
	for (auto &row : maze) {
		for (int &r : row) {
			char c = getchar();
			switch (c) {
			case 'X':
				r = 0;
				break;
			case 'I':
				r = 1;
				break;
			case 'H':
				r = 2;
				break;
			case 'L':
				r = 3;
				break;
			case '7':
				r = 4;
				break;
			case 'F':
				r = 5;
				break;
			case 'J':
				r = 6;
				break;
			default:
				r = -1;
			}
		}
		getchar();
	}
	int maxArea = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] && maze[i][j] != -1) {
				int area = 0;
				queue<crood> q;
				q.push({i, j});
				area++;
				visited[i][j] = true;
				while (!q.empty()) {
					crood curr = q.front();
					q.pop();
					int type = maze[curr.y][curr.x];
					for (int dir = 0; dir < 4; dir++) {
						if (openings[type].size() < dir + 1)
							break;
						int ny = curr.y + openings[type][dir].y, nx = curr.x + openings[type][dir].x;
						if (isValid(nx, ny, type, dir)) {
							q.push({ny, nx});
							area++;
							visited[ny][nx] = true;
						}
					}
				}
				maxArea = max(maxArea, area);
			}
		}
	}
	write(maxArea);
	return 0;
}