//
// Created by Psy.C on 2026/3/19.
//
/**
N = 2e5+5：最大数组大小
M = 1e6+5：最大数值大小
flag[M]：素数筛选标记
p[M/10]：素数数组
f[M]：记录每个数的最小质因子
get(int n)：线性筛算法
if (!flag[i]) p[++tot] = i, f[i] = i;：i是素数，记录并设置f[i]=i
内层循环：用已知素数筛掉合数
f[i*p[j]] = p[j]：记录最小质因子
if (i%p[j] == 0) break;：避免重复筛选

lst[M]：记录每个质因子最后出现的位置
遍历a[i]的所有质因数
add(i, p-1), add(i, inv(p))：将phi(p) = p-1的影响添加到位置i
if (lst[p])：如果该质因子之前出现过，消除之前的影响
lst[p] = i：更新该质因子的最新位置
while (x%p == 0) x /= p;：去除所有p因子

while (j < r) update(++j);：扩展到查询右端点
ans[q[i].id] = ...：计算区间[l,r]内所有数的欧拉函数乘积
时间复杂度：O(n log n + m log n + M log log M)

pre[r]*inv(pre[l-1])%mod
pre[i] 存储原数组 a 的前缀乘积：pre[i] = a[1] * a[2] * ... * a[i]
pre[r] = a[1] * a[2] * ... * a[r]
pre[l-1] = a[1] * a[2] * ... * a[l-1]
inv(pre[l-1]) = pre[l-1] 的模逆元
pre[r] * inv(pre[l-1]) % mod = (a[1] * ... * a[r]) / (a[1] * ... * a[l-1]) = a[l] * a[l+1] * ... * a[r]
结果：区间 [l, r] 内所有原数值的乘积
3. *query(r)%mod
query(r) 是树状数组的前缀查询
存储的是欧拉函数修正因子的累积
query(r) 包含了位置 1 到 r 所有质因子的 φ 修正影响
4. *inv(query[l-1])%mod
query[l-1] 包含了位置 1 到 l-1 所有质因子的 φ 修正影响
inv(query[l-1]) 是其模逆元
目的：消除位置 [1, l-1] 的修正影响

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 1e6+5, mod = 1e9+7;

struct node {
    int l, r, id;
    bool operator<(const node &o) const {
        return r < o.r;
    }
} q[N];

bool flag[M];
int p[M/10], tot, f[M];
void get(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!flag[i]) p[++tot] = i, f[i] = i;
        for (int j = 1; j <= tot && i*p[j] <= n; ++j) {
            flag[i*p[j]] = true, f[i*p[j]] = p[j];
            if (i%p[j] == 0) break;
        }
    }
}

int ksm(int x, int p) {
    int ret = 1;
    for (; p; p>>=1, x=1ll*x*x%mod)
        if (p&1) ret=1ll*ret*x%mod;
    return ret;
}

int inv(int x) { return ksm(x, mod-2); }
int n, b[N];
void add(int x, int val) {
    for (; x <= n; x += x&-x)
        b[x] = 1ll*b[x]*val%mod;
}
int query(int x) {
    int ret = 1;
    for (; x; x ^= x&-x)
        ret = 1ll*ret*b[x]%mod;
    return ret;
}

int a[N], lst[M];
void update(int i) {
    for (int x = a[i], p = f[x]; x > 1; p = f[x]) {
        add(i, p-1), add(i, inv(p));
        if (lst[p])
            add(lst[p], inv(p-1)), add(lst[p], p);
        lst[p] = i;
        while (x%p == 0) x /= p;
    }
}

int pre[N], m, ans[N];
int main() {
    fast;
    get(M-5); cin >> n; pre[0] = 1;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], pre[i] = 1ll*pre[i-1]*a[i]%mod;
    cin >> m;
    for (int i = 1; i <= m; ++i)
        cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q+1, q+m+1);
    for (int i = 0; i <= n; ++i) b[i] = 1;
    for (int i = 1, j = 0; i <= m; ++i) {
        int l = q[i].l, r = q[i].r;
        while (j < r) update(++j);
        ans[q[i].id] = 1ll*pre[r]*inv(pre[l-1])%mod*query(r)%mod*inv(query(l-1))%mod;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}