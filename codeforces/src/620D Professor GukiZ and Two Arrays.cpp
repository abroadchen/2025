//
// Created by Psy.C on 2026/3/26.
//
/**
n, a[N]：第一个数组的长度和元素
m, b[N]：第二个数组的长度和元素
p1, q1, q2：记录最优解的位置对
p[N*N]：存储两两配对的结果

读入第一个数组，累加到d0
读入第二个数组，从d0中减去所有元素
此时d0 = sum(a) - sum(b)，即两个数组的原始差值

情况1：交换一个a元素和一个b元素
d1：记录最小差值，初始化为极大值
遍历所有a[i]和b[j]的组合
d0 - 2*a[i] + 2*b[j]：交换a[i]和b[j]后的新差值
原理：原差值d0 = sum(a) - sum(b)
交换后：(sum(a) - a[i] + b[j]) - (sum(b) - b[j] + a[i])
化简：sum(a) - sum(b) - a[i] + b[j] - b[j] + a[i] = d0 - 2a[i] + 2b[j]
情况2：预处理两个b元素的配对
枚举所有b数组中两个不同元素的配对
存储{2*b[i] + 2*b[j], {i, j}}到数组p中
按第一维排序，用于后续二分查找
情况3：交换两个a元素和两个b元素
遍历所有a数组中两个不同元素的配对
t = 2*a[i] + 2*a[j] - d0：目标值
使用lower_bound在p数组中查找最接近t的值
检查附近最多5个位置（pos-2到pos+2），找到最小差值
交换效果：d0变成d0 - 2*a[i] - 2*a[j] + 2*b[u] + 2*b[v]
要使差值最小，需要2*b[u] + 2*b[v]最接近2*a[i] + 2*a[j] - d0

计算三种情况的最小差值：不变、换1对、换2对
输出最优方案：
0：不交换 差值为|sum(a) - sum(b)|
1：交换一对元素，输出a[p1.first]和b[p1.second] 枚举所有a[i]和b[j]的交换
2：交换两对元素，输出对应的四元组 使用二分查找优化，避免暴力枚举
时间复杂度：O(n² + m²log m) 空间复杂度：O(m²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 2005;
int n, a[N], m, b[N];
ii p1, q1, q2;
pair<ll, ii> p[N*N];
int main() {
    fast;
    cin >> n;
    ll d0 = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i], d0 += a[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> b[i], d0 -= b[i];
    ll d1 = 1e18;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (d1 > abs(d0 - 2*a[i] + 2*b[j])) {
                d1 = abs(d0 - 2*a[i] + 2*b[j]);
                p1 = {i, j};
            }
    int cnt = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = i + 1; j <= m; ++j)
            p[++cnt] = {2ll*b[i]+2ll*b[j], {i, j}};
    sort(p + 1, p + cnt + 1);
    ll d2 = 1e18;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            ll t = 2ll*a[i] + 2ll*a[j] - d0;
            int pos = lower_bound(p + 1, p + cnt + 1, make_pair(t, make_pair(0, 0))) - p;
            for (int k = max(1, pos-2); k <= min(cnt, pos+2); ++k)
                if (abs(p[k].first - t) < d2) {
                    d2 = abs(p[k].first - t);
                    q1 = {i, p[k].second.first};
                    q2 = {j, p[k].second.second};
                }
        }
    d0 = abs(d0);
    ll mn = min(d0, min(d1, d2));
    cout << mn << '\n';
    if (mn == d0) cout << "0\n";
    else if (mn == d1) cout << "1\n" << p1.first << ' ' << p1.second << '\n';
    else cout << "2\n" << q1.first << ' ' << q1.second << '\n' << q2.first << ' ' << q2.second << '\n';
    return 0;
}