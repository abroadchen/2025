//
// Created by Psy.C on 2026/10/15.
//
/**
inf = 1e11 用于浮点取整位数控制
A[i] 存每个元素的离散化下标对 (l, r)。排序：按 r 升序；r 相同时按 l 降序。这一排序规则是为后面的偏序计数服务的
把 x 向下截断到小数点后约 1e11 的粒度（乘 inf 取整再除回）。用来在离散化前统一浮点精度，减少 long double 比较误差
标准一维树状数组：query(x) 求前缀和，add(x) 单点 +1。
这里 a[] 复用数组，l1 作为树状数组规模上限
注意 x[i] = -rd()：输入读入后取负号（与上一版 x[i]*inf 的符号处理呼应——本版是在值上取负，不是乘 inf）。
对每个元素计算两个实数端点：
L[i] = x[i]/(v[i]-m)
R[i] = x[i]/(v[i]+m)
都做浮点取整 get()。
分别把 L[i]、R[i] 收集进待离散化数组 h1、h2
对 L 序列和 R 序列分别：排序 → 去重 → 得到离散化索引。
用 lower_bound 把每个 L[i]、R[i] 映射成 1..l1 / 1..l2 的整数下标，存进 A[i].l / A[i].r。
unique 去重后，l1、l2 更新为不同值的个数。
注意越界风险：若 lower_bound 返回 end()（值比所有去重值都大），下标会超出；这里因为值本身来自 h1/h2 集合，理论上能命中
先按 (r 升序, l 降序) 排好。
逐个元素处理：已处理的元素数 = i-1；其中 query(A[i].l-1) 统计已处理元素里 l < A[i].l 的个数。
ans += (i-1) - query(A[i].l-1) —— 即"已处理元素中，l ≥ A[i].l 的个数"。
然后把当前 A[i].l 加入树状数组：add(A[i].l)。
因为按 r 升序处理，所以处理到当前元素时，所有已处理元素的 r 都 ≤ 当前 r。于是 query 统计得到的，正好是满足某种偏序条件（r小 → l大 计数的补）的对数。最终 ans 就是满足条件的对数
单组测试，输出 ans
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
#define ld long double
#define low_bit(x) (x&(-x))
using namespace std;

constexpr int N = 2e6+5;
constexpr ll inf = 1e11;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

struct node {
    ll l, r;
    bool operator<(const node& o) const {
        if (r != o.r) return r < o.r;
        return l > o.l;
    }
} A[N];

void get(ld & x) { x = floor(x*inf)/inf; }

ll a[N];
ll query(ll x) {
    ll res = 0;
    for (ll i = x; i; i -= low_bit(i)) res += a[i];
    return res;
}

ll l1;
void add(ll x) { for (ll i = x; i <= l1; i += low_bit(i)) a[i]++; }

ll l2, ans, n, m, x[N], v[N];
ld L[N], R[N], h1[N], h2[N];
void solve() {
    l1 = l2 = ans = 0; n = rd(), m = rd();
    rep(i,1,n) {
        x[i] = -rd(); v[i] = rd();
        L[i] = (ld)x[i]/((ld)v[i]-m);
        R[i] = (ld)x[i]/((ld)v[i]+m);
        get(L[i]), get(R[i]);
        h1[++l1] = L[i]; a[l1] = 0; h2[++l2] = R[i];
    }
    sort(h1+1, h1+l1+1);
    l1 = unique(h1+1, h1+l1+1) - (h1 + 1);
    sort(h2+1, h2+l2+1);
    l2 = unique(h2+1, h2+l2+1) - (h2 + 1);
    rep(i,1,n) {
        A[i].l = lower_bound(h1+1, h1+l1+1, L[i]) - h1;
        A[i].r = lower_bound(h2+1, h2+l2+1, R[i]) - h2;
    }
    sort(A+1, A+n+1);
    rep(i,1,n) {
        ans += i - 1 - query(A[i].l-1);
        add(A[i].l);
    }
    write(ans), putchar('\n');
}


int main() {
    ll T = 1;
    while (T--) solve();
    return 0;
}