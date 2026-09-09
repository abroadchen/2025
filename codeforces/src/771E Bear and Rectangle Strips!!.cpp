//
// Created by Psy.C on 2026/9/8.
//
/**
node：一条"转移边"，x、y 是两维坐标，c 是这条边的权值（代价/步数）。
vc[i]：挂在对角线上 min(x,y)=i 的所有转移边。
dp[i]：到达"对角线状态 i"的最大/最优值
把一条边 (x,y,权c) 登记进数据结构。
用状态的较大坐标 max(x,y) 作为 dp 的索引并尝试更新 dp[max(x,y)] = max(..., c)。
同时把这条边压入 vc[min(x,y)]（按较小坐标分组，方便后续按对角线顺序处理）
从状态 (x,y) 出发，枚举三种扩展方向。
往 x 方向前进一步：(x→x+1)，权值保持 c；同时查 nx[0][x+1]——利用预处理好的"最近同前缀和位置"做跳跃，跳到位置 i 并权值 +1。
往 y 方向前进一步：(y→y+1)，同理查 nx[1][y+1] 做跳跃。
对角线方向（仅当 x==y 时）：利用 nx[2][x+1] 跳到 (i,i)，权值 +1
读入两个数组。
单次遍历 i=1..n，维护三个前缀和轨道 s[0],s[1],s[2]。
mp[j][s[j]] = i：在更新前缀和之前，记录"当前前缀和值 s[j] 上一次出现在位置 i"。
更新前缀和后，if (mp[j][s[j]]) nx[j][mp[j][s[j]]] = i：若当前前缀和 s[j] 此前出现过（在位置 mp[j][s[j]]），
则把 nx[j][上一次位置] = i。即 nx[j][p] = 从位置 p 出发、下一个前缀和值与 p 处相等的位置（同类和值再次出现，可跳跃的最近点）
主循环遍历对角线 i=0..n-1。
先从状态 (i,i) 用当前 dp[i] 展开 ex(i,i,dp[i])。
再遍历挂在 i 上的边 vc[i]：若某条边的 y==i（横着走到 i）且权值为 dp[i]+1，取最小 x 作为 l；同理 x==i 取最小 y 作为 r。
再用 ex(l,i,...)、ex(i,r,...) 二次展开。
最终输出 dp[n]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 3e5+5;
struct node { int x, y, c; };

vector<node> vc[N];
int dp[N];
void add(int x, int y, int c) {
    dp[max(x, y)] = max(dp[max(x, y)], c);
    vc[min(x, y)].push_back({.x = x, .y = y, .c = c});
}

int n, nx[3][N];
void ex(int x, int y, int c) {
    if (x < n) {
        add(x+1, y, c);
        int i = nx[0][x+1];
        if (i) add(i, y, c+1);
    }
    if (y < n) {
        add(x, y+1, c);
        int i = nx[1][y+1];
        if (i) add(x, i, c+1);
    }
    if (x < n && x == y) {
        int i = nx[2][x+1];
        if (i) add(i, i, c+1);
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[2][N], s[3];
map<int, int> mp[3];
signed main() {
    fast;
    n = rd();
    for (auto &i : a)
        for (int j = 1; j <= n; ++j) i[j] = rd();
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) mp[j][s[j]] = i;
        s[0] += a[0][i]; s[1] += a[1][i]; s[2] += a[0][i] + a[1][i];
        for (int j = 0; j < 3; ++j)
            if (mp[j][s[j]])
                nx[j][mp[j][s[j]]] = i;
    }
    for (int i = 0; i < n; ++i) {
        ex(i, i, dp[i]);
        int l = n+1, r = n+1;
        for (auto [x, y, c] : vc[i]) {
            if (y == i && c == dp[i] + 1) l = min(l, x);
            if (x == i && c == dp[i] + 1) r = min(r, y);
        }
        if (l <= n) ex(l, i, dp[i] + 1);
        if (r <= n) ex(i, r, dp[i] + 1);
    }
    cout << dp[n] << '\n';
    return 0;
}