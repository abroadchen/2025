//
// Created by Psy.C on 2026/3/9.
//
/**
a：原始数值
b：原始索引
c：排名结果
j：当前排名的起始位置
a[1].c = 1：第一个元素的排名是1
遍历数组，如果当前元素值不等于下一个元素值：
更新j为下一个不同值的起始位置
将排名赋给下一个元素

按原始索引b升序排序
恢复原始顺序

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2001;
struct node { int a, b, c; } a[N];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].a, a[i].b = i;
    sort(a + 1, a + n + 1, [](node x, node y) {
        return x.a > y.a;
    });
    int j = 1; a[1].c = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i].a != a[i+1].a) j = i + 1;
        a[i+1].c = j;
    }
    sort(a + 1, a + n + 1, [](node x, node y) {
        return x.b < y.b;
    });
    for (int i = 1; i <= n; ++i) cout << a[i].c << ' ';
    return 0;
}