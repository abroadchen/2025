//
// Created by Psy.C on 2026/10/8.
//
/**
标准的 01 字典树，son[bit][node] 表示从 node 沿 bit（0 或 1）走到的子节点。
每个数从第 30 位到第 0 位逐位插入，构建一个二进制 Trie（每个数对应一条从根到叶子的路径）
这个函数递归计算两个 Trie 子树（r1、r2）之间的最小异或值（针对第 b 位）。
优先走相同位（0-0 或 1-1），因为这不会产生该位贡献，取两者中较小者；
若没有相同位的路径，才走不同位（0-1 或 1-0），此时贡献 1<<b，同样取较小者。
本质是在求"两个集合各取一个数，其异或值最小是多少"，这是 01-Trie 求最小异或对的标准分治写法
递归遍历整棵 01-Trie。
当某节点同时有 0、1 两个分支时，说明第 b 位上存在不同的数——此时把"0 子树与 1 子树之间的最小异或"dfs(son[0], son[1], b-1) 加上 1<<b 累加进 ans。
然后分别递归 0 分支与 1 分支，继续向下处理
读入
n
n 个数插入 Trie，从根 dfs(0, M) 遍历统计，输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5, M = 30;

struct Trie {
    int son[2][N*M+10], tot;
    void insert(int a) {
        int now = 0, id;
        for (int i = M; i >= 0; --i) {
            id = (a>>i)&1;
            if (!son[id][now]) son[id][now] = ++tot;
            now = son[id][now];
        }
    }

    int dfs(int r1, int r2, int b) {
        if (b < 0) return 0;
        int a1 = -1, a2 = -1;
        if (son[0][r1] && son[0][r2]) a1 = dfs(son[0][r1], son[0][r2], b-1);
        if (son[1][r1] && son[1][r2]) a2 = dfs(son[1][r1], son[1][r2], b-1);
        if (~a1 && ~a2) return min(a1, a2);
        if (~a1) return a1;
        if (~a2) return a2;
        if (son[1][r1] && son[0][r2]) a1 = dfs(son[1][r1], son[0][r2], b-1) + (1<<b);
        if (son[0][r1] && son[1][r2]) a2 = dfs(son[0][r1], son[1][r2], b-1) + (1<<b);
        if (~a1 && ~a2) return min(a1, a2);
        if (~a1) return a1;
        if (~a2) return a2;
    }
} T;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll ans;
void dfs(int a, int b) {
    if (b < 0) return;
    if (T.son[0][a] && T.son[1][a]) ans += 1ll*T.dfs(T.son[0][a], T.son[1][a], b-1) + (1ll<<b);
    if (T.son[0][a]) dfs(T.son[0][a], b-1);
    if (T.son[1][a]) dfs(T.son[1][a], b-1);
}

int main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) T.insert(rd());
    dfs(0, M);
    cout << ans << '\n';
    return 0;
}