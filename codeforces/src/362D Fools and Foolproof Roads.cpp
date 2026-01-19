//
// Created by Psy.C on 2026/1/19.
//
/**
* sz[N]：每个连通分量的大小/权值
tot：当前连通分量总数
merge函数：合并两个节点x和y，权值增量为z
如果在同一集合：直接增加权值
如果在不同集合：合并集合，更新总数tot
 *
 *x表示节点编号，sz表示大小
 *实现最小堆（因为优先队列默认是最大堆，sz > o.sz使其变为最小堆
 *
 *n（节点数）、m（边数）、p（额外边数）、q（目标连通分量数）
 *
*tot - p > q：如果现有连通分量减去p条边仍大于q，不可能达到目标
tot < q：如果现有连通分量小于目标，不可能
(!m && !(q - n) && p)：如果没有输入边但需要p>0且q=n，矛盾
如果m=0（无边），且q=n（要求n个连通分量），那么图已经自然分成n个连通分量（每个节点独立），
此时如果还要添加边（p>0），就会减少连通分量数量，违背q=n的要求
 *
*当连通分量数大于目标时继续合并
取出两个最小的连通分量
减少p和tot（使用了一条边，减少一个连通分量）
输出合并的两个节点
合并并查集
更新权值：sz[t1.x] += min(inf, t1.sz + t2.sz + 1) + t2.sz
将合并后的结果重新放入队列
 *
*找到一个不是根节点的节点（用于添加额外边）
输出p条额外边，连接该节点与其父节点
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define inf 1000000000ll
using namespace std;

ll fa[N];
ll find(const ll x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

ll sz[N], tot;
void merge(ll x, ll y, const ll z) {
    x = find(x); y = find(y);
    if (x == y) sz[x] += z; else {
        fa[x] = y;
        sz[y] += z + sz[x];
        tot--;
    }
}

struct node {
    ll x, sz;
    bool operator<(const node o) const {
        return sz > o.sz;
    }
} t1, t2;


int main() {
    fast;
    ll n, m, p, q; cin >> n >> m >> p >> q; tot = n;
    for (ll i = 1; i <= n; ++i) fa[i] = i;
    for (ll i = 1, x, y, z; i <= m; ++i) {
        cin >> x >> y >> z;
        merge(x, y, z);
    }
    if (tot - p > q || tot < q || (!m && !(q - n) && p)) return cout << "NO\n", 0;
    cout << "YES\n";
    priority_queue<node> Q;
    for (int i = 1; i <= n; ++i) if (find(i) == i) {
        Q.push({i, sz[fa[i]]});
    }
    while (tot > q) {
        t1 = Q.top(); Q.pop();
        t2 = Q.top(); Q.pop();
        p--; tot--;
        cout << t1.x << ' ' << t2.x << '\n';
        fa[t2.x] = t1.x;
        sz[t1.x] += min(inf, t1.sz + t2.sz + 1) + t2.sz;
        Q.push({t1.x, sz[t1.x]});
    }
    for (tot = 1; tot <= n; ++tot) if (find(tot) != tot) break;
    while (p--) cout << tot << ' ' << fa[tot] << '\n';
    return 0;
}