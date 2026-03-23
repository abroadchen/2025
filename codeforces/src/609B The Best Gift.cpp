//
// Created by Psy.C on 2026/3/23.
//
/**
n：输入的物品总数
m：物品的种类数（种类编号从1到m）
a[11]：数组，用来统计每种物品的数量（最大支持10种物品）
x：临时变量，用于读取输入
ans：答案变量，统计总的组合方案数
循环n次，每次读取一个物品的种类编号x，然后将对应种类的数量加1
a[i]*a[j]：种类i的物品数量乘以种类j的物品数量，这代表从种类i中选1个和从种类j中选1个的组合数
时间复杂度：
O(n + m²)，其中n是读取输入的时间，m²是计算组合的时间。
空间复杂度：
O(m)，主要是数组a的空间。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, a[11], x, ans;
int main() {
    fast;
    cin >> n >> m;
    while (n--) {
        cin >> x; a[x]++;
    }
    for (int i = 1; i < m; ++i)
        for (int j = i+1; j <= m; ++j)
            ans += a[i]*a[j];
    cout << ans << '\n';
    return 0;
}