//
// Created by Psy.C on 2026/3/25.
//
/**
a[i] ^= a[i-1]，这样a[L]^a[R]就是区间[L+1,R]的异或和
O((n+m)√n)，其中n是数组长度，m是查询次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1<<20;//2^20=1048576

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

ll b[N];//分块数组，用于莫队算法的分块
struct node {
    int l, r, id;//左端点、右端点和原始编号
    bool operator<(const node &o) const {
        //按块编号排序，同块按右端点排序
        return b[l] == b[o.l] ? r < o.r : l < o.l;
    }
} q[N];

///f是频次数组，a是原数组，k是目标异或值
ll ans, f[N], a[N], k;
///添加元素到当前区间
void add(int x) { ans += f[a[x]^k]; f[a[x]]++; }//寻找与a[x]异或结果为k的数 当前值的频次加1
///从当前区间删除元素
void del(int x) { f[a[x]]--; ans -= f[a[x]^k]; }

ll n, m, res[N];
int main() {
    fast;
    rd(n, m, k);
    int t = m == 0 ? 1 : max(1ll, n/(ll)sqrt(m));//保证t至少为1
    for (int i = 1; i <= n; ++i) {
        rd(a[i]); a[i] ^= a[i-1];//前缀异或和：a[i] = a[1]^a[2]^...^a[i]
        b[i] = (i-1)/t+1;//为位置i分配块编号
    }
    for (int i = 1; i <= m; ++i) {
        //读取查询区间并保存原始编号
        rd(q[i].l, q[i].r); q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    f[0] = 1;//前缀异或为0的情况
    int l = 1, r = 0;//初始为空区间
    for (int i = 1; i <= m; ++i) {
        int L = q[i].l, R = q[i].r;//当前查询的左右端点
        //调整左端点到L
        while (l < L) { del(l-1); ++l; }//缩小左边界
        while (l > L) { l--; add(l-1); }//扩大左边界
        //调整右端点到R
        while (r < R) add(++r);//扩大右边界
        while (r > R) del(r--);//缩小右边界
        res[q[i].id] = ans;//保存当前查询的答案
    }
    for (int i = 1; i <= m; ++i) printf("%lld\n", res[i]);
    return 0;
}