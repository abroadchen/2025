/**
*l, r：原始区间的左右边界
nl, nr：离散化后区间的左右边界
ind：存储与该区间相关的查询索引
*pos：点的位置
fr：该点属于哪个区间
type：false表示左端点，true表示右端点
*ta：区间数量计数器
tb：端点数量计数器
 *
*fa[N]：并查集父节点数组
l[N], r[N]：每个连通分量的左右边界
init()：初始化并查集，每个区间独立
find()：查找根节点，带路径压缩
unite()：合并两个集合，同时更新边界信息
 *
 *线段树节点结构，每个节点存储区间范围和该区间内包含的区间索引
*更新线段树，将位置pos的区间与ind合并
遍历当前节点的区间列表，与ind进行合并操作
递归更新到叶子节点
*在线段树区间[l,r]中插入区间ind
如果当前节点完全在目标区间内，直接添加
否则递归插入到左右子树
 *
*q[N]：存储查询
tq：查询计数器
读入操作：操作1是添加区间，操作2是添加查询
*对所有端点排序进行离散化
为每个位置分配离散化后的编号
更新区间的离散化边界
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 100048
using namespace std;

struct interval {
    int l{}, r{}, nl{}, nr{};
    vector<int> ind;
} a[N];
struct point {
    int pos, fr; bool type;
    bool operator<(const point& x) const { return pos < x.pos; }
} b[N<<1];

int ta, tb;
namespace dsu {
    int fa[N], l[N], r[N];
    void init() {//每个集合的边界为对应区间的离散化边界
        for (int i = 1; i <= ta; ++i) fa[i] = i, l[i] = a[i].nl, r[i] = a[i].nr;
    }
    int find(const int x) {
        if (fa[x] != x) fa[x] = find(fa[x]);//递归查找其父节点的根节点 直接将x连接到根节点
        return fa[x];
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);//各自的根节点
        fa[x] = y;
        l[y] = min(l[y], l[x]); r[y] = max(r[y], r[x]);
    }
}

namespace sgt {
    struct node {
        int l{}, r{}; vector<int> v;
    } tr[N<<2];
    void build(const int cur, const int l, const int r) {
        tr[cur].l = l; tr[cur].r = r; tr[cur].v.clear();
        if (l != r) {
            const int mid = (l + r) >> 1;
            build(cur<<1, l, mid); build(cur<<1|1, mid+1, r);
        }
    }
    void update(const int cur, const int pos, const int ind) {
        for (const int i : tr[cur].v) dsu::unite(i, ind);//遍历当前节点存储的所有区间，与新区间ind进行合并
        tr[cur].v.clear();//清空当前节点的区间列表
        if (tr[cur].l == tr[cur].r) return;
        if (const int mid = (tr[cur].l + tr[cur].r) >> 1; pos <= mid) update(cur<<1, pos, ind);
        else update(cur<<1|1, pos, ind);
    }
    void insert(const int cur, const int l, const int r, const int ind) {
        if (l > tr[cur].r || r < tr[cur].l) return;
        if (l <= tr[cur].l && tr[cur].r <= r) { tr[cur].v.push_back(ind); return; }
        insert(cur<<1, l, r, ind); insert(cur<<1|1, l, r, ind);
    }
}

pair<int, int> q[N];
int tq, ind;
int main() {
    fast;
    int n; cin>>n;
    for (int i = 1, op; i <= n; ++i) {
        cin>>op;
        if (op == 1) {
            ++ta; cin >> a[ta].l >> a[ta].r;
            b[++tb] = {a[ta].l, ta, false};//将左端点添加到端点数组
            b[++tb] = {a[ta].r, ta, true};//将右端点添加到端点数组
        } else {
            cin >> q[++tq].first >> q[tq].second;//读入查询的两个区间索引
            a[ta].ind.push_back(tq);//将查询索引添加到当前区间的相关查询列表
        }
    }
    sort(b + 1, b + tb + 1); ind = 0;//初始化离散化索引
    for (int i = 1; i <= tb; ++i) {
        if (i == 1 || b[i].pos != b[i-1].pos) ind++;//当前位置与前一个位置不同（或第一个位置）
        if (!b[i].type) a[b[i].fr].nl = ind; else a[b[i].fr].nr = ind;//更新对应区间的离散化边界
    }
    dsu::init();
    sgt::build(1, 1, ind);
    for (int i = 1; i <= ta; ++i) {
        sgt::update(1, a[i].nl, i); sgt::update(1, a[i].nr, i);//更新线段树的区间端点
        int l = dsu::l[i], r = dsu::r[i];//获取当前区间所在集合的边界
        if (r - l >= 2) sgt::insert(1, l + 1, r - 1, i);//插入中间区间
        for (int j = 0; j < a[i].ind.size(); ++j) {
            int x = q[a[i].ind[j]].first, y = q[a[i].ind[j]].second;//获取查询的两个区间
            x = dsu::find(x); y = dsu::find(y);//查找两个区间的根节点
            if (x == y) { cout << "YES\n"; continue; }
            l = dsu::l[y]; r = dsu::r[y];//查询区间是否被当前区间包含
            if (const int x1 = a[q[a[i].ind[j]].first].nl, y1 = a[q[a[i].ind[j]].first].nr;
                (l < x1 && x1 < r) || (l < y1 && y1 < r)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}