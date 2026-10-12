//
// Created by Psy.C on 2026/10/12.
//
/**
r：当前"剩余容量/剩余预算"。
x：还需装（或还需消耗）x 个 A 类物品。
y：还需装 y 个 B 类物品。
ret：累计消耗的"天数 / 次数 / 代价"
dfs(r-a, x-1, y, ret)：当前这一轮/这一列内连续消费 a，消耗 1 个 A。
dfs(n-a, x-1, y, ret+1)：重新从满容量 n 开始，消费 a，消耗 1 个 A，代价 +1。
dfs(r-b, x, y-1, ret)：连续消费 b，消耗 1 个 B。
dfs(n-b, x, y-1, ret+1)：重置后消费 b，消耗 1 个 B，代价 +1。
终止条件：x==0 && y==0 时所有 A、B 都消费完，用当前 ret 更新全局 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int inf = 0x3f3f3f3f;

int ans(inf), n, a, b;
void dfs(int r, int x, int y, int ret) {
    if (x < 0 || y < 0) return;
    if (r < 0) return;
    if (x == 0 && y == 0) { ans = min(ans, ret); return; }
    dfs(r-a, x-1, y, ret); dfs(n-a, x-1, y, ret+1);
    dfs(r-b, x, y-1, ret); dfs(n-b, x, y-1, ret+1);
}


signed main() {
    fast;
    cin >> n >> a >> b; dfs(n, 4, 2, 1);
    cout << ans << '\n';
    return 0;
}