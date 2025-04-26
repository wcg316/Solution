#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

int n;
bool visited[100001];
vector<vector<int>> tree;
vector<int> distances;

signed main() {
    memset(visited, false, sizeof(visited));
	n = read();
    tree.resize(n, vector<int>(1, -1));
    for (int i = 0; i < n - 1; i++) {
        int a = read(), b = read();
        tree[b][0] = a;
        tree[a].push_back(b);
    }
    int root = 0;
    while (~tree[root][0])
        root = tree[root][0];
    distances.resize(n);
    queue<int> q;
    distances[root] = 0;
    q.push(root);
    int highestLeaf = -1;
    while (!q.empty()) {
        int curr = q.front();
        int d = distances[curr] + 1;
        q.pop();
        for (int i = 1; i < tree[curr].size(); i++) {
            distances[tree[curr][i]] = d;
            highestLeaf = tree[curr][i];
            q.push(tree[curr][i]);
        }
    }
    int maxDistance = -1;
    distances[highestLeaf] = 0;
    q.push(highestLeaf);
    visited[highestLeaf] = true;
    while (!q.empty()) {
        int curr = q.front();
        int d = distances[curr] + 1;
        q.pop();
        for (int neighbor : tree[curr]) {
            if (neighbor != -1 && !visited[neighbor]) {
                distances[neighbor] = d;
                maxDistance = d;
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    write(maxDistance);
	return 0;
}