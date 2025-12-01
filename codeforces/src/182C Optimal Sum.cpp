//
// Created by Psy.C on 2025/12/1.
//
/*
*a[N], b[N]：存储输入数组和其相反数数组
v：用于离散化的向量
node结构体：线段树节点，包含：
cnt：该区间内负数个数
sum：该区间内负数的和
tr[N<<2]：线段树数组（4倍空间）
 *
*初始化线段树节点
叶子节点无需特殊处理
非叶子节点递归构建左右子树
 *
*在位置idx插入/删除值val
op=1表示插入，op=-1表示删除
更新路径上所有节点的统计信息
 *
*查询最小的k个负数的和
如果左子树元素足够，只在左子树查询
否则在左右子树分别查询
 *
*n：数组长度
len：窗口长度
k：最多可以选择的负数个数
x[]：处理的数组
 *
*计算初始窗口的和
将负数插入线段树
计算选择最多k个最小负数的收益
 *
*滑动窗口：移除左端点，添加右端点
更新线段树
计算当前窗口的最优解
 *
*时间复杂度：O(n log n) - 离散化 + 线段树操作
空间复杂度：O(n) - 存储数组和线段树
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 100007
using namespace std;

int a[N], b[N];
vector<int> v;
struct node { int cnt, sum; } tr[N<<2];

void build(const int p, const int l, const int r) {
    tr[p].cnt = 0; tr[p].sum = 0;
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
}

void update(const int p, const int l, const int r, const int idx, const int val, const int op) {
    if (l == r) {
        if (op == 1) { tr[p].cnt++; tr[p].sum += val; }
        else { tr[p].cnt--; tr[p].sum -= val; }
        return;
    }
    const int mid = (l + r) >> 1;
    if (idx <= mid) update(p<<1, l, mid, idx, val, op);
    else update(p<<1|1, mid+1, r, idx, val, op);
    tr[p].cnt = tr[p<<1].cnt + tr[p<<1|1].cnt;
    tr[p].sum = tr[p<<1].sum + tr[p<<1|1].sum;
}

int query(const int p, const int l, const int r, const int k) {
    if (l == r) {
        if (k <= tr[p].cnt) return k * v[l];
        return tr[p].sum;
    }
    const int mid = (l + r) >> 1;
    if (tr[p<<1].cnt >= k) return query(p<<1, l, mid, k);
    return tr[p<<1].sum + query(p<<1|1, mid+1, r, k - tr[p<<1].cnt);
}

int f(const int n, const int len, const int k, int x[]) {
    v.clear();
    for (int i = 1; i <= n; ++i) v.push_back(x[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    const int m = static_cast<int>(v.size());
    build(1, 0, m - 1);
    int ans = static_cast<int>(-1e18), sum = 0;
    for (int i = 1; i <= len; ++i) {
        sum += x[i];
        if (x[i] < 0) {
            const int idx = static_cast<int>(lower_bound(v.begin(), v.end(), x[i]) - v.begin());
            update(1, 0, m - 1, idx, x[i], 1);
        }
    }
    int t1 = tr[1].cnt, t = min(k, t1), sn = query(1, 0, m-1, t);
    ans = max(ans, sum - 2 * sn);
    for (int l = 2, r = len + 1; r <= n; ++l, ++r) {
        sum -= x[l-1]; sum += x[r];
        if (x[r] < 0) {
            const int in = static_cast<int>(lower_bound(v.begin(), v.end(), x[r]) - v.begin());
            update(1, 0, m - 1, in, x[r], 1);
        }
        if (x[l-1] < 0) {
            const int out = static_cast<int>(lower_bound(v.begin(), v.end(), x[l-1]) - v.begin());
            update(1, 0, m - 1, out, x[l-1], -1);
        }
        t1 = tr[1].cnt; t = min(k, t1); sn = query(1, 0, m-1, t);
        ans = max(ans, sum - 2 * sn);
    }
    return ans;
}

signed main() {
    fast;
    int n, len, k; cin >> n >> len;
    for (int i = 1; i <= n; ++i) { cin >> a[i]; b[i] = -a[i]; }
    cin >> k;
    cout << max(f(n, len, k, a), f(n, len, k, b));
    return 0;
}