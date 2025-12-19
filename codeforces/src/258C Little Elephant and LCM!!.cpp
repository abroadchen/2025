//
// Created by Psy.C on 2025/12/19.
//
/*
*时间复杂度：O(max(a[i]) * sqrt(max(a[i])) * log(n))
空间复杂度：O(N)
 *
*sum - pre：
当前这一轮新增的需要处理的元素个数
表示数值在区间 (prev_value, b[j]] 中的元素个数
pw(j, sum - pre)：
计算 j^(sum-pre) mod mod
表示：从j种约数中为(sum-pre)个位置分配方案数
 *
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
#define mod 1000000007
using namespace std;

ll b[N], cnt;//b:存储约数的数组, cnt:约数个数
void solve(const ll x) {//求x的所有约数
    cnt = 0;//约数计数器
    for (ll i = 1; i <= sqrt(x); ++i) {
        if (x % i == 0) {//i是x的约数
            b[cnt++] = i;//添加约数i
            if (i * i != x) b[cnt++] = x / i;//添加对应的约数x/i
        }
    }
    sort(b, b + cnt);
}

ll pw(ll x, ll y) {
    ll res = 1;
    while (y) {//当指数不为0时
        if (y & 1) res = (res * x) % mod;//结果乘以底数 指数的最低位为1
        x = (x * x) % mod;//底数平方
        y >>= 1;//指数右移一位
    }
    return res;
}

int main() {
    fast;
    ll n, a[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (ll i = a[n]; i >= 1; --i) {//从最大元素开始向下枚举
        const ll x = i; solve(x);
        ll t = 1, pre = 0;//t:当前计算结果, pre:前一个位置
        for (ll j = 1; j < cnt; ++j) {
            const int idx = lower_bound(a + 1, a + n + 1, b[j]) - (a+1);
            const ll sum = idx;//小于等于b[j]的元素个数
            t = t * pw(j, sum - pre) % mod;
            pre = sum;
        }//恰好使用所有cnt个约数的方案数
        t = t * (pw(cnt, n - pre) - pw(cnt - 1, n - pre) + mod) % mod;
        ans = (ans + t) % mod;
    }
    cout << ans << '\n';
    return 0;
}