//
// Created by Psy.C on 2025/10/15.
//
/*
*定义节点结构体Node，包含：
sum: 区间和
lazy: 懒惰标记，用于延迟更新
mn: 区间最小值
默认构造函数：sum=0, lazy=0, mn=1e18(无穷大)
带参构造函数：初始化为给定值
apply方法：应用增量更新节点值
merge方法：合并左右子节点的信息
 *
*传播懒惰标记：
如果当前节点没有懒惰标记，直接返回
否则将懒惰标记传递给左右子节点
清空当前节点的懒惰标记
 *
*构建线段树：
如果是叶子节点，直接用原数组对应值初始化
否则递归构建左右子树，然后合并子节点信息
 *
*区间更新操作：
如果当前区间与目标区间无交集，直接返回
如果当前区间完全包含在目标区间内，直接应用更新并返回
否则传播懒惰标记，递归更新左右子树，最后合并结果
 *
*区间查询操作：
如果当前区间与目标区间无交集，返回空节点
如果当前区间完全包含在目标区间内，返回当前节点
否则传播懒惰标记，递归查询左右子树并合并结果
 *
*构造函数：调整size大小，分配空间并构建线段树
update方法：公共更新接口
query方法：公共查询接口，返回区间最小值
 *
*solve函数处理主要逻辑：
读入数组大小n和数组元素
构建线段树
处理q个查询
对于每个查询，判断是查询还是更新操作：
查询操作：如果是环形区间(l>r)，则分别查询两段并取最小值；否则直接查询
更新操作：如果是环形区间，则分别更新两段；否则直接更新
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

class SegmentTree {
private:
    int size = 1;
    struct Node {
        ll sum, lazy, mn;
        Node() : sum(0), lazy(0), mn(1e18) {}
        Node(ll val) : sum(val), lazy(0), mn(val) {}

        void apply(int l, int r, ll val) {
            sum += val;
            mn += val;
            lazy += val;
        }

        void merge(const Node& l, const Node& r) {
            sum = l.sum + r.sum;
            mn = min(l.mn, r.mn);
        }
    };

    vector<Node> seg;//存储线段树节点的向量
    void propagate(int nd, int l, int r) {
        if (seg[nd].lazy == 0) return;
        if (l != r) {
            int mid = (l + r) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
            seg[lf].apply(l, mid, seg[nd].lazy);
            seg[ri].apply(mid + 1, r, seg[nd].lazy);
        }
        seg[nd].lazy = 0;
    }

    void build(int nd, int l, int r, vector<int>& a) {
        if (l == r) {
            if (l < a.size()) seg[nd] = Node(a[l]);
            return;
        }
        int mid = (l + r) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        build(lf, l, mid, a);
        build(ri, mid + 1, r, a);
        seg[nd].merge(seg[lf], seg[ri]);
    }

    void update(int nd, int lx, int rx, int l, int r, ll val) {
        if (lx > r || rx < l) return;
        if (lx >= l && rx <= r) {
            seg[nd].apply(lx, rx, val);
            return;
        }
        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        update(lf, lx, mid, l, r, val);
        update(ri, mid + 1, rx, l, r, val);
        seg[nd].merge(seg[lf], seg[ri]);
    }

    Node query(int nd, int lx, int rx, int l, int r) {
        if (lx > r || rx < l) return Node();
        if (lx >= l && rx <= r) return seg[nd];
        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        Node ret;
        ret.merge(query(lf, lx, mid, l, r), query(ri, mid + 1, rx, l, r));
        return ret;
    }
public:
    SegmentTree(vector<int>& a) {
        while (size < a.size()) size <<= 1;
        seg.assign(2*size, Node());
        build(0, 0, size-1, a);
    }
    void update(int l, int r, ll val) { update(0, 0, size-1, l, r, val); }
    ll query(int l, int r) { return query(0, 0, size-1, l, r).mn; }
};


void solve(...) {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    SegmentTree st(a);
    int q; cin >> q;
    while (q--) {
        int l, r, v; cin >> l >> r;
        if (cin.peek() == '\n') {
            if (l > r) cout << min(st.query(l, n - 1), st.query(0, r));
            else cout << st.query(l, r);
            cout << '\n';
        } else {
            cin >> v;
            if (l > r) {
                st.update(l, n - 1, v);
                st.update(0, r, v);
            } else {
                st.update(l, r, v);
            }
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    solve(1), cout << '\n';

    return 0;
}