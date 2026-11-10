//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
s[i]：每个物品，a=价值，p=容量/代价。
排序按 a 从大到小（大价值先选，因为放大系数随选择顺序增大，先放大价值更优）
p1[i] = (10/9)^i：第 i 个被选中的物品加权放大倍数。先选的物品越大放大越划算，所以决定了前面按 a 降序
读 n 个物品、以及两个参量 c、t（温度/时间参数）
f[j][k] = 选恰好 j 个物品、总容量恰好 k，且“成本” = Σ (被选物品 a × 它被选中顺序的放大系数 p1[j]) 的最小值。

注意这里滚动数组：j 从大到小枚举防覆盖；物品按 a 降序，因此后面选中时顺序 j 越大，放大系数越大。

10*i 是容量上界估计（每个 p 至多……题目若 p≤10 则可设 10i）。

成本项 s[i].a * p1[j]：第 j 个被选物品价值放大 (10/9)^j 倍，先选大的放大更多，与排序一致
对每个 (i=j 物品数, k 容量) 状态，完成时间函数为
time(x) = x + f/(1+c·x) + 10*i（其中 x 是要三分求解的某个速度/时间变量，10*i 是固定的切菜/等待基础时间）。
这个 x + f/(1+cx) 是凸函数，用三分在 [0,t] 上找最小完成时间。
若最小完成时间 < 时间上限 t，则该选 j 个物品可行，更新 ans=j（j 越大越好）。
为减小范围，从 ans+1 开始枚举 j
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i = 1; i <= (n); ++i)
#define db double
#define eps 1e-5
using namespace std;

constexpr int N = 101, M = 1010;
constexpr long long inf = 1e18;

struct node { int a, p; } s[N];
inline bool operator<(const node& a, const node& b) { return a.a > b.a; }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

db p1[N], f[N][M];
int main() {
    p1[0] = 1;
    rep(i,N-1) p1[i] = p1[i-1]*10/9;
    int T = rd();
    db l, r, lm, rm, ls, rs;
    while (T--) {
        int n = rd();
        db c, t; cin >> c >> t;
        rep(i,n) s[i].a = rd(), s[i].p = rd();
        sort(s+1, s+n+1);
        for (auto &i : f) for (auto &j : i) j = inf;
        f[0][0] = 0;
        rep(i,n) for (int j = i; j; --j) for (int k = s[i].p; k <= 10*i; ++k)
            f[j][k] = min(f[j][k], f[j-1][k-s[i].p]+s[i].a*p1[j]);
        int ans = 0;
        rep(i,n) for (int j = ans+1; j <= 10*i; ++j) {
            l = 0, r = t;
            while (r-l > eps) {
                lm = l + (r-l)/3; rm = lm + (r-l)/3;
                ls = lm + f[i][j]/(1+c*lm); rs = rm + f[i][j]/(1+c*rm);
                if (ls < rs) r = rm; else l = lm;
            }
            l = (l+r)*0.5;
            if (l+f[i][j]/(1+c*l)+10*i < t) ans = j;//实际完成时间 < 时限
        }
        cout << ans << '\n';
    }
    return 0;
}