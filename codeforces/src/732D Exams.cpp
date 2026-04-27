//
// Created by Psy.C on 2026/4/26.
//
/**
vis[N]: 访问标记数组
a[N]: 权重/价值数组
m: 特殊物品数量
d[N]: 物品序列数组
从位置x倒序遍历到1
统计不同物品的种类数量(cnt)和总权重(sum)
当遇到未访问过的物品d[i]时，标记访问、累加权重、计数器+1
当遇到已访问物品或无特殊物品时，如果sum > 0则减少1
返回true当且仅当收集了全部m种物品且权重和为0
找到满足条件的最左边位置（最小前缀长度）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;

int vis[N], a[N], m, d[N];
bool check(int x) {
    int cnt = 0, sum = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = x; i > 0; i--) {
        if (d[i] && !vis[d[i]]) {
            vis[d[i]] = 1;
            sum += a[d[i]];
            cnt++;
        } else if (sum) sum--;
    }
    if (cnt == m && !sum) return true;
    return false;
}

int n;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= m; ++i) cin >> a[i];
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r)>>1;
        if (check(mid)) { ans = mid; r = mid - 1; }
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}