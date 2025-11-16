//
// Created by Psy.C on 2025/11/16.
//
/*
*n: 总元素个数
k: 分组数
a[N]: 存储n个元素的数组
x: 每组基本元素个数，x = n / k
q: 已经给出的分组方案数
t: 临时变量，用于读取输入
used[N]: 标记数组，记录哪些元素已被使用
mn: 最小平均值（初始化为最大整数）
mx: 最大平均值
v: 存储未被使用的元素的向量
 *
*检查是否有足够的未使用元素来组成新的一组
n - k * (n / k) 是余数，即不能整除的部分
 *
*计算由最小的x个未使用元素组成的组的总和
更新最小值mn和最大值mx
*计算由最大的x个未使用元素组成的组的总和
更新最小值mn和最大值mx
 *
 *
 *O(q×x + v×log(v))，其中x=n/k，v是未使用元素数
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 105;
int n, k, a[N], x, q, t, used[N],
mn = INT_MAX, mx;
vector<int> v;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    x = n / k; cin >> q;
    while (q--) {
        int ans = 0;
        for (int i = 0; i < x; ++i) cin >> t,
            ans += a[t], used[t] = 1;
        mn = min(mn, ans);
        mx = max(mx, ans);
    }
    for (int i = 1; i <= n; ++i) if (!used[i]) v.push_back(a[i]);
    sort(v.begin(), v.end());
    if (v.size() >= x + (n - k * (n / k))) {
        int ans = 0;
        for (int i = 0; i < x; ++i) ans += v[i];
        mn = min(mn, ans);
        mx = max(mx, ans);
        ans = 0;
        for (int i = v.size() - x; i < v.size(); ++i) ans += v[i];
        mn = min(mn, ans);
        mx = max(mx, ans);
    }
    printf("%.6f %.6f", (double)mn/x, (double)mx/x);
    return 0;
}