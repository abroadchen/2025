//
// Created by Psy.C on 2026/3/10.
//
/**
键为位置索引，值为访问距离
pos: 当前位置索引
lst: 剩余跳跃距离
flag: 方向标志（1表示向右，0表示向左）
dis: 总跳跃距离
如果已访问过，计算循环周期并更新剩余距离

向右跳跃 (flag = 1):
寻找最右边且不超过 a[pos].p + lst 的点
如果找不到向右的点，尝试向左跳跃
递归到下一个位置，更新剩余距离和方向
向左跳跃 (flag = 0):
寻找最左边且不低于 a[pos].p - lst 的点
如果找不到向左的点，尝试向右跳跃
递归到下一个位置，更新剩余距离和方向

b数组：将原始ID映射到排序后的索引
从原始ID x开始，以距离y向右跳跃
输出最终停靠点的原始ID

预处理：O(n log n)
每次查询：O(log n × 平均跳跃步数)
总体：O(n log n + m × 平均步数 × log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

struct node {
    int p, id;
    bool operator<(const node &o) const {
        return p < o.p;
    }
} a[N];

map<int, int> vis;
int n;
int dfs(int pos, int lst, int flag, int dis) {
    if (vis[pos]) {
        int x = dis - vis[pos]; lst %= x;
        vis[pos] = dis;
    }
    vis[pos] = dis;
    if (flag) {
        int x = upper_bound(a + 1, a + n + 1, node{a[pos].p+lst, 0}) - a - 1;
        if (x == pos) {
            x = lower_bound(a + 1, a + n + 1, node{a[pos].p-lst, 0}) - a;
            if (x == pos) return pos;
            return dfs(x, lst-(a[pos].p-a[x].p), 1, dis+(a[pos].p-a[x].p));
        }
        return dfs(x, lst-(a[x].p-a[pos].p), 0, dis+(a[x].p-a[pos].p));
    }
    int x = lower_bound(a + 1, a + n + 1, node{a[pos].p-lst, 0}) - a;
    if (x == pos) {
        x = upper_bound(a + 1, a + n + 1, node{a[pos].p+lst, 0}) - a - 1;
        if (x == pos) return pos;
        return dfs(x, lst-(a[x].p-a[pos].p), 0, dis+(a[x].p-a[pos].p));
    }
    return dfs(x, lst-(a[pos].p-a[x].p), 1, dis+(a[pos].p-a[x].p));
}

int m, b[N];
int main() {
    fast;
    cin>>n>>m;
    for (int i = 1; i <= n; ++i) { cin >> a[i].p; a[i].id = i; }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) b[a[i].id] = i;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y; vis.clear();
        cout << a[dfs(b[x], y, 1, 0)].id << '\n';
    }
    return 0;
}