//
// Created by Psy.C on 2026/9/6.
//
//f: 原始映射; g: 元素到组的映射; h: 组到目标的映射
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int f[N], g[N], h[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> f[i];
    for (int i = 1; i <= n; ++i) fa[i] = i;
    memset(g, -1, sizeof(g));//未定义
    memset(h, -1, sizeof(h));
    for (int i = 1; i <= n; ++i) {
        int x = find(i), y = find(f[i]);
        if (x != y) fa[x] = y;//合并根节点
        //同一个连通分量内的所有节点都能相互到达（直接或间接指向）
    }
    //遍历所有节点，为每个连通分量分配唯一的编号（从 1 开始递增）
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (g[find(i)] == -1)
            g[i] = g[find(i)] = ++cnt;//cnt 最终等于连通分量的数量，即组数m
        else g[i] = g[find(i)];//节点 i 所属的组编号
    }
    int flag = 1;
    for (int i = 1; i <= n; ++i) {
        if (h[g[i]] == -1) h[g[i]] = f[i];//第一次出现，记录目标
        else if (h[g[i]] != f[i]) { flag = 0; break; }//冲突，标记错误
    }
    if (!flag) cout << "-1\n";
    else {
        int m = 0;
        for (int i = 1; i <= n; ++i) m = max(m, g[i]);//确定总组数
        for (int i = 1; i <= m; ++i)
            if (g[h[i]] != i) { flag = 0; break; }//检查目标是否是有效组
        if (!flag) cout << "-1\n";
        else {
            cout << m << '\n';
            for (int i = 1; i <= n; ++i) {
                if (i == 1) cout << g[i];
                else cout << ' ' << g[i];
            }
            cout << '\n';
            for (int i = 1; i <= m; ++i) {
                if (i == 1) cout << h[i];
                else cout << ' ' << h[i];
            }
            cout << '\n';
        }
    }
    return 0;
}