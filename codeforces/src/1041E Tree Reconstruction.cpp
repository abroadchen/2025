//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
a[]：最后要输出的边（答案）。
q[]：一组"关键点"序列。
num[]：与 q 配套的计数值
读 n-1 条边（恰好一棵树的边数）。
t1 判断：
若出现 x==y（自环）→ t1=0。
若出现一条边两端都不是 n → t1=0。
若 t1 保持为 1，说明所有边都至少有一端是 n（即 n 是"万能中心"，每条边都连到 n）。
q[i]：每条边除了 n 之外的那一端（若 x=n 则记 y，否则记 x）。
t2：是否有边涉及节点 n-1
若不是"每条边都含 n" 或 "没有边含 n-1"，直接判 NO。
将 q[1..n-1]（每条边除 n 外的端点）‍升序排序。
去重：q[1..tl] 是不重复的关键点，num[tl] 记录每个点出现的次数。
同时把这些点标记 vis 为已用
q[tl+1] = n：在序列末尾补上 n。
now：从节点 1 开始，找最小的未使用节点。
tot：已构造的边数。
对每个关键点 q[i]（它有 num[i] 条边连到 n）：

先把 num[i]-1 条边用作内部"链式"扩展：
找一个未用节点 now。
若 now > q[i] → NO（因为要求现在内部挂的节点必须 ≤ q[i]）。
构造边 (lst, now) 并更新 lst=now，重复直到 num[i]-1 用完。
剩下的那条边连接到 q[i+1]（下一个关键点）或当前 now，构造出一条"桥"。
构造出的边都存入 a[]，tot 增加。
只有构造出的边数等于 n-1 才算合法（否则 NO）。
合法则输出 YES 和构造出的所有边
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1010;

struct node { int x, y; } a[N];

int n, q[N], tl, num[N];
bool vis[N];
int main() {
    fast;
    cin >> n;
    bool t1 = 1, t2 = 0;
    rep(i,n-1) {
        int x, y; cin >> x >> y;
        if (x == y) t1 = 0;
        if (x == n) q[i] = y; else q[i] = x;
        if (x != n && y != n) t1 = 0;
        if (x == n-1 || y == n-1) t2 = 1;
    }
    if (t1 == 0 || t2 == 0) { cout << "NO\n"; return 0; }
    sort(q+1, q+n); q[0] = tl = 0;
    for (int i = 1, j = 1; i < n; i = j) {
        q[++tl] = q[i]; vis[q[i]] = 1;
        for (j = i+1; j <= n && q[i] == q[j]; j++) {}
        num[tl] = j - i;
    }
    q[tl+1] = n;
    int now = 1, tot = 0;
    rep(i,tl) {
        int lst = q[i], y = num[i] - 1;
        while (num[i]-1) {
            while (vis[now] && now <= n) now++;
            vis[now] = 1;
            if (now > q[i]) { cout << "NO\n"; return 0; }
            a[++tot] = {lst, now};
            lst = now; num[i]--;
        }
        if (!y) a[++tot] = {q[i+1], q[i]};
        else a[++tot] = {q[i+1], now};
    }
    if (tot != n-1) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    rep(i,tot) cout << a[i].x << ' ' << a[i].y << '\n';
    return 0;
}