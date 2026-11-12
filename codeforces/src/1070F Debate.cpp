//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
h[20] 是 20 个优先队列。每个元素是 pair<int,int>（t）。
cmp 自定义比较器：按 p.second（即 pair 的第二个值）从大到小排——因为 std 默认是大顶堆（p1 < p2 表示 p1 优先级更高），所以 p1.second < p2.second 返回真意味着second 更大的排前面。即每个堆顶都是该队列里 second 最大的。
t.first 是类别编号（代码中取 0、1、10、11 等），t.second 是权值/收益
l、r：某种左右两侧的累积计数；
sum：总共已选的物品数（或某种容量计数）；
ans：总收益（所有选中的 second 之和）
阶段一：先消耗类别 11
把类别 11 的全部物品无条件全部选中：每选一个，sum、r、l 各 +1。这说明类别 11 是"必选、且不影响平衡"的一类
阶段二：配对消耗类别 10 和类别 1
每次同时从类别 10 和类别 1 各取一个（h[10] 和 h[1] 都要非空）；
每轮 sum +2、r 和 l 各 +1；
循环条件是平衡约束：2*(l+1) >= sum+2 且 2*(r+1) >= sum+2，翻译过来是 2l >= sum 且 2r >= sum（两边 +2 抵消）。
→ 即要求始终满足 l、r 各不小于 sum 的一半。这像是在维持某种"左右两侧数量均衡（差值至少 ≥0）"的约束
阶段三：把类别 10 和 1 剩余的全部并入类别 0
把阶段二没选完的类别 10 和类别 1 的所有剩余项，全部转投到 h[0]，作为第三阶段的统一素材。
阶段四：消耗类别 0
每次从 h[0]（内部按权重从大到小）取一个，sum+1；
循环条件 2*l >= sum+1 且 2*r >= sum+1：即在保证 l、r 各不小于 (sum+1)/2 的情况下，尽量多取。
→ 由于此时 h[10]、h[1] 已空，l、r 不再增长，而 sum 每次 +1，所以这个平衡条件很快会被破坏（l 固定值，sum 越来越大直到超过 2l）。也就是说阶段四会一直取到平衡被打破为止——这是有明确上界的有限循环
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

struct cmp {
    bool operator()(const ii &p1, const ii &p2) const {
        return p1.second < p2.second;
    }
};
priority_queue<ii, vector<ii>, cmp> h[20];

int n;
ii t;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> t.first >> t.second; h[t.first].push(t); }
    ll ans = 0, l = 0, r = 0, sum = 0;
    while (!h[11].empty()) {
        ans += h[11].top().second; sum += 1ll; r += 1ll; l += 1ll;
        h[11].pop();
    }
    while (2*(l+1) >= sum+2 && 2*(r+1) >= sum+2 && !h[10].empty() && !h[1].empty()) {
        ans += h[10].top().second; ans += h[1].top().second;
        sum += 2ll; r += 1ll; l += 1ll;
        h[10].pop(); h[1].pop();
    }
    while (!h[10].empty()) { h[0].push(h[10].top()); h[10].pop(); }
    while (!h[1].empty()) { h[0].push(h[1].top()); h[1].pop(); }
    while (2ll*l >= sum+1 && 2ll*r >= sum+1 && !h[0].empty()) {
        ans += h[0].top().second; h[0].pop();
        sum++;
    }
    cout << ans << '\n';
    return 0;
}