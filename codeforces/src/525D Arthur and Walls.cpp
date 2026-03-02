//
// Created by Psy.C on 2026/3/2.
//

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2100;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m;
char s[N][N];
void dfs(const int x, const int y) {
    if (x < 0 || x >= n-1 || y < 0 || y >= m-1) return;
    int sum = 0, tx = 0, ty = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            if (s[x+i][y+j] == '*') {
                sum++; tx = x + i; ty = y + j;//最后一个'*'的位置
            }
    if (sum == 1) {
        s[tx][ty] = '.';
        for (int i = -1; i < 1; ++i)
            for (int j = -1; j < 1; ++j)
                dfs(tx + i, ty + j);
    }
}

int main() {
    read(n); read(m);
    for (int i = 0; i < n; ++i) scanf("%s", s[i]);
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < m-1; ++j)
            dfs(i, j);
    for (int i = 0; i < n; ++i) puts(s[i]);
    return 0;
}