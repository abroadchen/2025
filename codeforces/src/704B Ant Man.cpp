//
// Created by Psy.C on 2026/4/19.
//
/**
n: 节点数量
s, e: 起点和终点
t[N]: 链表数组，t[i]表示节点i的下一个节点
ans: 总代价

初始路径：直接从s到e
t[s] = e: s的下一个节点是e
遍历待插入节点:
对除起点终点外的每个节点i
j = s; j != e; j = t[j]: 遍历当前路径上的所有相邻节点对(j, t[j])
get(j, i)+get(i, t[j])-get(j, t[j]): 插入i后节省的代价
get(j, i) + get(i, t[j]): j→i→t[j]的代价
-get(j, t[j]): 减去原来的j→t[j]代价
找到使总代价增加最少（或节省最多）的插入位置

t[i] = t[o.second]: i的下一节点是原o.second的下一节点
t[o.second] = i: o.second的下一节点是i
ans += o.first: 更新总代价
O(n³): 外层循环n次，内层循环遍历路径（最坏O(n)），每次计算O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define li pair<ll, int>
using namespace std;
constexpr int N = 5e3+5;
constexpr ll inf = 1e18;
ll x[N], d[N], a[N], c[N], b[N];
ll get(int i, int j) {
    return i < j ? x[j] - x[i] + d[i] + a[j] : x[i] - x[j] + c[i] + b[j];
}

int n, s, e, t[N];
ll ans;
int main() {
    fast;
    cin >> n >> s >> e;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    ans = get(s, e); t[s] = e;
    for (int i = 1; i <= n; ++i)
        if (i != s && i != e) {
            li o = {inf, 0};
            for (int j = s; j != e; j = t[j])
                o = min(o, {get(j, i)+get(i, t[j])-get(j, t[j]), j});
            t[i] = t[o.second], t[o.second] = i, ans += o.first;
        }
    cout << ans << '\n';
    return 0;
}