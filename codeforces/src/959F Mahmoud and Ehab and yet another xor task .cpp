//
// Created by Psy.C on 2026/10/20.
//
/**
node q[]：存每个查询：l（右边界）、x（目标值）、id（原始编号，用于按原顺序输出）。
cmp：按 l（右边界）升序排序 → 用于离线处理（前缀式扩展）
d[i]：线性基数组，d[i] 存一个二进制最高位为第 i 位的基底向量（0..20 共 21 位，对应数值 < 2^21）
从最高位往下，若 x 第 i 位为 1：
若 d[i]==0：把 x 作为第 i 位的基底插入，返回 1（表示"维度扩展成功，增加了向量空间的维数"）。
否则 x ^= d[i]（消去该位），继续。
若最终 x 变 0：返回 0（表示这个数被现有基底线性表示，不增加维数）。
返回值含义：1 = 秩增加了 1，0 = 秩没变
尝试用线性基把 x 消成 0：每一步若需要第 i 位但 d[i] 为空 → 表示无法表示，返回 false。
若最终能消成 0，说明 x 在基底张成的空间中，返回 true

读入 n、m，数组 a[]，以及 m 个查询（l、x，并记原始 id）。

把查询按右边界 l 升序排序 → 这样从前往后扩展，能复用之前插入的基底。

主循环（i 遍历排序后的查询）：

while (j <= q[i].l)：把下标 ≤ 当前查询右边界 l 的 a[j] 依次插入线性基，sz += insert(...) 累加秩。
check(q[i].x)：判断 x 能否由 a[1..l] 这 l 个数的异或空间表示（1 或 0）。
q[i].l - sz：l 个向量中，线性基的秩为 sz，则自由变量个数 = l - sz。每个自由变量的取值（0/1）独立，所以能表示的方案数为 2^(l-sz)。
ans[q[i].id] = check(q[i].x) * ksm(2, l-sz, p)：若 x 可表示，则方案数为 2^(l-sz) 种；否则为 0。
最后按原始 id 顺序输出每个查询的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, p = 1e9+7;

struct node { ll l, x, id; } q[N];
bool cmp(const node &a, const node &b) { return a.l < b.l; }

ll d[30];
ll insert(ll x) {
    for (ll i = 20; i >= 0; --i) {
        if ((x>>i)&1) {
            if (d[i] == 0) { d[i] = x; return 1; }
            x ^= d[i];
        }
    }
    return 0;
}
bool check(ll x) {
    for (ll i = 20; i >= 0; --i) {
        if ((x>>i)&1) {
            if (d[i] == 0) return false;
            x ^= d[i];
        }
    }
    return true;
}
ll ksm(ll a, ll b, ll p) {
    ll ans = 1;
    while (b) {
        if (b&1) ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}

ll n, m, i, j, a[N], ans[N], sz;
int main() {
    fast;
    cin >> n >> m;
    for (i = 1; i <= n; ++i) cin >> a[i];
    for (i = 1; i <= m; ++i) cin >> q[i].l >> q[i].x, q[i].id = i;
    sort(q+1, q+1+m, cmp);
    for (i = 1, j = 1; i <= m; ++i) {
        while (j <= q[i].l) { sz += insert(a[j]); j++; }
        ans[q[i].id] = (check(q[i].x))*ksm(2, q[i].l-sz, p);
    }
    for (i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}