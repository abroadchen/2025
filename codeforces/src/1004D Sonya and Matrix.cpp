//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
判断 n 是否为质数。注意它对 n=2 特判 true
在 n 为质数 / 网格退化情况下，合法的 cnt 应满足特殊形：

mx = cnt 非零的最大下标，即最大曼哈顿距离；
要求 1..mx 每个距离都有出现（cnt 中间不能跳空）；
前部若干距离出现 2 次（mn 记录能连续凑够 2 次的最远距离，实为：从 1 开始连续 cnt[i]==2 的最后一位）；
mn+1..mx 全部恰好出现 1 次。
若都满足，f=1 时输出 1 n 和 1 mn+1。

这对应退化为 1 行/1 列（直线）网格的情形

读入 n 个数并统计每种距离出现次数 cnt[k]
只有一个距离值：若为 0（说明 1×1 网格，点到自身距离 0）则输出 1 1（行列均为 1，点 (1,1)）；否则无解
cnt[0]（距离为 0 的次数）必须恰好 1 次（即隐藏点在网格内，且只有一个格点距离为 0——就是点自身）。
若 cnt[0]==0（点不在网格内）或 >1（多点距离 0，矛盾）→ 无解
距离 0 出现自身、距离 k 在一个网格里最多出现在 4 个方向对称点上，故 cnt[k] 理论上 ≤ 4k（i<<2 即 4i）。超过即非法
当 n 是质数时，网格只可能是退化（1×n 或 n×1），用 check 验证并输出
先试退化直线形状能否匹配，能则输出
求解思路：对 A×B 网格及隐藏点 (x,y)，距离 0 出现 1 次、距离 k 出现次数 ≤ 4k，且能取到 4k 只有在"四角全占"时。代码取第一个不达上限的距离 i 作为 x（行坐标方向），再利用对称性设 y
枚举 A（t），B = n/A。
利用"最大曼哈顿距离 = (A-1)+(B-1) 或相关"的约束，用 y = A+B-x-mx 反推列坐标。
对每种 A×B 几何配置，暴力把每个格点到 (x,y) 的曼哈顿距离做成频次 h，与输入 cnt 逐一比对；一致即找到解，否则试下一个因子
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e6+10;

inline bool is_prime(int n) {
    if (n == 2) return true;
    for (int i = 2; i*i <= n; ++i)
        if (n%i == 0) return false;
    return true;
}

int n, cnt[N];
inline bool check(bool f=0) {
    int mx = 0, mn = 0, i;
    rep(i,n) if (cnt[i]) mx = i;
    rep(i,mx) if (!cnt[i]) {
        if (f) cout << "-1\n";
        return false;
    }
    rep(i,mx) {
        if (cnt[i] != 2) break;
        mn = i;
    }
    for (i = mn+1; i <= mx; ++i)
        if (cnt[i] != 1) {
            if (f) cout << "-1\n";
            return false;
        }
    if (f) cout << 1 << ' ' << n << '\n' << 1 << ' ' << mn+1 << '\n';
    return true;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int i, a[N], mx, x, t, h[N], j;
int main() {
    fast;
    n = rd();
    rep(i,n) { a[i] = rd(); ++cnt[a[i]]; }
    if (n == 1) {
        if (!a[1]) cout << "1 1\n 1 1\n"; else cout << "-1\n";
        return 0;
    }
    if (cnt[0] > 1 || !cnt[0]) { cout << "-1\n"; return 0; }
    rep(i,n) if (cnt[i] > i<<2) { cout << "-1\n"; return 0; }
    if (is_prime(n)) {
        if (!check()) cout << "-1\n"; else check(1);
        return 0;
    }
    if (check()) { check(1); return 0; }
    rep(i,n) mx = max(mx, a[i]);
    rep(i,n) if (cnt[i] < i<<2) { x = i; break; }
    rep(t,n) if (n%t == 0) {
        for (i = 0; i <= n; ++i) h[i] = 0;
        int A = t, B = n/t, y = A + B - x - mx;
        rep(i,A) rep(j,B) ++h[abs(i-x)+abs(j-y)];
        bool flg = 0;
        rep(i,n) if (h[i] != cnt[i]) { flg = 1; break; }
        if (!flg) {
            cout << A << ' ' << B << '\n' << x << ' ' << y << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}