//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
N：星球数上界。
inf=2e9：上界参考（燃料数量级）
n：星球数量。
m：飞船返回地球时希望剩余的最低燃料量 / 有效载荷（题中通常含义是"到达终点后想保留 m 吨"，初始燃料 = m + 消耗部分）。
a[i]、b[i]：第 i 个星球的起飞消耗系数与降落消耗系数（k 值，指"消耗 = 当前总质量 / k"）
sum = m + t：初始总质量 = 有效载荷 m + 初始燃料 t（模型的重心：总质量先包含 m 的有效载荷，再加燃料）。

rep(i,n) 遍历 n 个星球（起飞一次 + 降落一次为一轮）：

sum -= sum/a[i];：第 i 次 起飞。消耗燃料 = sum/a[i]（总质量除以起飞系数），从总质量减去。

sum -= sum/b[(i==n?1:i+1)];：本次目标星球的 降落。b[(i==n?1:i+1)] 即下一个（循环）星球的降落系数为 b；消耗 sum/b[next]。

每步用的是更新后的当前 sum 去计算消耗（因为先减去起飞损耗，再算降落损耗），这与题意"消耗基于当前剩余质量"一致。
走完 n 次「起飞+降落」后，sum 表示回到地球时剩余的燃料 + 有效载荷。

return sum >= m;：若剩余总质量 ≥ m（即有效载荷没被损掉，燃料够用），返回 true —— t 吨燃料可行
读入 n、m，再读 a[]（起飞系数）、b[]（降落系数）。
二分区间 [0, inf+10]：l=0，r 取一个很大的上界。
while (r-l > eps)（eps=1e-6）浮点二分收缩区间：
mid=(l+r)/2。
若 check(mid) 为真（mid 够用）→ 把右界压到 mid（答案 ≤ mid）。
否则（mid 不够）→ 左界移到 mid。
二分结束后若 l>=inf（说明上界内都不可行）→ 输出 -1（不可能）。
否则输出 l，保留 7 位小数

每次 check O(n)，二分约 log((inf)/eps) ≈ log(2e15) ≈ 51 次。
总复杂度 O(n · log(inf/eps)) ≈ O(5e4)，非常快
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define eps 1e-6
using namespace std;

constexpr int N = 1e3+5, inf = 2e9;

ll m, n, a[N], b[N];
bool check(double t) {
    double sum = m + t;
    rep(i,n) {
        sum -= sum/a[i];
        sum -= sum/b[(i==n?1:i+1)];
    }
    return sum >= m;
}


int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    double l = 0, r = inf+10;
    while (r - l > eps) {
        double mid = (l+r)/2.;
        if (check(mid)) r = mid; else l = mid;
    }
    if (l >= inf) return cout << -1, 0;
    cout << fixed << setprecision(7) << l;
    return 0;
}