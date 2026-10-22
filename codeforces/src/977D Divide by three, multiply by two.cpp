//
// Created by Psy.C on 2026/10/22.
//
/**
分别对 x、y 循环除以 3，统计各自能被 3 整除的次数 k1、k2（即 3 的幂次）。
注意这里循环内会不断把 x、y 本身除掉，所以比较的是"去掉所有 3 因子后的剩余值"。
规则：
若 k1 == k2（3 因子数相同），返回 x < y，即按剩余值升序（等价于按原数值升序，因为 3 因子相同）；
否则返回 k1 > k2，即 3 因子多的排前面
读入 n 个数到数组 a。
用自定义比较器 cmp 排序。
依序输出，元素间以空格分隔，末尾换行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 105;

bool cmp(ll x, ll y) {
    ll k1 = 0, k2 = 0;
    while (x%3 == 0) { x/=3; k1++; }
    while (y%3 == 0) { y/=3; k2++; }
    if (k1 == k2) return x < y;
    return k1 > k2;
}

ll n, a[N];
int main() {
    fast;
    cin >> n;
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, cmp);
    for (ll i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}