//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
m：物品种类数（编号 1..m），n：购买事件数。
t[x]：统计每个种类的当前持有数量（或"还需凑齐进度"）。
cnt：当前已凑齐的种类数。
每次买入一个 x，若该种从 0→1 则 cnt++；一旦 cnt==m（全部凑齐），就“消费”掉每类各 1 件（即把所有 t 减 1，把因此掉到 0 的种类 cnt--），并输出 1，否则输出 0
每次读一个购买物品编号 x，t[x]++。
若它恰好变成 1（第一次出现该种），说明多了一种类，cnt++。
当 cnt == m，说明从某刻起所有 m 种都有至少 1 件库存，满足一次"任务/结算"。
此时对全部 m 类各减 1（消费掉本轮各 1 件），并把因此变 0 的种类从 cnt 里减去。
输出 1 表示本轮凑齐并结算；否则输出 0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int m, n, x, t[N], cnt;
int main() {
    fast;
    cin >> m >> n;
    rep(i,n) {
        cin >> x; t[x]++;
        if (t[x] == 1) cnt++;
        if (cnt == m) {
            rep(j,m) {
                t[j]--;
                if (!t[j]) cnt--;
            }
            cout << "1";
        } else cout << "0";
    }
    return 0;
}