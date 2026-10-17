//
// Created by Psy.C on 2026/10/17.
//
/**
数组 a 存当前组的数；n 为个数；s 是一个 set（自动去重、默认升序）
while (cin >> n)：反复读入 n 直到输入结束（多组测试数据）。
每组先 s.clear() 清空集合。
读入 n 个数存入 a，同时 s.insert(a[i]) 把每个数插入 set——自动去重
sum = s.size()：得到不同数值的个数。
sort(a, a+n) 升序排序（只为了取最小值 a[0]）。
if (a[0] == 0) sum--：如果最小数是 0，则结果减 1（即不统计 0）。
输出 sum
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 101;

int a[N], n;
set<int> s;
int main() {
    fast;
    while (cin >> n) {
        s.clear();
        for (int i = 0; i < n; ++i) {
            cin >> a[i]; s.insert(a[i]);
        }
        int sum = s.size();
        sort(a, a + n);
        if (a[0] == 0) sum--;
        cout << sum << '\n';
    }
    return 0;
}