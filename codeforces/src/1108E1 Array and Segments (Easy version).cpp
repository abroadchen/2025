//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
q[N]：存 m 个区间操作的端点（q[j].x, q[j].y）
a[N]: 原数组。
mx: 当前最优的 (max-min)。
cnt: 当前方案选中的区间个数。
x: 累加临时变量。
c[N]: 差分数组。
z[N]: 当前方案中被选中的区间编号集合。
t: 最终方案选中的区间个数。
s[N]: 最终方案被选中的区间编号
读 n 个数，记录全局最大 lm、最小 ln。
mx = lm - ln：不选任何区间的初始差值作为基准最优值。
读入 m 个区间的 x、y。
对每个位置 i（作为"最大值所在位置"的假设）：

初始化：cnt=0, x=0, lm=-inf, ln=inf。
构造差分数组：c[j] = a[j] - a[j-1]，即用差分表示原数组（a[0]=0）。这样 c 的前缀和可以还原出数组值。
选择区间：对所有区间 j，若它包含位置 i（q[j].x <= i && q[j].y >= i），则:
差分操作：c[q[j].x]--（左端 -1）、c[q[j].y+1]++（右端后 +1）——相当于对该区间整体减 1（因为 -- 在该区间还原出的前缀和里减 1）。
把区间编号 j 记入 z[++cnt]。
目的：让包含 i 的区间都减 1，从而让"最大值位置 i"本身被压低？不对——这里其实是想要"把不包含 i 的区间加、包含的减"来拉开差距。减 1 的是包含 i 的区间，等价于让这些位置的值下降，从而让「其他位置相对升高」。
实际上常见版本是"使包含 i 的区间 -1，不包含的 +1"来最大化解。这里只对包含 i 的减 1（相当于把该区间整体压低 1）。
还原并求 max-min：rep(j,n) { x += c[j]; lm=..., ln=... }。对差分数组做前缀和 x，还原出每个位置操作后的值，更新该位置的 lm、ln。
比较：若当前方案的 lm - ln > mx，则更新最优：记录 t=cnt（选中区间数）、mx 新差值、并把 z 拷贝到 s。
输出最大差值 mx、选中的区间个数 t、以及这些区间编号 s[1..t]（每个后面带空格）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 305, inf = 1e8;

struct node { int x, y; } q[N];

int n, m, a[N], mx, cnt, x, c[N], z[N], t, s[N];
int main() {
    fast;
    cin >> n >> m;
    int lm = -inf, ln = inf;
    rep(i,n) { cin >> a[i]; lm = max(lm, a[i]); ln = min(ln, a[i]); }
    mx = lm - ln;
    rep(i,m) cin >> q[i].x >> q[i].y;
    rep(i,n) {
        cnt = 0; x = 0; lm = -inf, ln = inf;
        rep(j,n) c[j] = a[j] - a[j-1];
        rep(j,m) if (q[j].y >= i && q[j].x <= i) { c[q[j].x]--; c[q[j].y+1]++; z[++cnt] = j; }
        rep(j,n) { x += c[j]; lm = max(lm, x); ln = min(ln, x); }
        if (lm - ln > mx) {
            t = cnt; mx = lm - ln;
            rep(j,cnt) s[j] = z[j];
        }
    }
    cout << mx << '\n' << t << '\n';
    rep(i,t) cout << s[i] << ' ';
    return 0;
}