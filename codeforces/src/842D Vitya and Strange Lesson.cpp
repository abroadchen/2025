//
// Created by Psy.C on 2026/9/27.
//
/**
M=18：数位宽度（处理 0-2^18-1，18 位二进制，从高位 17 到低位 0）。
tr[u][s]：Trie 节点 u 沿位 s（0/1）的孩子。
sz[u]：子树中元素个数。
insert：从最高位 M=18 递归到最低位 now==-1 停止，叶子 sz[u]=1。回溯时 sz[u] = sz[左]+sz[右] 更新。
因为集合铺满整个值域（0-2^M-1 每个恰好一个），所以任意深度 i 的子树大小必然是 2^i（一种特例情况
输入 x = nx（全局异或累积值）。
从最高位到最低位做最大异或贪心：
s = x 当前位。
我们希望异或结果该位为 1（即走与 s 相反的分支 s^1）。
关键判断：if (sz[tr[u][s]] == 1<<i)。
sz[tr[u][s]] 是"沿当前位 s 的分支子树元素个数"。
1<<i 是"在该深度 i 下，一个满子树应有的元素个数"（因为满集合中深度 i 的子树要么全满 2^i、要么为空 0）。
若 sz[tr[u][s]] == 1<<i：说明沿 s 分支是满的（元素全都在这边，s^1 分支为空）——所以必须走 s^1 分支（被迫反向），答案该位必为 1（res |= 1<<i）。
否则（sz[tr[u][s]] 为 0 或非满）：说明可以沿 s 分支走（存在元素），该位异或为 0，走 tr[u][s]。
if (!u) return res：走到空分支提前返回。
这里 == 1<<i 的分支判断利用了"值域铺满"性质：深度 i 处任一分支要么空要么满，绝不会"半满"，因此能只用 sz 快速判断该走哪边。这是相对普通 Trie 最大异或（用 exists 标记）的简化。
读入 n 个元素插入 Trie 建集合。
m 次操作：每次读入 x，更新全局累积异或 nx ^= x，然后输出 query(nx)。
输出的是：集合中能与当前 nx 得到最大异或值的结果（即 max_y { nx ^ y }，实际代码直接返回最大异或结果的数值）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5, M = 18;

int sz[N*(M+1)], tr[N*(M+1)][2], cnt(1);
void insert(int x, int u=1, int now=M) {
    if (now == -1) return sz[u]=1, void();
    int s = x>>now&1;
    if (!tr[u][s]) tr[u][s] = ++cnt;
    insert(x, tr[u][s], now-1);
    sz[u] = sz[tr[u][0]] + sz[tr[u][1]];
}

int nx;
inline int query(int x=nx) {
    int u = 1, res = 0;
    for (int i = M; i >= 0; --i) {
        int s = x>>i&1;
        if (sz[tr[u][s]] == 1<<i)
            u = tr[u][s^1], res |= 1<<i;
        else u = tr[u][s];
        if (!u) return res;
    }
    return res;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m, x;
int main() {
    fast;
    rd(n); rd(m);
    for (int i = 1; i <= n; ++i) rd(x), insert(x);
    while (m--) {
        rd(x); nx ^= x;
        cout << query() << '\n';
    }
    return 0;
}