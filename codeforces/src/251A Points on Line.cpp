//
// Created by Psy.C on 2025/12/17.
//
/*
*n：数组元素个数
k：给定的距离阈值
a[N]：存储元素的数组
 *
 *要找三元组(i,j,l)，其中i<j<l，所以i最多只能到n-2
*使用二分查找找到最大的索引p，使得a[p] ≤ a[i] + k
upper_bound(a + i, a + n + 1, a[i] + k)返回第一个大于a[i]+k的元素位置
减去a的基地址再减1，得到最后一个满足条件的元素索引
*计算以i为第一个元素的合法三元组数量
在区间[i+1, p]中共有(p-i)个元素
从中任选2个作为三元组的后两个元素，组合数为C(p-i,2) = (p-i)*(p-i-1)/2
将这个数量累加到答案中
 *
 *时间复杂度：O(n log n)
 *
 *
*因为 upper_bound 返回第一个不满足条件的元素位置
所以它前面的那个位置就是最后一个满足条件的元素位置
即：p = upper_bound(...) - a - 1
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;


int main() {
    fast;
    int n, k, a[N]; cin>>n>>k;
    for (int i = 1; i <= n; ++i) cin>>a[i];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n - 2; ++i) {
        const ll p = upper_bound(a + i, a + n + 1, a[i] + k) - a - 1;
        ans += (p - i) * (p - i - 1) / 2;
    }
    cout << ans;
    return 0;
}