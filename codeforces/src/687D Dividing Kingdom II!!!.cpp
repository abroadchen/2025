//
// Created by Psy.C on 2026/4/15.
//
/**
继承vector：bsi类继承自vector<T>
构造函数：使用vector的构造函数
+=操作符重载：支持单个元素添加和整个bsi对象合并

N：最大边数（1000005）
M：最大节点数（2005）
fa：并查集的父节点数组
dst：距离数组，用于判断二分图（异或值表示相对颜色）
路径压缩：递归查找根节点并压缩路径
距离更新：在路径压缩过程中更新相对距离（异或值）
相同根节点：如果已在同一连通分量，检查是否会形成奇环
合并操作：将v的根节点连接到u的根节点
返回值：2表示形成奇环，1表示成功合并，0表示已在同连通分量
w：边的权重
u, v：边的两个端点
flag：全局标志，表示是否发现奇环
merge函数：合并两个bsi容器，按权重降序排序
初始化：为每条边重置并查集状态
处理边：依次处理排序后的边，检查是否破坏二分图性质
ve：线段树数组，存储区间内的边集合
update函数：更新线段树节点，合并左右子树的边集合
ms：线段树的起始索引
区间查询：使用线段树区间查询，找到最小的破坏二分图性质的边的权重
标志检查：如果发现了奇环，返回最后一条造成冲突的边的权重

输入参数：n个节点，m条边，q个查询
线段树大小：计算合适的线段树大小
读入边信息：读取所有边的端点和权重
叶节点初始化：将每条边放到对应的线段树叶节点
建树：从底部向上构建线段树
处理查询：对每个查询区间[l,r]，查找该区间内最小的破坏二分图性质的边权重
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

template<typename T>
class bsi : public vector<T> {
public:
    using vector<T>::vector;
    bsi& operator+=(const T& val) {
        this->push_back(val);
        return *this;
    }
    bsi& operator+=(const bsi& o) {
        this->insert(this->end(), o.begin(), o.end());
        return *this;
    }
};

constexpr int N = 1e6+5, M = 2005;

int fa[M], dst[M];
int find(int x) {
    if (x != fa[x]) {
        int u = find(fa[x]);
        dst[x] ^= dst[fa[x]];
        return fa[x] = u;
    }
    return x;
}

int merge(int x, int y) {
    int u = find(x), v = find(y);
    if (u == v) {
        if (dst[x] == dst[y]) return 2;
        return 0;
    }
    fa[v] = u;
    dst[v] = dst[x]^dst[y]^1;
    return 1;
}

int w[N], u[N], v[N];
bool flag;
bsi<int> merge(const bsi<int>& l, const bsi<int>& r) {
    bsi<int> q, res;
    ranges::merge(l, r, back_inserter(q), [&](int x, int y) {
        return w[x] > w[y];
    });
    for (auto i : q) {
        fa[u[i]] = u[i], fa[v[i]] = v[i];
        dst[u[i]] = dst[v[i]] = 0;
    }
    for (auto i : q) {
        int t = merge(u[i], v[i]);
        if (t) res += i;
        if (t == 2) { flag = 1; break; }
    }
    return res;
}

vector<bsi<int>> ve;
void update(int now) { ve[now] = merge(ve[now<<1], ve[now<<1|1]); }

int ms;
int query(int l, int r) {
    bsi<int> res; flag = 0;
    for (l += ms-1, r += ms; l < r; l>>=1, r>>=1) {
        if (l&1) res = merge(res, ve[l++]);
        if (r&1) res = merge(ve[--r], res);
    }
    if (flag) return w[res.back()];
    return -1;
}

int n, m, q, mh;
int main() {
    fast;
    cin >> n >> m >> q;
    mh = ceil(log2(m)); ms = 1<<mh; ve = vector(ms*2, bsi<int>{});
    for (int i = 1; i <= m; ++i) cin >> u[i] >> v[i] >> w[i];
    for (int i = 1; i <= m; ++i) ve[i+ms-1] = bsi<int>({i});
    for (int i = ms-1; i >= 1; --i) update(i);
    for (int l, r; q--;) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}