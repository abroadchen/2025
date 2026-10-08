//
// Created by Psy.C on 2026/10/8.
//
/**
a[2][M]：只保留两行的格子值（now 与 now^1，即当前行与上一行），a[row][col] = 该格是否为"1"（有障碍/被占用）
now = i&1：当前行在滚动数组中的槽位（0 或 1）。
每行读入一个字符串 s，每个字符是 1 个十六进制位（表示 4 个连续格子）
每个十六进制字符的低 4 个 bit 依次对应 4 个格子 j*4, j*4-1, j*4-2, j*4-3。
每出现一个"1"格，ans++（先假设每个 1 是独立连通块）
当前行左右相邻两个 1 若不在同一集合，就合并，ans--
当前行与上一行（now^1）同列的 1 若不同集合就合并，ans--
输出整张图中"1 的连通块个数"（通过"总数 - 合并次数"动态维护)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+10, M = N/10;

int fa[N];
int find(int x) {
    if (x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

int a[4][M];
int main() {
    fast;
    int n, m; cin >> n >> m;
    int ans = 0, i, j;
    for (i = 1; i <= n; ++i) {
        int now = i&1;
        string s; cin >> s; s = " " + s;
        for (j = 1; j <= m/4; ++j) {
            int res;
            if (s[j] >= '0' && s[j] <= '9') res = s[j] - '0';
            else res = s[j] - 'A' + 10;//十六进制字符转数值
            a[now][j*4] = res&1, ans += res&1, res>>=1;
            a[now][j*4-1] = res&1, ans += res&1, res>>=1;
            a[now][j*4-2] = res&1, ans += res&1, res>>=1;
            a[now][j*4-3] = res&1, ans += res&1, res>>=1;
        }
        int t = now*m;//本行并查集的基址
        for (j = 1; j <= m; ++j) fa[t+j] = t+j;//初始化本行每个格子的并查集节点
        for (j = 1; j < m; ++j) {
            if (a[now][j] && a[now][j+1]) {//左右两个都是1
                int pa = find(t+j), pb = find(t+j+1);
                if (pa != pb) { fa[pb] = pa; ans--; }//合并则连通块数-1
            }
        }
        for (j = 1; j <= m; ++j) {
            if (a[now][j] && a[now^1][j]) {
                int pa = find(t+j), pb = find((now^1)*m+j);
                if (pa != pb) { fa[pb] = pa; ans--; }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}