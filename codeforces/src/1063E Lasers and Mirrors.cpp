//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
标准并查集，merge 把较大编号作为父亲（这里大小关系用于后面定位）
to[i]：i 指向的下标；fr[]：反向映射；
chk += |to[i]-i|：用于判断置换是否为恒等置换（如果所有 to[i]==i，则 chk==0）
若 chk==0（即恒等置换），输出 n 并直接跳到输出网格（此时网格全为 '.'）。
否则输出 n-1（第一步输出一个数，作为某种"取值"）
对每个环组件 x（且 x != n，n 单独处理），计算环大小 sz 和最小下标 mn。
l = cnt+1, r = cnt+sz 分配给该环一段区间 [l,r]
沿置换环 y → to[y] 走，对沿环相邻对 (y, z=to[y])，若 z>y 画 '/'，否则画 '\'，放在行 cnt+1。
之后在边界行 r、l 放额外的 '/'、'\' 收尾（把环"闭合"）。
这是把环结构映射为网格上的路径线的构造
从 n 开始，沿 to[] 往前走到再次到 n，把这条"链"也画成斜线
输出整个 n×n 网格，每行末尾换行。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 1145;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x < y) swap(x, y);
    if (x != y) fa[y] = x;
}

int n, to[N], fr[N], chk, vis[N], cnt, l, r, t;
char s[N][N];
int main() {
    fast; int i, j;
    cin >> n;
    rep(i,n) fa[i] = i;
    rep(i,n) cin >> to[i], fr[to[i]] = i, chk += abs(to[i]-i), merge(i, to[i]);
    rep(i,n) rep(j,n) s[i][j] = '.';
    if (!chk) { cout << n << '\n'; goto end; }
    cout << n-1 << '\n';
    rep(i,n) if (find(i) != n && !vis[find(i)]) {
        cerr << i << " ? " << find(i) << '\n';
        int x = find(i); vis[x] = 1;
        int sz = 0, mn = n + 1;
        rep(j,n) if (find(j) == x) sz++, mn = min(mn, j);
        if (sz == 1) { cnt++; continue; }
        l = cnt+1, r = cnt+sz;
        int y = to[to[mn]];
        while (y != to[mn]) {
            int z = to[y]; cnt++;
            if (z > y) s[cnt+1][y] = s[cnt+1][z] = '/';
            else s[cnt+1][y] = s[cnt+1][z] = '\\';
            y = to[y];
        }
        s[r][n] = '/', s[l][n] = '\\', s[l][to[y]] = '\\';
        cnt = r;
    }
    t = n;
    while (to[t] != n) {
        int y = to[t]; cnt++;
        if (y > t) s[cnt][t] = s[cnt][y] = '/';
        else s[cnt][t] = s[cnt][y] = '\\';
        t = to[t];
    }
    end:
    rep(i,n) rep(j,n) cout << s[i][j], j == n ? void(cout << '\n') : void();
    return 0;
}