//
// Created by Psy.C on 2026/4/11.
//
/**
用新的线性函数更新线段树
在中点比较新函数v与现有函数
如果新函数在中点有更高的值，则交换它们
递归更新左或右子树，如果新函数在该范围内占主导地位
查询在点x处所有存储线性函数的最大值
在叶节点返回存储函数的值
在内部节点，比较当前函数的值与相应子树结果的最大值

读取数组a并计算前缀和s和加权前缀和is
s[i] = 前i个元素的和
is[i] = j*a[j]的和，j从1到i
从n到1反向迭代
设置线性函数，斜率为-s[i]，截距为is[i]
用此函数更新线段树
在点i-1查询最大值并加上剩余项
更新总体答案

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5, inf = 1e18;

struct node { int k, b; } p[N];
int get(int x, int v) {//计算线性函数在点x处的值：k*x + b
    if (v == 0) return -inf;
    return x*p[v].k + p[v].b;
}
#define mid ((l+r)>>1)
int dat[N<<2];//每个线段树节点中的最佳线性函数索引
void update(int u, int l, int r, int v) {
    if (get(mid, v) > get(mid, dat[u])) swap(dat[u], v);
    if (l == r) return;
    if (get(l, v) > get(l, dat[u])) update(u<<1, l, mid, v);
    if (get(r, v) > get(r, dat[u])) update(u<<1|1, mid+1, r, v);
}
int query(int u, int l, int r, int x) {
    if (l == r) return get(l, dat[u]);
    int t = get(x, dat[u]);
    if (x <= mid) return max(query(u<<1, l, mid, x), t);
    return max(query(u<<1|1, mid+1, r, x), t);
}

int n, a[N], s[N], is[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], s[i] = s[i-1]+a[i], is[i] = is[i-1]+i*a[i];
    int ans = 0;
    for (int i = n; i; i--) {
        p[i] = {-s[i], is[i]};
        update(1, 0, n, i);
        ans = max(ans, query(1, 0, n, i-1) + (i-1)*s[i-1] - is[i-1]);
    }
    cout << ans << '\n';
    return 0;
}