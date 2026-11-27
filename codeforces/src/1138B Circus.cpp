//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
c0（0,0）和 c2（1,1）：各存到 v0、v2。
(0,1) 和 (1,0) 两类合并计数到 c1（存同一数组 v1）。
sum 记录 (0,1) 和 (1,1) 的总数（即两串对应位中 q=1 的个数）
枚举 i = 从 (1,1) 类中选几个。
由组合约束反推 x（需从 (0,1) 类取的个数）和 y（需从 (0,0) 类取的个数）。
当组合可行（x≥0、y≥0、x≤c1、y≤c0）时，按顺序输出各位置的编号

i = 从 c2（1,1）取的个数
x = 从 c1（0,1 与 1,0）取的个数
y = 从 c0（0,0）取的个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<(n); ++i)
using namespace std;

constexpr int N = 1e5+5, M = 5005;
struct edge { int to, nxt; } t[N<<1];

int head[N], cnt;
inline void add(int u, int v) {
    t[++cnt] = {v, head[u]}; head[u] = cnt;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, c0, c1, c2, sum;
char p[M], q[M];
vector<int> v0, v1, v2;
int main() {
    fast;
    n = rd(); scanf("%s %s", p+1, q+1);
    for (int i = 1; i <= n; ++i) {
        if (p[i] == '0' && q[i] == '0') ++c0, v0.push_back(i);
        if (p[i] == '0' && q[i] == '1') ++c1, v1.push_back(i), ++sum;
        if (p[i] == '1' && q[i] == '0') ++c1, v1.push_back(i);
        if (p[i] == '1' && q[i] == '1') ++c2, v2.push_back(i), ++sum;
    }
    int x, y;
    rep(i,c2+1) {
        x = sum - i*2, y = n/2-i-x;
        if (x < 0 || y < 0) continue;
        if (x <= c1 && y <= c0) {
            rep(j,y) cout << v0[j] << ' ';
            rep(j,x) cout << v1[j] << ' ';
            rep(j,i) cout << v2[j] << ' ';
            exit(0);
        }
    }
    cout << "-1\n";
    return 0;
}