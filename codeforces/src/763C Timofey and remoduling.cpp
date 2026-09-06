//
// Created by Psy.C on 2026/9/6.
//
/**
判断目标值 t 是否存在于已排序数组 c[1..len] 中。
实现：利用 lower_bound 找到第一个不小于 t 的位置，然后检查是否相等。
返回值：若存在返回 true，否则 false

接受一个已排序数组 c（可能是原数组 a 或其补集 b），以及一个假设的“位移” dis（初始猜测的公差）
第一步：计数匹配
对于每个元素 c[i]，检查它右移 dis（即加上 dis 并取模）后的结果是否仍在集合中。
cnt 表示满足该条件的元素个数
第二步：推导真实公差
k 是缺失的点数量（即左移 dis 后不在集合中的点）。
根据数学推导，如果真正的公差是 ad，那么 dis 应该是 ad * k（因为缺失了 k 个点导致整体错位）。
因此，通过 ad = dis / k（即 dis * k^{-1}）求出真实的公差 ad
第三步：验证唯一性
再次遍历集合，检查是否存在唯一的起点 ans。
条件 (c[i] - ad) % m 不在集合中，说明 c[i] 可能是序列的首项。
若找到多个候选，则答案不唯一，设为 -1 并退出

单点 (
n
=
1
n=1)：任意公差均可，默认输出 0。
双点 (
n
=
2
n=2) 或 全覆盖 (
n
=
m
n=m)：
起点显然是最小值 a[1]。
公差即为两个点之间的距离 (a[2]-a[1]) mod m
稀疏情况 (2n < m)：直接对原数组 a 调用 solve。
稠密情况 (2n >= m)：构造补集 b（即环上未出现的点），并对 b 调用 solve。此时的逻辑类似于寻找缺失点的等差数列，从而间接推导原集合的等差数列
当补集只有 1 或 2 个点时，可以直接算出答案（因为缺失点本身就构成了等差数列）。
否则，对补集调用 solve，得到缺失点的起点 ans 与公差 ad。
最终输出需要映射回原集合：(ans + ad * t) % m 即为原集合的首项

 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

ll m;
ll pw(ll x, ll y) {
    ll ans = 1;
    while (y > 0) {
        if (y%2 == 1) ans = ans*x%m;
        x = x*x%m;
        y /= 2;
    }
    return ans;
}

bool find(ll *c, ll t, int len) {
    int id = lower_bound(c+1, c+len+1, t) - c;
    return c[id] == t;
}

ll ad, ans;
void solve(ll *c, int len, ll dis) {
    int cnt = 0;
    for (int i = 1; i <= len; ++i)
        cnt += find(c, (c[i]+dis)%m, len);
    ll k = len-cnt;
    ad = dis*pw(k, m-2)%m;
    ans = -1;
    for (int i = 1; i <= len; ++i)
        if (find(c, (c[i]-ad+m)%m, len) == 0) {
            if (ans == -1) ans = c[i];
            else { ans = -1; return; }
        }
}

ll n, a[N], b[N];
int main() {
    while (~scanf("%lld%lld", &m, &n)) {
        for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        sort(a+1, a+n+1);
        if (n == 1) {
            printf("%lld 0\n", a[1]);
            return 0;
        }
        if (n == 2 || n == m) {
            printf("%lld %lld\n", a[1], (a[2]-a[1]+m)%m);
            return 0;
        }
        if (2*n < m) {
            ll dis = (a[2]-a[1]+m)%m;
            solve(a, n, dis);
            if (ans != -1) printf("%lld %lld\n", ans, ad);
            else printf("-1\n");
        } else {
            int t = 1;
            for (ll i = 0; i < m; ++i)
                if (find(a, i, n) == 0) { b[t] = i; t++; }
            t--;
            sort(b+1, b+1+t);
            if (t == 1) {
                printf("%lld %lld\n", a[1], (a[1]-b[1]+m)%m);
                return 0;
            }
            if (t == 2) {
                ad = (b[2]-b[1]+m)%m;
                printf("%lld %lld\n", (b[2]+ad)%m, ad);
                return 0;
            }
            solve(b, t, (b[2]-b[1]+m)%m);
            if (ans != -1) printf("%lld %lld\n", (ans+ad*t%m)%m, ad);
            else printf("-1\n");
        }
    }
    return 0;
}