//
// Created by Psy.C on 2025/12/1.
//字符串和数组的索引都是从0开始的
/*
*n：行数（字符串数量）
m：列数（每个字符串长度）
a[N]：每行中星号(*)的数量
b[N]：每列中星号(*)的数量
s[N]：存储n个字符串
 *
*遍历每个字符串的每个字符
如果字符是星号(*)：
a[i]++：第i行的星号数量加1
b[j]++：第j列的星号数量加1
 *
*寻找只包含一个星号的行：
遍历所有行
找到第一个只包含一个星号的行（a[i] == 1）
输出该行号并跳出循环
 *
*寻找只包含一个星号的列：
遍历所有列
找到第一个只包含一个星号的列（b[j] == 1）
输出该列号（注意：列号从1开始，所以是j + 1）并跳出循环
 *
*时间复杂度：O(n×m) - 需要遍历整个网格
空间复杂度：O(n+m) - 存储行列统计信息
查找时间：O(n+m) - 查找特殊行列
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000
using namespace std;

int n, m, a[N], b[N];
string s[N];

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < m; ++j) if (s[i][j] == '*') {//遍历时使用数组索引（从0开始）
            a[i]++; b[j]++;//统计时使用数组索引
        }
    for (int i = 1; i <= n; ++i) if (a[i] == 1) {
        cout << i << ' '; break;
    }
    for (int j = 0; j < m; ++j) if (b[j] == 1) {//输出时转换为位置编号（从1开始）
        cout << j + 1;
        break;
    }
    return 0;
}