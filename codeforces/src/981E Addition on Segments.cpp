//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
lz[]：线段树数组，每个结点是一个 vector<int>，用来收集完全覆盖该结点的若干区间操作里的权重 w。
线段树大小为 N<<2（4 倍）。
核心思想：把"给区间 [L,R] 增加权重 w"这样的操作，像 lazy 一样挂到线段树覆盖结点上，最后在 DFS 时把每个结点收集到的所有权重做一次"加入可选集合"的背包转移
标准线段树区间更新。
若当前结点区间 [l,r] 被更新区间 [L,R] 完全覆盖，就把权重 w 挂到该结点的 lz[rt]，直接返回（不再下钻）。
否则递归向左右子树继续（保证每个区间操作最多挂在 O(log n) 个结点上）
参数 w 是一个 bitset<N>，表示"当前到达该结点时，已可选权重能组成的和的集合"。
处理当前结点收集的权重：对 lz[rt] 里每个权重 w[i]，做背包"选或不选"转移：w |= w << lz[rt][i]（左移 = 加上这个权重）。
到达叶子结点 l==r 时，把当前可达集合并入全局 ans。
否则继续向左右子树递归（同一个 w 往下传递）。
含义：每个位置对应一条根到叶的路径，路径上所有挂载的权重都应当被考虑进"可选组合"，用 bitset 背包求所有可达和
读入 n（位置范围 1..n）、q 次操作，每次读入 l r w，调用 update(l,r,w,1,n,1)：给区间 [l,r] 挂上权重 w。
s[0]=1：初始可达集合只含 0（空集和 0）。
query(s,1,n,1)：从根开始 DFS，收集所有可达和。
统计 ans 中 1..n 中为 1 的位数 num，输出 num，再输出这些可达和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e4+5;

vector<int> lz[N<<2];
void update(int L, int R, int w, int l, int r, int rt) {
    if (L <= l && r <= R) { lz[rt].push_back(w); return; }
    int m = (l+r)>>1;
    if (L <= m) update(L, R, w, l, m, rt<<1);
    if (R > m) update(L, R, w, m+1, r, rt<<1|1);
}

bitset<N> ans;
void query(bitset<N> w, int l, int r, int rt) {
    for (int i = lz[rt].size()-1; i >= 0; i--)
        w |= w<<lz[rt][i];
    if (l == r) { ans |= w; return; }
    int m = (l+r)>>1;
    query(w, l, m, rt<<1); query(w, m+1, r, rt<<1|1);
}

int n, q;
bitset<N> s;
int main() {
    fast;
    cin >> n >> q;
    for (int i = 0, l, r, w; i < q; i++) {
        cin >> l >> r >> w;
        update(l, r, w, 1, n, 1);
    }
    s[0] = 1; query(s, 1, n, 1);
    int num = 0;
    for (int i = 1; i <= n; i++) if (ans[i]) num++;
    cout << num << '\n';
    for (int i = 1; i <= n; i++) if (ans[i]) cout << i << ' ';
    return 0;
}