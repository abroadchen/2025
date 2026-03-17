//
// Created by Psy.C on 2026/3/17.
//
/**
终止条件：当p > m时，到达前半部分末尾
状态记录：将{x-z, x-y}作为key，{x, f}作为value存储
状态更新：如果已有相同key但新值更优，则更新
三种选择：
操作0：增加a[p], b[p]，不增加c[p]
操作1：增加a[p], c[p]，不增加b[p]
操作2：增加b[p], c[p]，不增加a[p]

终止条件：当p ≤ m时，到达后半部分开头
状态匹配：查找与前半部分互补的状态
答案更新：如果找到更好的组合，更新ans、p1、p2
三种选择：与DFS1类似的操作

ch[3][3] = {"LM", "LW", "MW"}：三种操作对应的输出
从p1恢复前半部分的选择序列
从p2恢复后半部分的选择序列
按照选择输出对应字符串

O(3^(n/2))，比暴力O(3^n)大大优化
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 30, inf = 0x3f3f3f3f;
struct node {
    int b, c;
    bool operator<(const node& o) const {
        return b < o.b || (b == o.b && c < o.c);
    }
};

int m, a[N], b[N], c[N];
map<node, node> mp;
void dfs(int p, int x, int y, int z, int f) {
    if (p > m) {
        node i = {x - z, x - y};
        if (mp.contains(i)) {
            if (mp[i].b < x)
                mp[i] = {x, f};
        } else mp[i] = {x, f};
        return;
    }
    dfs(p + 1, x + a[p], y + b[p], z, f*3);
    dfs(p + 1, x + a[p], y, z + c[p], f*3+1);
    dfs(p + 1, x, y + b[p], z + c[p], f*3+2);
}

int ans = -inf, p1, p2;
void dfs2(int p, int x, int y, int z, int f) {
    if (p <= m) {
        node i = {z - x, y - x};
        if (mp.contains(i)) {
            if (mp[i].b + x > ans) {
                ans = mp[i].b + x;
                p1 = mp[i].c; p2 = f;
            }
        }
        return;
    }
    dfs2(p - 1, x + a[p], y + b[p], z, f*3);
    dfs2(p - 1, x + a[p], y, z + c[p], f*3+1);
    dfs2(p - 1, x, y + b[p], z + c[p], f*3+2);
}

int num[N], n;
char ch[3][3] = {"LM", "LW", "MW"};
void out() {
    int cnt = 0;
    for (int i = 1; i <= m; p1/=3, ++i) num[++cnt] = p1%3;
    for (int i = cnt; i; --i) puts(ch[num[i]]);
    for (int i = m + 1; i <= n; p2/=3, ++i) puts(ch[p2%3]);
}


int main() {
    fast;
    cin >> n; m = n>>1;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> c[i];
    dfs(1, 0, 0, 0, 0); dfs2(n, 0, 0, 0, 0);
    if (ans == -inf) puts("Impossible"); else out();
    return 0;
}