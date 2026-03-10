//
// Created by Psy.C on 2026/3/9.
//
/**
v[N*10]：以模m的余数为索引的向量数组
solve(s, t, x)：查询v[x]中在[s, t]范围内的元素个数
在v[0]中添加0（前缀和为0的索引）

计算前缀和
将索引i按前缀和模m的结果分类存储
单调栈计算pre数组
pre[i]：元素i左边第一个大于num[i]的元素位置+1
维护单调递减栈
suf[i]：元素i右边第一个大于等于num[i]的元素位置-1
从右往左遍历，维护单调递减栈

对于每个位置i，根据左右区间长度选择更优的枚举方式
第一种情况：枚举左端点k，查询满足条件的右端点数量
第二种情况：枚举右端点k，查询满足条件的左端点数量

减去n是因为要排除单个元素
时间复杂度：O(n²)的复杂度被优化为接近O(n²/2)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

vector<int> v[N*10];
int solve(ll s, ll t, ll x) {
    return ranges::upper_bound(v[x], t) - ranges::lower_bound(v[x], s);
}

ll n, m, num[N], sum[N], pre[N], suf[N], st[N];
int main() {
    fast;
    read(n), read(m); v[0].push_back(0);
    for (int i = 1; i <= n; ++i) {
        read(num[i]);
        sum[i] = sum[i-1] + num[i];
        v[sum[i]%m].push_back(i);
    }
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        while (s && num[i] >= num[st[s]]) s--;
        pre[i] = st[s] + 1;
        st[++s] = i;
    }
    st[s=0] = n+1;
    for (ll i = n; i >= 1; --i) {
        while (s && num[i] > num[st[s]]) s--;
        suf[i] = st[s] - 1;
        st[++s] = i;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (suf[i] - i > i - pre[i]) {
            for (ll k = pre[i] - 1; k < i; ++k)
                ans += solve(i, suf[i], (sum[k]+num[i])%m);
        } else {
            for (int k = i; k <= suf[i]; ++k)
                ans += solve(pre[i] - 1, i - 1, (sum[k]-num[i])%m);
        }
    }
    printf("%lld\n", ans-n);
    return 0;
}