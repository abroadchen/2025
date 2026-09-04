//
// Created by Psy.C on 2026/9/4.
//
/**
N=105：矩阵最大维。
inf = 1ll<<60：表示极大值，用于初始化最小值。
a[N][N]：记录每个格子的访问次数
读入
n
n（行数）、
m
m（列数）、
k
k（总停留次数）、
(
x
,
y
)
(x,y)（查询目标）

若只有一行，则巴士只在第 1 行上沿列移动（从左到右，到第 m 列后回第 1 列）。
t
=
⌊
k
/
m
⌋
t=⌊k/m⌋：完整走完
m
m 个格子的轮数。之后还剩 k%m 步。
最大值：完整轮数基础上还要看余数。若 k%m != 0，则第一轮多走了一步，最大值是 t+1；否则所有格子都走了恰好 t 次，最大值是 t。因为所有格子轮流走，最大不会超过最小值+1。
最小值：就是 t（每个格子至少走满
t
t 轮，这里写法其实是统一的 t）。
目标格
(
x
,
y
)
(x,y)：因为只有一行，
x
=
1
x=1。前 k%m 个格子被多访问一次。若 k%m >= y（注意下标从 1 起，目标在余数覆盖范围内），则它是 t+1，否则是 t

loop：一个完整周期的状态数（如上推导）。
get = k / loop：完整跑了几整圈。
lst = k % loop：跑完整圈后还剩的步数
遍历每个格子。
若在第 1 行或第 n 行（首尾行），每个整圈出现 1 次 → 加 get。
若是中间行（1 < i < n），每个整圈出现 2 次（去程+回程）→ 加 get*2
从
(
1
,
1
)
(1,1) 出发，按实际路径走 lst 步，每步把对应格子 a[i][j]++。
移动逻辑：
j++：列递增（沿列方向推进）。
当 j > m（本列走完，到达列尾），重置 j=1，然后切换到下一列的方向：
若当前在
i
=
n
i=n（底部），下一个循环方向为向上 p=-1；
若当前在
i
=
1
i=1（顶部），方向为向下 p=1；
i += p 执行换行
遍历整个矩阵，分别取访问次数的最大值 mx 和最小值 mn
依次输出 mx（最大访问次数）、mn（最小访问次数）、a[x][y]（目标格访问次数），空格分隔、末尾换行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105;
constexpr ll inf = 1ll<<60;
ll n, m, k, x, y, a[N][N];
int main() {
    fast;
    cin >> n >> m >> k >> x >> y;
    if (n == 1) {
        ll t = k/m;
        if (k%m) cout << t+1 << ' '; else cout << t << ' ';
        cout << t << ' ';
        if (k%m >= y) cout << t+1; else cout << t;
        cout << '\n';
        return 0;
    }
    ll loop = n*m+(n-2)*m, lst = k%loop, get = k/loop;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (i == 1 || i == n) a[i][j] += get;
            else a[i][j] += get*2;
        }
    int i = 1, j = 1, p;
    while (lst > 0) {
        a[i][j]++; j++;
        if (j > m) {
            j = 1;
            if (i == n) p = -1;
            else if (i == 1) p = 1;
            i += p;
        }
        lst--;
    }
    ll mx = -1, mn = inf;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j) {
            mn = min(mn, a[i][j]);
            mx = max(mx, a[i][j]);
        }
    cout << mx << ' ' << mn << ' ' << a[x][y] << '\n';
    return 0;
}