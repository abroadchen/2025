//
// Created by Psy.C on 2026/3/30.
//
/**
将数组按sqrt(n)分块
查询按左端点所在块和右端点排序
fib[]: 斐波那契数列
fxl[], fx[]: 线段树节点存储的斐波那契相关值
d: 离散化后的不同值个数
F(n+k) = F(k)*F(n-1) + F(k+1)*F(n) (Cassini's identity的变形)
这里实现的是将斐波那契数列的索引进行偏移
sgn: 线段树节点编号
p: 斐波那契索引偏移量

离散化: rk[i] = lower_bound(...) 将值域映射到[1,d]
莫队算法: O(n√n)处理区间查询
线段树+Lazy: O(log n)处理斐波那契变换

预处理：O(n log n)
查询处理：O(m√n log d)
总体：O(n log n + m√n log d)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e4+5;

int pos[N];//每个位置属于哪个块
struct node {
    int l, r, id;
    bool operator<(const node& o) const {
        if (pos[l] == pos[o.l]) return r < o.r;//同一块按右端点升序
        return l < o.l;//不同块按左端点升序
    }
} q[N];

int fib[N<<1], fxl[N<<2], fx[N<<2], d, mod;
void shift(int sgn, int p) {
    int a = (fxl[sgn]*fib[d+p] + fx[sgn]*fib[d+p+1])%mod,//新的fx值
    b = (fxl[sgn]*fib[d+p-1] + fx[sgn]*fib[d+p])%mod;//新的fxl值
    fxl[sgn] = b, fx[sgn] = a;
}
void push_up(int sgn) {
    fxl[sgn] = (fxl[sgn<<1] + fxl[sgn<<1|1])%mod;
    fx[sgn] = (fx[sgn<<1] + fx[sgn<<1|1])%mod;
}
int laz[N<<2];
void push_down(int sgn) {
    if (laz[sgn]) {
        laz[sgn<<1] += laz[sgn];
        laz[sgn<<1|1] += laz[sgn];
        shift(sgn<<1, laz[sgn]);//同时更新斐波那契变换的偏移量
        shift(sgn<<1|1, laz[sgn]);
        laz[sgn] = 0;
    }
}

int un[N];//离散化后的数组
void right(int sgn, int l, int r, int x) {
    if (l == r) {
        fxl[sgn] = un[l]%mod*fib[d+laz[sgn]]%mod;
        fx[sgn] = un[l]%mod*fib[d+laz[sgn]+1]%mod;
        return;
    }
    push_down(sgn);
    int mid = (l+r)>>1;
    if (x <= mid) {
        right(sgn<<1, l, mid, x);//递归处理左子树
        laz[sgn<<1|1]++;//右子树懒惰标记+1
        shift(sgn<<1|1, 1);//对右子树进行+1变换
    } else right(sgn<<1|1, mid+1, r, x);
    push_up(sgn);//更新当前节点
}
void left(int sgn, int l, int r, int x) {
    if (l == r) {
        fxl[sgn] = fx[sgn] = 0;//清零
        return;
    }
    push_down(sgn);
    int mid = (l+r)>>1;
    if (x <= mid) {
        left(sgn<<1, l, mid, x);
        laz[sgn<<1|1]--;
        shift(sgn<<1|1, -1);
    } else left(sgn<<1|1, mid+1, r, x);
    push_up(sgn);
}

///rk: 值的排名，cnt: 每个排名出现次数
int rk[N], cnt[N];
void add(int x) {
    if (++cnt[rk[x]] == 1)//第一次出现，添加到线段树
        right(1, 1, d, rk[x]);
}
void del(int x) {
    if (--cnt[rk[x]] == 0)//最后一次出现，从线段树删除
        left(1, 1, d, rk[x]);
}
void init() {
    fib[d] = 0, fib[d+1] = 1;
    for (int i = d+2; i <= d<<1; i++)
        fib[i] = (fib[i-1] + fib[i-2])%mod;
    for (int i = d-1; i >= 0; i--)
        fib[i] = (fib[i+2] - fib[i+1] + mod)%mod;//反向递推
}

int n, a[N], m, ans[N];
int main() {
    fast;
    cin >> n >> mod; int sz = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; un[i] = a[i]; pos[i] = i/sz;//设置块号
    }
    sort(un + 1, un + n + 1);
    d = unique(un + 1, un + n + 1) - (un + 1);//不同值个数
    for (int i = 1; i <= n; ++i)
        rk[i] = lower_bound(un + 1, un + d + 1, a[i]) - un;//计算排名
    init();//初始化斐波那契数列
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> q[i].l >> q[i].r; q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    int L = 1, R = 0;
    for (int i = 1; i <= m; ++i) {
        while (q[i].l < L) add(--L);//扩展左边界
        while (q[i].l > L) del(L++);//收缩左边界
        while (q[i].r > R) add(++R);//扩展右边界
        while (q[i].r < R) del(R--);//收缩右边界
        ans[q[i].id] = fx[1];
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}