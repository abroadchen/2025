//
// Created by Psy.C on 2026/9/2.
//
/**
什么是排列？
排列 p: 把 {1, 2, 3, 4, 5} 映射到 {3, 1, 2, 5, 4}
意思: 1→3, 2→1, 3→2, 4→5, 5→4
每个排列都可以唯一分解为若干 不相交的环 。
- 环的个数 cnt （通过 DFS 找）
- 值为 1 的 b[i] 的个数 （奇偶性）
从位置 x 出发，沿着排列的指向一直走，直到遇到已访问的位置。 走过的所有位置都标记为已访问 。
用 while 循环代替递归（更安全，不会爆栈）每次调用标记 一个环的所有节点

如果是偶数，需要额外一次操作来修正奇偶性。
- 对每个未访问的位置 i，做一次 DFS → 标记一个完整的环
- cnt = 排列中不相交环的总数
cnt == 1 不加 只有一个环，不需要额外操作
cnt != 1 + cnt 有 cnt 个环，需要 cnt 次操作
ans = (b 中 1 的个数是否为偶数 ? 1 : 0) + (环数 cnt，如果 cnt ≠ 1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

bool vis[N];
int p[N];
void dfs(int x) {
    while (!vis[x]) {
        vis[x] = true;
        x = p[x];
    }
}

int n, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    int cnt = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        if (b[i] == 1) cnt++;
    }
    if (cnt%2 == 0) ans++;
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        dfs(i);
        cnt++;
    }
    if (cnt != 1) ans += cnt;
    cout << ans << '\n';
    return 0;
}