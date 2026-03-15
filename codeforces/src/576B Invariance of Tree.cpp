//
// Created by Psy.C on 2026/3/15.
//
/**
存储排列，a[i]表示从节点i指向的节点

输出以x为中心的星型连接
将x与所有其他节点相连
适用于x指向自己的情况（自环）
输出x和y之间的连接
遍历所有未访问节点
在环中交替连接到x和y（通过op ^= 1实现交替）
p = a[p]：沿着排列的指向关系遍历环
检查所有环的长度是否为偶数
如果存在奇数长度的环，输出"NO"并退出
因为在奇数长度环中无法完美配对

如果存在自环（a[i] == i），则以i为中心输出星型结构
查找长度为2的环（相互指向的两个节点）
如果找到，调用get函数处理其余节点
如果既没有自环，也没有长度为2的环，则无解
O(n)：每个节点最多被访问几次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int n;
void out(int x) {
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        if (x == i) continue;
        cout << x << ' ' << i << '\n';
    }
}

int vis[N], a[N];
void out(int x, int y) {
    cout << "YES\n";
    cout << x << ' ' << y << '\n';
    for (int i = 1, op = 0; i <= n; ++i) {
        if (vis[i] == 1) continue;
        int p = i;
        while (vis[p] == 0) {
            vis[p] = 1;
            if (op == 0) cout << x << ' ' << p << '\n';
            else cout << y << ' ' << p << '\n';
            op ^= 1;
            p = a[p];
        }
    }
}

void get(int x, int y) {
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 1) continue;
        int p = i, cnt = 0;
        while (vis[p] == 0) {
            vis[p] = 1;
            p = a[p];
            cnt++;
        }
        if (cnt&1) { cout << "NO\n"; exit(0); }
    }
    memset(vis, 0, sizeof(vis));
    vis[x] = vis[y] = 1;
    out(x, y);
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == i) { out(i); return 0; }
    }
    for (int i = 1; i <= n; ++i) {
        if (a[a[i]] == i) {
            vis[i] = vis[a[i]] = 1;
            get(i, a[i]);
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}