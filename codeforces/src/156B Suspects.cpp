//
// Created by Psy.C on 2025/11/24.
//
/*
*a[N]: 存储输入的陈述数组
x[N]: 统计正面陈述（>0）的频次
y[N]: 统计负面陈述（<0）的频次
z[N]: 标记某个编号的陈述是否为真
t: 符合条件的真陈述数量
k: 负面陈述的总数
 *
*x[i]: 声称第i题为真的陈述数
k: 总的负面陈述数
y[i]: 声称第i题为假的陈述数
k - y[i]: 不声称第i题为假的陈述数（即认为第i题为真的负面陈述）
x[i] + k - y[i]: 总共认为第i题为真的陈述数
如果这个总数等于m，则第i题被判为真
 *
*如果恰好只有1个陈述被判为真（t==1），则t保持为1
否则t置为0（表示无法确定唯一真相）
 *
*对于正面陈述(a[i]>0)：如果对应题目为假则输出"Lie"，否则根据t值判断
对于负面陈述(a[i]<0)：如果对应题目为假则输出"Truth"，否则根据t值判断
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+1;
int a[N], x[N], y[N], z[N], t(0), k(0);

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > 0) x[a[i]]++;
        else y[-a[i]]++, k++;
    }
    for (int i = 1; i < n + 1; ++i) if (x[i] + k - y[i] == m) {
        t++;
        z[i] = 1;
    }
    if (t != 1) t = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) cout << (!z[a[i]] ? "Lie" : t ? "Truth" : "Not defined") << '\n';
        else cout << (!z[-a[i]] ? "Truth" : t ? "Lie" : "Not defined") << '\n';
    }
    return 0;
}