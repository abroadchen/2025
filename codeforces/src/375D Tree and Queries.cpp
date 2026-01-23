//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define inf 1e5
#define ii pair<int, int>
using namespace std;

struct sgt {
#define mid ((l+r)>>1)
    int sum[N<<2];
    //更新线段树中位置p的值，增加x
    void update(const int id, const int l, const int r, const int p, const int x) {
        if (l == r) { sum[id] += x; return; }
        if (p <= mid) update(id<<1, l, mid, p, x);
        else update(id<<1|1, mid+1, r, p, x);
        sum[id] = sum[id<<1] + sum[id<<1|1];
    }
    //查询区间[L,R]内的和
    int query(const int id, const int l, const int r, const int L, const int R) {
        if (L <= l && r <= R) return sum[id];
        int res = 0;
        if (L <= mid) res += query(id<<1, l, mid, L, R);
        if (R > mid) res += query(id<<1|1, mid+1, r, L, R);
        return res;
    }
#undef mid
} tr;

int siz[N], son[N];//每个节点的子树大小 重儿子
vector<int> g[N];
void dfs(const int u, const int fa) {
    siz[u] = 1;//当前节点大小为1
    for (const int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;//更新重儿子
    }
}

int cnt[N], clr[N], Son;//每种颜色的数量 每个节点的颜色 当前处理的重儿子
void dfs2(const int u, const int fa, const int val) {//更新节点u的颜色计数
    tr.update(1, 0, inf, cnt[clr[u]], -1);//先删除原来的计数
    cnt[clr[u]] += val;//更新计数值
    tr.update(1, 0, inf, cnt[clr[u]], 1);//添加新的计数
    for (const int v : g[u]) if (v != fa && v != Son) dfs2(v, u, val);//递归处理轻儿子
}

vector<ii> a[N];//询问编号, 颜色数量
int ans[N];
void dfs3(const int u, const int fa, const bool keep) {
    for (const int v : g[u]) {//先处理所有轻儿子，不清空它们的贡献
        if (v == fa || v == son[u]) continue;
        dfs3(v, u, false);
    }
    if (son[u]) dfs3(son[u], u, true), Son = son[u];//处理重儿子，保留它的贡献
    dfs2(u, fa, 1);//处理当前节点的贡献
    for (auto [fst, snd] : a[u])//回答在当前节点的询问
        ans[fst] = tr.query(1, 0, inf, snd, inf);
    if (!keep) Son = 0, dfs2(u, fa, -1);//如果不需要保留当前节点的贡献，则清空它
}


int main() {
    fast;
    int n, m; cin >> n >> m;//节点数n和询问数m
    for (int i = 1; i <= n; ++i) cin >> clr[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    for (int i = 1, u, k; i <= m; ++i) {//读取询问并存储到对应节点
        cin >> u >> k;
        a[u].emplace_back(i, k);
    }
    dfs(1, 0);//计算重儿子
    tr.update(1, 0, inf, 0, inf);//初始化线段树
    dfs3(1, 0, true);//启发式合并DFS
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';//输出所有询问的结果
    return 0;
}