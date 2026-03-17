//
// Created by Psy.C on 2026/3/16.
//
/**
时间复杂度：O(n log n)（主要是排序的时间）
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;
struct node { ll f, m; } p[N];
int n, d;
ll sum[N], ans;
int main() {
    fast;
    cin >> n >> d;
    for (int i = 0; i < n; ++i) cin >> p[i].m >> p[i].f;
    sort(p, p + n, [](node a, node b) {
        return a.m < b.m;
    });
    sum[0] = ans = p[0].f;//初始化第一个元素
    for (int i = 1, j = 0; i < n; ++i) {
        sum[i] = sum[i-1] + p[i].f;//前缀和
        ans = max(ans, p[i].f);//单个元素的最大值
        while (p[i].m - p[j].m >= d) j++;//移动左边界j 维护滑动窗口的左边界
        ans = max(ans, sum[i] - sum[j-1]);//区间[j, i]的价值和
    }
    cout << ans << '\n';
    return 0;
}