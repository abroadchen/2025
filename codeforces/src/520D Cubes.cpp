//
// Created by Psy.C on 2026/3/1.
//
/**
获取候选点（最小或最大索引）
验证该点是否仍满足条件
如果满足条件，更新答案，删除该点，添加受影响的邻近点
如果不满足条件，直接删除该点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1, mod = 1e9+9;

int x[N], y[N];///各个点的x和y坐标
map<ii, int> mp;///将坐标对映射到其在数组中的索引
///当前点上方三个相邻位置的点是否存在，并验证相应的邻居点是否存在
bool ok(const int t) {
    int X = x[t] + 1, Y = y[t] + 1;
    if (mp.contains({X, Y})) {
        if (!mp.contains({X, Y-1}) && !mp.contains({X+1, Y-1}))
            return false;
    }
    X = x[t], Y = y[t] + 1;
    if (mp.contains({X, Y})) {
        if (!mp.contains({X-1, Y-1}) && !mp.contains({X+1, Y-1}))
            return false;
    }
    X = x[t] - 1, Y = y[t] + 1;
    if (mp.contains({X, Y})) {
        if (!mp.contains({X-1, Y-1}) && !mp.contains({X, Y-1}))
            return false;
    }
    return true;
}

set<int> g;///当前可处理的点的索引
///被删除点下方三个位置的点，如果存在且满足条件就加入活跃集合
void add(const int t) {
    int X = x[t] - 1, Y = y[t] - 1;
    if (mp.contains({X, Y})) {
        if (const int u = mp[{X, Y}]; ok(u)) g.insert(u);
    }
    X = x[t], Y = y[t] - 1;
    if (mp.contains({X, Y})) {
        if (const int u = mp[{X, Y}]; ok(u)) g.insert(u);
    }
    X = x[t] + 1, Y = y[t] - 1;
    if (mp.contains({X, Y})) {
        if (const int u = mp[{X, Y}]; ok(u)) g.insert(u);
    }
}

int n;
ll ans;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        mp[{x[i], y[i]}] = i;//将坐标映射到对应的索引
    }
    for (int i = 0; i < n; ++i)
        if (ok(i)) g.insert(i);//将所有满足条件的点加入活跃集合
    for (int i = 0; i < n; ++i) {
        if (i&1) {//奇数轮：从小到大处理
            while (!g.empty()) {
                int t = *g.begin();
                if (ok(t)) {
                    ans = (ans*n%mod+t)%mod;
                    g.erase(t);
                    mp.erase({x[t], y[t]});
                    add(t);
                    break;
                }
                g.erase(t);
            }
        } else {//偶数轮：从大到小处理
            while (!g.empty()) {
                int t = *g.rbegin();
                if (ok(t)) {
                    ans = (ans*n%mod+t)%mod;
                    g.erase(t);
                    mp.erase({x[t], y[t]});
                    add(t);
                    break;
                }
                g.erase(t);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}