//
// Created by Psy.C on 2025/11/9.
//
/*
*凸包算法（Graham扫描法）：
构建点集的凸包
首先按坐标排序
分别构建上凸壳和下凸壳
使用叉积判断转向
 *
*线段树构建函数：
叶子节点存储单个点
非叶子节点合并左右子树的点集并构建凸包
使用merge函数合并已排序的点集
 *
*查询函数：
在指定区间内查询与给定点叉积最大的点
利用凸包的性质优化查询
返回最大叉积值和对应点的索引
 *
*p[i]：当前正在处理的点
q[k-2]：凸包构造过程中已确定的倒数第二个点
p[i] - q[k-2]：从点 q[k-2] 指向点 p[i] 的向量
 *
 *
 *
 */
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

typedef long long ll;
template<typename T>
struct point {
    friend bool operator<(const point& lhs, const point& rhs) {//（按x优先，y次要）
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
    friend point operator-(const point& lhs, const point& rhs) {//向量减法
        return point{lhs.x - rhs.x, lhs.y - rhs.y};
    }
    T x, y;//x、y坐标和索引z
    int z;
};
using pt = point<int>;
vector<pt> p[1<<18];//线段树数组，每个节点存储一个点集

template<typename T, typename K>//向量的叉积
K cross_product(const point<T>& lhs, const point<T>& rhs) {
    return (K)lhs.x * rhs.y - (K)lhs.y * rhs.x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q; cin>>n>>q;
    vector<pt> a(n, {0, 0, 0});
    for (int i = 0; i < n; ++i) cin >> a[i].y >> a[i].x, a[i].z = i;

    auto convex_hull = [&](vector<pt>& p) {
        int n = p.size();
        if (n == 1) return;
        if (!is_sorted(p.begin(), p.end())) sort(p.begin(), p.end());
        vector<pt> q(n + 1);
        int k = 0;
        for (int i = 0; i < n; ++i) {
            while (k > 1 && cross_product<int,ll>(q[k-1]-q[k-2],
                p[i] - q[k-2]) >= 0) k--;
            q[k++] = p[i];
        }
        int m = k;
        for (int i = n - 2; i >= 0; --i) {
            while (k > m && cross_product<int,ll>(q[k-1]-q[k-2],
                p[i] - q[k-2]) >= 0) k--;
            if (i) q[k++] = p[i];
        }
        q.resize(k);
        p = q;
    };

    function<void(int,int,int)> build = [&](int u, int l, int r) {
        if (l == r) { p[u] = {a[l]}; return; }
        int mid = l + r >> 1;
        build(u<<1, l, mid);
        build(u<<1|1, mid+1, r);
        p[u].resize(p[u<<1].size() + p[u<<1|1].size());
        merge(p[u<<1].begin(), p[u<<1].end(),
            p[u<<1|1].begin(), p[u<<1|1].end(),
            p[u].begin());
        convex_hull(p[u]);
    };

    function<pair<ll,int>(int,int,int,int,int,const pt&)> query =
        [&](int u, int l, int r, int ql, int qr, const pt& x) {
        if (ql <= l && r <= qr) {
            int n = p[u].size();
            for (; n > 1 && cross_product<int,ll>(p[u][n-2] - p[u][n-1],
                x) > 0; n--) p[u].pop_back();
            return pair<ll,int>({cross_product<int,ll>(p[u][n-1],x),
                p[u][n-1].z});
        }
        int mid = l + r >> 1;
        pair<ll,int> ret = {0,0};
        if (ql <= mid) ret = max(ret, query(u<<1, l, mid, ql, qr, x));
        if (mid < qr) ret = max(ret, query(u<<1|1, mid+1, r, ql, qr, x));
        return ret;
    };
    build(1, 0, n-1);
    vector<tuple<int,int,int,int>> e(q);
    for (int i = 0, l, r, t; i < q; ++i) cin >> l >> r >> t,
        e[i] = tie(t, --l, --r, i);
    sort(e.begin(), e.end());//按时间排序
    for (int i = 0; i < 1<<18; ++i) reverse(p[i].begin(), p[i].end());//反转所有凸包中点的顺序
    vector<ll> ans(q);
    for (const auto& x : e) {
        int t, l, r, i; tie(t, l, r, i) = x;
        ans[i] = query(1, 0, n-1, l, r, {-1,t,0}).second + 1;
    }
    for (const auto& x : ans) cout << x << '\n';
    return 0;
}