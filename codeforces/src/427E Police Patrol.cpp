//
// Created by Psy.C on 2026/2/5.
//
/**
* 三分搜索：O(log³n)
每次计算get函数：O(n/m)
总时间复杂度：O((n/m)*log³n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
#define inf 1e9
using namespace std;


ll a[N], n, m;//a数组存储数据，n是元素个数，m是间隔参数
ll get(const ll x) {//将所有元素调整到值x所需的成本，其中每次调整m个元素
    ll res = 0;
    //x在排序数组a中的插入位置
    const ll p = lower_bound(a + 1, a + 1 + n, x) - a;
    for (ll i = 1; i < p; i += m) res += x - a[i];//左边小于x的元素贡献
    for (ll i = n; i >= p; i -= m) res += a[i] - x;//右边大于等于x的元素贡献
    return res<<1;
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll l = -inf, r = inf, la, ra;
    while (l < r) {
        const ll lm = l + (r - l) / 3, rm = r - (r - l) / 3;
        la = get(lm), ra = get(rm);//计算两个分割点的函数值
        if (la <= ra) r = rm - 1; else l = lm + 1;
    }
    cout << min(la, ra);
    return 0;
}