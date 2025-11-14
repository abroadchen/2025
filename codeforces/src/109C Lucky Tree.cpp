//
// Created by Psy.C on 2025/11/13.
//
/*
*f数组用于并查集的父节点存储
s数组用于存储每个集合的大小
 *
*计算该连通分量对答案的贡献：
s[i]：该连通分量的节点数
(n - s[i])：其他节点数
(n - s[i] - 1)：其他节点数减1
这部分计算的是与幸运数字相关的三元组数量
 */
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 111111;
int n, f[N], s[N];

bool check(int c) {
    for (; c > 0; c /= 10) if (c % 10 != 4 && c % 10 != 7) return 1;
    return 0;
}
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) f[i] = i, s[i] = 1;//每个集合大小为1
    for (int i = 0, u, v, c; i < n - 1; ++i) {
        cin >> u >> v >> c;
        if (check(c)) {
            u = find(u); v = find(v);
            f[u] = f[v];//将u所在集合合并到v所在集合（u的根节点指向v的根节点）
            s[v] += s[u];//更新v所在集合的大小，加上u所在集合的大小
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) if (f[i] == i) {
        ans += 1ll * s[i] * (n - s[i]) * (n - s[i] - 1);
    }
    cout << ans;
    return 0;
}