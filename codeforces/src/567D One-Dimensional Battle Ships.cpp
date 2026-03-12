//
// Created by Psy.C on 2026/3/12.
//
/**
x表示位置，id表示原始序号
m-障碍物数量，a-参数，n-总长度，k-需要放置的数量
判断前mid个障碍物是否能满足条件；cnt记录可放置数量，l记录上一个已考虑的位置

遍历所有障碍物，如果当前障碍物的原始序号小于等于mid，则计算在当前位置之前最多可放置多少个物品，
公式为(当前位置-上次位置)/(a+1)，然后更新l为当前位置
计算从最后一个考虑的障碍物位置到终点n之间还能放置多少个物品
如果可放置数量小于要求的数量k，返回true，否则返回false

如果check(mid)为真，说明当前mid满足条件，更新答案并继续在左半区间查找；否则在右半区间查找
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

struct node { int x, id; } d[N];

int m, a, n, k;
bool check(int mid) {
    int cnt = 0, l = 0;
    for (int i = 1; i <= m; ++i)
        if (d[i].id <= mid) {
            cnt += (d[i].x - l) / (a + 1);
            l = d[i].x;
        }
    cnt += (n - l + 1) / (a + 1);
    return cnt < k;
}


int main() {
    fast;
    cin >> n >> k >> a >> m;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x; d[i] = {x, i};
    }
    sort(d + 1, d + 1 + m, [](node x, node y) {
        return x.x < y.x;
    });
    int l = 1, r = m, ans = -1;
    while (l <= r) {
        if (int mid = (l + r) >> 1; check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}