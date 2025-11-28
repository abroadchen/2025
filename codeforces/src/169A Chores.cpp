//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 数组元素个数
a: 未使用的变量
b: 用于后续计算的索引
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, a, b; cin >> n >> a >> b;
    vector<int> v(n, 0);
    for (int i = 0; i < n; ++i) cin >> v[i];
    sort(v.begin(), v.end());//对向量v进行升序排序
    cout << v[b] - v[b - 1] << '\n';
    return 0;
}