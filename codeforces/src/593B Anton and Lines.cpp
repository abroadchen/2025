//
// Created by Psy.C on 2026/3/19.
//
/**
x1, x2：两个不同的x坐标值
k, b：线性函数y=kx+b的斜率和截距
v1：存储(f(x1), f(x2), index)的元组向量
v2：存储(f(x2), f(x1), index)的元组向量
按元组第一维（f(x1)的值）对v1排序
按元组第一维（f(x2)的值）对v2排序
比较在两种排序中同一位置的原始索引
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll x1, x2, k, b;
vector<tuple<ll, ll, int>> v1, v2;
int main() {
    fast;
    cin >> n >> x1 >> x2;
    for (int i = 0; i < n; ++i) {
        cin >> k >> b;
        v1.push_back({k*x1+b, k*x2+b, i});
    }
    ranges::sort(v1);
    for (int i = 0; i < n; ++i)
        v2.push_back({get<1>(v1[i]), get<0>(v1[i]), get<2>(v1[i])});
    ranges::sort(v2);
    bool ans = false;
    for (int i = 0; i < n; ++i)
        if (get<2>(v1[i]) != get<2>(v2[i]))
            ans = true;
    cout << (ans ? "YES" : "NO") << '\n';
    return 0;
}