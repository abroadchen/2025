//
// Created by Psy.C on 2026/3/15.
//
/**
vis[i]=1表示i不是素数或其幂次
v: 存储结果的向量，包含所有符合条件的数字

res = i：从当前数字i开始
不断乘以i直到超过n
将i^1, i^2, i^3...加入结果向量（只要不超过n
从i的2倍开始标记
将i的所有倍数标记为vis[j]=1
O(n log log n)：类似埃拉托斯特尼筛法的时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;

int n, vis[N];
vector<int> v;
void get() {
    for (int i = 2; i <= n; ++i) if (!vis[i]) {
        int res = i;
        while (res <= n)
            v.push_back(res), res *= i;
        for (int j = i<<1; j <= n; j += i)
            vis[j] = 1;
    }
}

int main() {
    fast;
    cin >> n; get();
    cout << v.size() << '\n';
    for (auto it : v) cout << it << ' ';
    return 0;
}