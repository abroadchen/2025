//
// Created by Psy.C on 2025/11/30.
//
/*
*cnt = 0：累计操作次数（累计已处理元素的和）
dist = 1：跳跃距离
 *
*上一版：先处理元素，再输出累计值
这一版：先累计并输出，再处理元素传播
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin>>a[i];
    ll cnt(0), dist(1);
    while (2 * dist < n) dist *= 2;
    for (int i = 0; i + 1 < n; ++i) {
        cnt += a[i];
        cout << cnt << '\n';
        if (i + dist >= n) dist /= 2;
        a[i + dist] += a[i];
    }
    return 0;
}