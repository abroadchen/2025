//
// Created by Psy.C on 2026/1/31.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 4100
#define ii pair<int, int>
using namespace std;


int main() {
    fast;
    int x, k; cin >> x >> k;//x（目标值）和k（操作数）
    ii a[N];//存储区间信息
    for (int i = 1, op; i <= k; ++i) {
        cin >> op;
        if (op == 2) {
            cin >> a[i].first;//单点区间
            a[i].second = a[i].first;
        } else cin >> a[i].first >> a[i].second;
    }
    a[k+1].first = x;//second默认为0
    sort(a + 1, a + 1 + k);
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= k + 1; ++i) {
        //第i-1个区间末尾到第i个区间开头之间的空隙大小
        const int t = a[i].first - a[i-1].second - 1;
        ans1 += t/2+t%2;//(t+1)/2，表示在空隙中最多可以放置多少个不相邻的点
        ans2 += t;//累加所有空隙的总大小
    }
    cout << ans1 << ' ' << ans2;
    return 0;
}