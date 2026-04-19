//
// Created by Psy.C on 2026/4/18.
//
/**
遍历数组中的每个元素作为第一个数
遍历所有可能的2的幂次（从2¹到2³¹）
j从1到31是因为int范围内2的最大幂是2³¹
(1ll<<j): 2^j（左移j位等于乘以2^j）
t = (1ll<<j) - num[i]: 需要找到的num[i] + num[k] = 2^j的num[k]值
也就是寻找是否存在第三个数使得三个数的和为2^j

num+1+i, num+1+n: 搜索范围是从i+1到n（避免重复使用同一个元素）
lower_bound(...): 返回第一个大于等于t的元素位置
upper_bound(...): 返回第一个大于t的元素位置
upper_bound - lower_bound: 等于t的元素个数
找到三元组(i,j,k)，使得num[i] + num[j] + num[k]等于某个2的幂

固定num[i]
枚举目标值2^j
查找有多少个num[k]（k > i）满足num[k] = 2^j - num[i]
即查找有多少个num[k]使得num[i] + num[k] = 2^j
O(n log n) 排序
O(n × 31 × log n) 双重循环加二分查找
总体：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n;
ll num[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> num[i];
    sort(num + 1, num + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 31; ++j) {
            ll t = (1ll<<j) - num[i];
            ans += upper_bound(num+1+i, num+1+n, t) -
                lower_bound(num+1+i, num+1+n, t);
        }
    cout << ans << '\n';
    return 0;
}