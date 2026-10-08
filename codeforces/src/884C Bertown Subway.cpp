//
// Created by Psy.C on 2026/10/8.
//
/**
读入一个排列 a[1..n]（每个值在 1..n，且是 i 的某种映射
用 v[] 标记已访问。
对每个未访问的起点，沿映射 a 走一圈形成一个置换环，cnt 是环的长度。
每个环对答案贡献 cnt*cnt，环的长度记录到数组 b[]。
p 是环的总个数
若只有一个环（p==1），直接输出 ans。
否则把所有环按长度排序，取最长的两个环做"合并"，额外加上 2 * b[p-1] * b[p-2]
(c1+c2)² = c1²+c2²+2c1c2，净增 2c1c2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;
ll n, a[N], b[N];
int v[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll ans = 0, p = 0;
    for (int i = 1; i <= n; ++i) {
        if (v[i]) continue;
        ll cnt = 1, x = a[i]; v[x] = 1;
        while (x != i) {//沿 a 走，直到回到起点 i
            x = a[x]; v[x] = 1; cnt++;
        }
        b[p++] = cnt;
        ans += cnt*cnt;
    }
    if (p == 1) cout << ans;
    else {
        sort(b, b+p);
        ans += b[p-1]*b[p-2]*2;
        cout << ans;
    }
    return 0;
}