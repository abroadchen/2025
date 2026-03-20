//
// Created by Psy.C on 2026/3/21.
//
/**
a和b，分别表示两个数组的大小
对于y中的每一个元素：
upper_bound(x.begin(), x.begin() + a, y[i])：在已排序的x数组中查找第一个大于y[i]的元素位置
upper_bound(...) - x.begin()：计算该位置相对于数组起始位置的索引
这个索引值等于x数组中小于等于y[i]的元素个数
输出这个计数值，并加上空格
时间复杂度为O((a+b)log a)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b;
int main() {
    fast;
    cin >> a >> b;
    vector<ll> x(a), y(b);
    for (int i = 0; i < a; ++i) cin >> x[i];
    for (int i = 0; i < b; ++i) cin >> y[i];
    sort(x.begin(), x.begin() + a);
    for (int i = 0; i < b; ++i)
        cout << upper_bound(x.begin(), x.begin() + a, y[i]) - x.begin() << ' ';
    return 0;
}