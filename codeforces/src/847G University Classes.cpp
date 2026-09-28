//
// Created by Psy.C on 2026/9/28.
//
/**
读入字符串个数 n。
vector<string> str(n)：创建能存 n 个字符串的容器。
for 循环依次读入 n 个字符串，存进 str[0] - str[n-1]
len 记录第一个字符串的长度。因为题目里这些字符串等长，所以所有串长度都一样，用第 0 个的长度即可
外层循环 j：按列遍历，从第 0 列到第 len-1 列。
temp = 0：每列开始时清零，用于统计当前列里 '1' 的个数。
内层循环 i：遍历所有 n 个字符串，取出第 i 个字符串的第 j 个字符 str[i][j]。
若该字符是 '1'，temp++。
统计完当前列后，用 sum = max(sum, temp) 更新历史最大值。
双重循环的物理含义：把 n 个字符串看作一个 n 行 × len 列 的字符矩阵，对每一"竖列"数有多少个 '1'，最后取所有列里 '1' 数量的最大者
输出 sum，即"所有列中 '1' 数量最大的一列，其 '1' 的个数"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int n; cin >> n;
    vector<string> str(n);
    for (int i = 0; i < n; ++i) cin >> str[i];
    int len = str[0].size(), sum = 0;
    for (int j = 0; j < len; ++j) {
        int t = 0;
        for (int i = 0; i < n; ++i)
            if (str[i][j] == '1') t++;
        sum = max(sum, t);
    }
    cout << sum << '\n';
    return 0;
}