//
// Created by Psy.C on 2026/3/30.
//
/**
n: 元素个数
a[i]: 第i个元素的值
str[i]: 第i个元素的归属 ('A' 或 'B')
sa[i], sb[i]: A和B的前缀和

 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 5e5+5;

int n, a[N];
char str[N];
ll sa[N], sb[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%s", str+1);
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i-1]; sb[i] = sb[i-1];
        if (str[i] == 'A') sa[i] += a[i];
        else sb[i] += a[i];
    }
    ll res = max(sa[n], sb[n]);
    for (int i = 1; i <= n; i++) {
        res = max(res, sb[n] - sb[i] + sa[i]);//修改前缀
        res = max(res, sa[n] - sa[i] + sb[i]);//修改后缀
    }
    cout << res << '\n';
    return 0;
}