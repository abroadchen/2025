//
// Created by Psy.C on 2026/4/10.
//
/**
将b从1索引转换为0索引，应用模运算，然后转换回1索引
确保b在[1, n]范围内
(a-1): 将a从1索引转换为0索引
+b: 添加偏移量
+n: 确保即使a-1+b可能是负数，结果也是正数
%n: 应用模运算以绕回圆形结构
+1: 转换回1索引系统
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, b;
int main() {
    fast;
    cin >> n >> a >> b;
    b = (b-1)%n + 1;
    int k = (a-1+b+n)%n + 1;
    if (k) cout << k << '\n';
    else cout << n << '\n';
    return 0;
}