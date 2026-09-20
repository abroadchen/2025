//
// Created by Psy.C on 2026/9/20.
//
/**
① 递归出口
空矩形或当前偏移 f 已超过 k → 贡献 0。
保证 x ≥ y（用 x 的最大幂做主轴拆解更简单）
② 基础情况：x 恰为 2 的幂
x == (x&-x) 表示 x 正好是 2 的幂（lowbit = 自身）。
在这个"方块"里，函数值随偏移 f 从 f 线性增长到 f+x-1，是一段等差数列：
首项 l=f，末项 r=min(k, f+x-1)（受上限 k 截断）。
等差数列和 (l+r)*(项数)/2，再乘上 y（纵向重复 y 次）。
这样能 O(1) 算出一整块 2 的幂方块的贡献，避免深入递归——这就是加速的关键。
③ 一般情况：x 不是 2 的幂 → 分治拆解
找到 ≤ x 的最大 2 的幂 d（比如 x=13，d=8
④ 情况 A：y ≤ d（矩形较高不超 d）‍
把 x×y 拆成左 d×y 和右 (x-d)×y 两块分别递归。偏移 f 随 x 轴推进增加 d
⑤ 情况 B：y > d（矩形两维都大）‍
把矩形按 d 切成 4 块（拿 d 当坐标轴刻度），偏移 f 根据块在 x/y 轴上的位置相应增加。
因为是二进制分治，递归深度 O(log max)，总块数可控

用二维前缀和容斥求任意子矩形 [x1..x2]×[y1..y2] 的和：
S(x2,y2) - S(x1-1,y2) - S(x2,y1-1) + S(x1-1,y1-1)。
即 dfs(rect) = F(x2,y2) − F(x1−1,y2) − F(x2,y1−1) + F(x1−1,y1−1)。
+2*mod 防止减出负数，再取模。
偏移 f 初始为 1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define add(x,y) (x+=y)%=mod
using namespace std;
constexpr int mod = 1e9+7;
ll k;
ll dfs(int x, int y, ll f) {
    if (x == 0 || y == 0 || f > k) return 0;
    if (x < y) swap(x, y);
    if (x == (x&-x)) {
        ll l = f, r = min(k, f+x-1);
        return (l+r)*(r-l+1)/2%mod*y%mod;
    }
    int d = 1;
    ll ret = 0;
    while ((d<<1) < x) d <<= 1;
    if (y <= d) {
        add(ret, dfs(d, y, f));//左块：宽 d
        add(ret, dfs(x-d, y, f+d));//右块：宽 x-d，偏移 +d
    } else {
        add(ret, dfs(d, d, f));//左上 d×d
        add(ret, dfs(x-d, d, f+d));//右上 (x-d)×d
        add(ret, dfs(d, y-d, f+d));//左下 d×(y-d)
        add(ret, dfs(x-d, y-d, f));//右下 (x-d)×(y-d)
    }
    return ret;
}


int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2 >> k;
        ll ans = dfs(x2, y2, 1) + dfs(x1-1, y1-1, 1) -
            dfs(x1-1, y2, 1) - dfs(x2, y1-1, 1);
        cout << (ans+2*mod)%mod << '\n';
    }
    return 0;
}