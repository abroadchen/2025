//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
有两个"周期区间"：

区间 A：[la, ra]，每 ta 单位重复一次；且 A 整体可以在时间轴上随意左右平移（等价于它能出现在任意 la + k*ta 的位置）。
区间 B：[lb, rb]，每 tb 单位重复一次；同样可随意平移。
要求：通过平移（平移量是各自周期 ta / tb 的整数倍）让 A 和 B 的某两个版本重叠最大化，输出最大重叠长度。

因为 A 可任意平移，我们先把 A 固定住，考察 B 怎么平移使重叠最大
这几行把整个坐标系平移到 A 的左端点 la 为原点，让 A 变成 [0, ra]。B 变成相对 A 的 [lb, rb]。这样问题就"以 A 为基准"了
这是本解法最妙的一步。因为 ta 和 tb 的最小公倍数周期会带来很大的周期，而有效共同周期是 gcd(ta,tb)。把 tb 替换为 g = gcd(ta, tb) 后，B 的可平移分辨率就变成了 g。这一步让后面的平移枚举变得可行（只需在一个 g 周期内讨论）。

（直观理解：A 周期 ta、B 周期 tb，两者能重叠的版本可以看成在步长 g=gcd(ta,tb) 上滑动 B 的整数倍。）
md(lb, tb) 是向下取整除法（对任意符号都向下取整，见下节）。
取 v = md(lb, tb)，即 lb 除以 tb 的向下取整，然后 lb -= v*tb，rb -= v*tb。
效果：把 B 整体平移到 0 <= lb < tb 的范围，使其落在一个基本周期单元内。这样 B 的每个副本在 [lb, rb] 基础上每隔 tb 重复
t = md((lb-rb), tb)：让 B 的右端 rb 被平移若干个 tb，使它尽量靠近并右移 A 的右端 ra。
得到的 l, r 是 B 的一个"理想对齐副本"的左右端点，其中 r 落在 ra 附近（可能是 ra 上方或下方的最近副本）。
这一步是在找 B 的哪个副本最贴合 A，作为重叠候选之一。t 可能为 0、-1 等，代表不同的平移倍数
这里枚举几个可能产生最大重叠的 B 候选位置，两两与 A 的 [0, ra] 求重叠长度，取最大值：

0ll：无重叠的情况兜底（避免负数）。
min(rb-tb, ra)+1：B 偏移一个 tb 后与 A 的重叠（rb-tb 表示回退一个周期）。
min(rb, ra)-lb+1：B 原始位置（已在 [0,tb) 内）与 A 的重叠。
min(ra,r)-max(0,l)+1：第 4 步算出的理想副本 [l,r] 与 A 的重叠（注意 A 的左端是 0，所以用 max(0,l)）。
min(r+tb,ra)-max(0,l+tb)+1：再偏移一个 tb 的副本 [l+tb, r+tb] 与 A 的重叠。
每项都形如 min(右端, ra) - max(左端, 0) + 1，即两区间在 [0, ra] 上的交集长度。因为这是端点都是整数的离散区间问题（题中出现的都是整数网格意义下的区间重叠，重叠指共享的整数点个数），所以用 +1。

取所有候选里最大的那个即为答案

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll md(ll x, ll y) {
    if (y < 0) { x = -x; y = -y; }
    if (x >= 0) return x/y;
    if (x%y == 0) return x/y;
    return x/y - 1;
}

ll la, ra, ta, lb, rb, tb;
int main() {
    fast;
    cin >> la >> ra >> ta >> lb >> rb >> tb;
    ra -= la; lb -= la; rb -= la; tb = gcd(ta, tb);
    ll v = md(lb, tb); lb -= v*tb; rb -= v*tb;
    ll t = md(lb-rb, tb), r = rb+t*tb, l = lb+t*tb;
    cout << max({0ll,min(rb-tb,ra)+1,min(rb,ra)-lb+1,min(ra,r)-max(0ll,l)+1,
        min(r+tb,ra)-max(0ll,l+tb)+1});
    return 0;
}