//
// Created by Psy.C on 2026/9/20.
//
/**
cmp 比较 a.v * b.w > b.v * a.w，等价于比较 a.v / a.w > b.v / b.w（交叉相乘避免浮点误差）。
即按性价比（价值/重量）从高到低排序
(a) sum 的更新：

sum 表示"处理到当前物品 i 时，可能达到的最大背包容量"，即把所有已处理的物品全放进容量也封顶 m：min(已处理物品总重, m)。
这作为遍历上界，避免每次都遍历到 m（省时间）。
(b) 下界 max(v[i].w, sum-4)：

循环从 sum 倒着到 max(v[i].w, sum-4)，也就是只更新容量在 [sum-4, sum] 这一小窗内的 dp。
这是该题的精妙近似：因为物品按性价比排好序，最优解往往集中在容量接近 sum（接近装满）的位置，所以只更新最靠近装满的 4 个容量档位即可，大幅减少计算量。
常数 4 是调出来的参数（经验值，控制精度与速度的平衡）。
(c) 转移（01背包）：

dp[j] = max(dp[j], dp[j-w]+v)：标准 01 背包一维滚动数组，倒序遍历保证每个物品只用一次。
遍历所有容量 1..m，取 dp 最大值作为答案（因为不一定装满最优）。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

struct node {
    ll w, v;
    node() = default;
    node(ll w, ll v) : w(w), v(v) {}
};
bool cmp(node a, node b) {
    return a.v*b.w > b.v*a.w;
}

int n, m;
vector<node> v;
ll dp[3*N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, a, b; i <= n; ++i) {
        cin >> a >> b;
        v.emplace_back(a, b);
    }
    ranges::sort(v, cmp);
    ll len = v.size(), sum = 0;
    for (int i = 0; i < len; ++i) {
        sum = sum+v[i].w < m ? sum+v[i].w : m;
        for (ll j = sum; j >= max(v[i].w, sum-4); --j)
            dp[j] = max(dp[j], dp[j-v[i].w]+v[i].v);
    }
    ll ans = 0;
    for (int i = 1; i <= m; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
    return 0;
}