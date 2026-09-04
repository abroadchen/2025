//
// Created by Psy.C on 2026/9/4.
//
/**
n：数字个数；
mx = 0：当前最大值，初始为 0；
sum = 0：累计差值
循环读入每个数存到 a[i]。
每次读入后判断：若当前数比 mx 大，则更新 mx。循环结束 mx 即为数组中最大的元素
第二个循环遍历每个元素，把 mx - a[i]（该元素离最大值的差距）累加到 sum
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, mx = 0, sum = 0; cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > mx) mx = a[i];
    }
    for (int i = 0; i < n; ++i)
        sum += mx - a[i];
    cout << sum;
    return 0;
}