//
// Created by Psy.C on 2025/12/15.
//
/*
*时间复杂度：O(n)
空间复杂度：O(n)
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define ii pair<int,int>
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int l = 1e9+1, r = 0, res = -1;//表示未找到
    ii p[N];//存储所有区间
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
        l = min(p[i].first, l);//更新全局最左端点l为当前所有左端点的最小值
        r = max(p[i].second, r);//更新全局最右端点r为当前所有右端点的最大值
    }
    for (int i = 0; i < n; ++i) {
        if (p[i].first == l && p[i].second == r) {
            res = i + 1;//从1开始计数
        }
    }
    cout << res << '\n';
    return 0;
}