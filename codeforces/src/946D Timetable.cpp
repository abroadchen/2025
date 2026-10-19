//
// Created by Psy.C on 2026/10/18.
//
/**
N=505: 数组上限。
n: 行数；nn: 每行最多列数；m: 总共允许删除的 1 的个数。
c[i][k]: 第 i 行删 k 个 1 的最小跨度。
a[]: 临时存当前行中各个 1 的位置（下标）。注意：a 是全局数组，但这里复用来存"当前行"的 1 的位置——其实是每次循环覆盖使用。
s[i]: 第 i 行中 '1' 的个数。
f[i][j]: DP 数组，前 i 行、总共删 j 个 1 的最小总跨度。
ch: 读字符用
memset(c, 0x3f, ...): 把 c 初始化为 INF（0x3f3f3f3f ≈ 1e9）。

对第 i 行：

读 nn 个字符，若是 '1'，则记下它所在的列号 j 到 a[++s[i]]。结束时 s[i] 就是这行 1 的个数，a[1..s[i]] 是从左到右各 1 的列号（因为 j 递增读入，天然有序）。
c[i][s[i]] = 0：如果整行所有 1 都删掉（删 s[i] 个），剩余为空，跨度为 0。这是边界。
内层双重循环：枚举剩余 len 个 1，再枚举这 len 个 1 的连续段起点 l（在有序位置 a[1..s] 中取 a[l..r]，其中 r = l+len-1，即长度为 len 的连续区间）。
关键观察（贪心性质）：若要从一行里删掉恰好 k = s[i]-len 个 1，且保留的 1 跨度最小，那么保留的一定是在位置序列里连续的 len 个 1。因为如果有跨越的空隙（删掉中间某段），跨度会更大；最优总是去掉两头的 1，保留下"位置序列中连续的一段"。
该连续段的跨度为 a[r] - a[l] + 1（最右列 − 最左列 + 1）。
c[i][s[i]-len] = min(..., a[r]-a[l]+1)：即在"删掉 s[i]-len 个"这一档，取所有可能连续段跨度的最小值。
这样预处理出 c[i][k]：第 i 行删 k 个的最小跨度
f 初始化为 INF；f[0][j] = 0：前 0 行、不管删多少个，总跨度都是 0（边界）。
三重循环分组背包：
i: 当前处理到第 i 行（组）。
j: 前 i 行总共已删的 1 个数。
k: 第 i 行这一行删掉的 1 个数，最多不超过 min(j, s[i])（不能超过已分配的总数和该行所有 1 数）。
转移：f[i][j] = min(f[i][j], f[i-1][j-k] + c[i][k]) — 前 i−1 行删 j-k 个，加上第 i 行删 k 个的跨度 c[i][k]。
这就是 每组取一种（每行决定删 k 个）的分组背包 / 多重背包式 DP，目标最小化总跨度。
输出前 n 行、恰好总共删 m 个 1 时的最小总跨度 f[n][m]

复杂度：预处理每行 O(s[i]²)（内层两重循环），DP O(n·m²)（i、j 各 n、m，k 最多 m）。对 n、m ≤ 500 完全可行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 505;

int n, nn, m, c[N][N], a[N], s[N], f[N][N];
char ch;
int main() {
    fast;
    cin >> n >> nn >> m;
    memset(c, 0x3f, sizeof(c));
    rep(i,1,n) {
        rep(j,1,nn) {
            cin >> ch;
            if (ch == '1') a[++s[i]] = j;
        }
        c[i][s[i]] = 0;
        rep(len,1,s[i]) rep(l,1,s[i]-len+1) {
            int r = l + len - 1;
            c[i][s[i]-len] = min(c[i][s[i]-len], a[r]-a[l]+1);
        }
    }
    memset(f, 0x3f, sizeof(f));
    rep(j,0,m) f[0][j] = 0;
    rep(i,1,n) rep(j,0,m) rep(k,0,min(j,s[i]))
        f[i][j] = min(f[i][j], f[i-1][j-k]+c[i][k]);
    cout << f[n][m];
    return 0;
}