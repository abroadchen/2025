//
// Created by Psy.C on 2026/2/10.
//
/**
l, r：区间范围
h1：正向哈希值（int模mod，ull自然溢出）
h2：反向哈希值（int模mod，ull自然溢出）
pw1[i]：base^i mod mod
pw2[i]：base^i（ull类型，自然溢出）

将两个相邻区间合并
正向哈希：hash(left) + hash(right) * base^|left|
反向哈希：hash(right) + hash(left) * base^|right|

依次将排列中的位置设为0
计算以p[i]为中心的最大对称区间
查询该区间的正向和反向哈希值
如果不相等，说明不对称，输出"YES"

时间复杂度：O(n log n)，每次更新/查询O(log n)
空间复杂度：O(n)，线段树空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ull unsigned long long
#define N 300005
#define mod 998244353
#define base 233
using namespace std;

struct node {
    int l{}, r{};
    pair<int, ull> h1, h2;
} tr[N<<2];

int pw1[N];
ull pw2[N];
node operator+(const node &a, const node &b) {
    node c;
    c.l = a.l, c.r = b.r;
    c.h1.first = (a.h1.first + (ull)b.h1.first*pw1[a.r-a.l+1]%mod) % mod;
    c.h2.first = (b.h2.first + (ull)a.h2.first*pw1[b.r-b.l+1]%mod) % mod;
    c.h1.second = a.h1.second + b.h1.second*pw2[a.r-a.l+1];
    c.h2.second = b.h2.second + a.h2.second*pw2[b.r-b.l+1];
    return c;
}

void build(const int u, const int l, const int r) {
    if (l == r) {
        tr[u] = {l, r, {1, 1}, {1, 1}};//叶子节点初始化为{1,1}
        return;
    }
    const int mid = (l + r) >> 1;
    build(u<<1, l, mid);
    build(u<<1|1, mid+1, r);
    tr[u] = tr[u<<1] + tr[u<<1|1];//区间合并：左右子树合并
}

void update(const int u, const int x) {
    if (tr[u].l == tr[u].r) {
        tr[u] = {tr[u].l, tr[u].r, {0, 0}, {0, 0}};//将位置x的值设为0
        return;
    }
    if (const int mid = (tr[u].l + tr[u].r) >> 1; mid >= x) update(u<<1, x);
    else update(u<<1|1, x);
    tr[u] = tr[u<<1] + tr[u<<1|1];
}

//完全包含、跨中点、在左/右子树
node query(const int u, const int l, const int r) {//返回[l,r]区间的哈希值
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    const int mid = (tr[u].l + tr[u].r) >> 1;
    if (mid >= l && mid < r) return query(u<<1, l, r) + query(u<<1|1, l, r);
    if (mid >= l) return query(u<<1, l, r);
    return query(u<<1|1, l, r);
}

int n, p[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i];//排列p
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pw1[i] = (ull)pw1[i-1]*base%mod;
        pw2[i] = pw2[i-1]*base;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        update(1, p[i]);
        const int len = min(p[i]-1, n-p[i]);
        if (auto t = query(1, p[i]-len, p[i]+len); t.h1 != t.h2) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}