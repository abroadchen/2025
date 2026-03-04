//
// Created by Psy.C on 2026/3/4.
//
/**
第一部分：max(0ll, m-(sum-a[i])-1)

sum-a[i]: 除了第i个元素外的其他元素总和
m-(sum-a[i]): 在总资源m中，除去其他元素后剩余给第i个元素的资源
-1: 减去1（可能是为了避免某种边界情况）
max(0ll, ...)：确保结果非负
第二部分：max(0ll, a[i]-(m-n+1))

m-n+1: 在平均分配的情况下，每个元素至少可以获得的资源
a[i]-(m-n+1): 第i个元素超出平均值的部分
max(0ll, ...)：确保结果非负

约束条件:
所有元素的和不能超过m
每个元素有自身的最小需求a[i]
计算公式: 每个元素的"得分"由两部分组成：
在资源限制下的最大可能值
超过平均分配的额外值

时间复杂度为O(n)，空间复杂度为O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+1;
ll n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    ll sum = 0;///数组a中所有元素的总和
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    for (int i = 1; i <= n; ++i)
        cout << max(0ll, m-(sum-a[i])-1)+
            max(0ll, a[i]-(m-n+1)) << ' ';
    return 0;
}