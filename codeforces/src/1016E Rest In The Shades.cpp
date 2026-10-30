//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
计算从点 (p, q) 到 (u, v) 的方向，投影到 y=0（x轴）的交点 x 坐标。

几何意义：已知点 (p, q)（墙端点，q 是它的 y，通常墙顶 y 很大）和点 (u, v)（观察者，v=sy），求这两点连线与地平线（y=0，即 x 轴）的交点横坐标。
公式展开：直线过 (p,q) 和 (u,v)，令 y=0：
斜率方向，交点 x = u - v*(p-u)/(q-v)。
若 q == v（即墙顶 y 与观察点同高，水平线），直接返回 u（退化情况，避免除零）。
返回值是该墙边界投影到 x 轴上的位置，用于判断遮挡区间。
u 扮演"观察点 x 坐标参考"（后续传 a 或 b），v 是观察高度 sy，p,q 是被投影点的坐标
sy：观察高度；a,b：目标线段端点；n：墙的数量。
每堵墙读入 l, r，把端点拆入离散化数组 p：
左端 l：cnt++，s[cnt]=s[cnt-1]（左端点处累积长度不变）。
右端 r：cnt++，s[cnt]=s[cnt-1]+(r-l)（累积的"覆盖长度"加上这段墙的长度 r-l）。
所以 p[] 是排序好的端点坐标，s[] 是"从最左端累加到该端点处，被墙覆盖的总长度"。这构成一个前缀和式区间覆盖结构：任意 [l,r] 区间被遮挡的长度 = s[R]-s[L] + 边界修正。
⚠️ 这里默认墙端点已经按 x 有序依次读入（且不重叠）。s 记录的是累计覆盖长度，说明墙区间在该题中互不重叠且端点有序
q 个查询，每个给一个"遮挡物端点" (x, y)（可能在移动，比如一个会动的挡板顶）。
l = get(a, sy, x, y)：把 (x,y) 按观察点 (a, sy) 投影到 x 轴。
r = get(b, sy, x, y)：同理用观察点 (b, sy) 投影。
得到遮挡区间 [l, r]——即这个挡板在目标线段 [a,b] 上投下的影子区间
L：第一个 p[i] >= l 的位置。
R：第一个 p[i] > r 的位置再减 1（即最后一个 p[i] <= r 的位置）。
若 L > R：查询区间 [l,r] 完全落在两个端点之间、没覆盖任何端点的整段内，说明它要么完全在一个墙内、要么完全在空隙里：
若 R&1（R 是奇数）→ 空隙在墙内，整个 [l,r] 都被遮挡，输出 b-a（整段被遮）。
否则 → 空隙里，没被遮，输出 0。
在 L <= R 时，计算 [l,r] 内被墙覆盖的总长度：

s[R]-s[L]：从端点 p[L] 到 p[R] 完全覆盖的段累计长度。
+(L&1 ? 0 : p[L]-l)：若 L 是偶数（起点在半段墙内 … 依题意），补上左端点之前的半段 p[L]-l；若 L 奇数则不加。
+(R&1 ? r-p[R] : 0)：若 R 是奇数，补上到右端点之后的半段 r-p[R]；否则不加。
再整体乘缩放系数 (b-a)/(r-l)：把 x 轴上的遮挡长度换算回目标线段 [a,b] 上的实际长度

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
using namespace std;

constexpr int N = 4e5+5;

db get(db u, db v, db p, db q) { return u == p ? u : u-v*(p-u)/(q-v); }

int n, cnt, q;
db sy, a, b, p[N], s[N];
int main() {
    fast;
    cin >> sy >> a >> b >> n;
    for (int i = 1, l, r; i <= n; ++i) {
        cin >> l >> r;
        p[++cnt] = l; s[cnt] = s[cnt-1];
        p[++cnt] = r; s[cnt] = s[cnt-1]+r-l;
    }
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        db x, y; cin >> x >> y;
        db l = get(a,sy,x,y), r = get(b,sy,x,y);
        int L = lower_bound(p+1,p+1+cnt,l)-p, R = upper_bound(p+1,p+cnt+1,r)-p-1;
        if (L > R) cout << fixed << setprecision(16) << (R&1?b-a:0) << '\n';
        else cout << fixed << setprecision(16) <<
            (s[R]-s[L]+(L&1?0:p[L]-l)+(R&1?r-p[R]:0))*(b-a)/(r-l) << '\n';
    }
    return 0;
}