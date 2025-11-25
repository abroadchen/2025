//
// Created by Psy.C on 2025/11/25.
//
/*
*n: 图中顶点数
m: 图中边数
p: 模数
fa[N]: 并查集的父节点数组
cnt[N]: 每个连通分量的节点数
 *
 *初始化每个节点为自己所在集合的根节点
 *读入所有边，将相连的节点合并到同一集合中
 *统计每个连通分量包含的节点数
 *
 *Cayley公式推广：对于由c个连通分量组成的图，
 *每个分量大小为n₁,n₂,...,n_c，生成树数目为
 *n^(c-2) × n₁ × n₂ × ... × n_c
*当c=1（整个图连通）时，结果是各节点数的乘积
当c>1时，需要乘以n^(c-2)因子
 *
*时间复杂度：O(m × α(n))，其中α是阿克曼函数的反函数
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 101010;
int n, m, p, fa[N], cnt[N];

int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void join(int x, int y) { x = find(x); y = find(y);  fa[x] = y; }

int main() {
    fast;
    cin >> n >> m >> p;
    for (int i = 1; i < n + 1; ++i) fa[i] = i;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        join(u, v);
    }
    for (int i = 1; i < n + 1; ++i) ++cnt[find(i)];
    ll ans = 1; int c = 0;
    for (int i = 1; i < n + 1; ++i) if (cnt[i]) {
        ans = ans * cnt[i] % p;//累乘每个连通分量的大小
        ++c;
    }
    for (int i = 0; i < c - 2; ++i) ans = ans * n % p;//ans = ans × n^(c-2) % p
    if (c == 1) ans = 1 % p;//确保结果始终在模p的意义下
    cout << ans << '\n';
    return 0;
}