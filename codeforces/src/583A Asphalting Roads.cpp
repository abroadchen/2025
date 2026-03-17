//
// Created by Psy.C on 2026/3/17.
//
/**
n：矩阵边长
u[N], v[N]：存储坐标对
b[N+5], c[N+5]：标记数组，分别标记u和v是否已被使用
d[N+5]：存储结果索引
k：结果数组的有效长度

遍历所有坐标对
如果当前坐标的u值和v值都还没有被选择过：
将当前索引i+1（题目要求1-indexed）加入结果数组
标记u[i]和v[i]为已使用
k自增，指向下一个可用位置

时间复杂度：
O(n²)，需要遍历所有输入数据
空间复杂度：
O(n)，需要存储标记数组和结果数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5;
int n, u[N], v[N], b[N+5], c[N+5], d[N+5], k;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n*n; ++i) cin >> u[i] >> v[i];
    for (int i = 0; i < n*n; ++i)
        if (b[u[i]] == 0 && c[v[i]] == 0) {
            d[k++] = i + 1;
            b[u[i]] = 1; c[v[i]] = 1;
        }
    for (int i = 0; i < k-1; ++i) cout << d[i] << ' ';
    cout << d[k-1] << '\n';
    return 0;
}