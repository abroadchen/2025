//
// Created by Psy.C on 2025/11/30.
//
/*
*时间复杂度：O(n)
空间复杂度：O(1)（除了输入数组）
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin>>a[i];
    ll t(1), cnt(0);
    while (2 * t < n) t *= 2;//找到小于 n/2 的最大2的幂次
    for (int i = 0; i < n - 1; ++i) {//遍历数组前 n-1 个元素
        if (i + t >= n) t /= 2;//当前索引 i 加上步长 t 超出数组范围 将步长减半
        a[i + t] += a[i];//将当前位置 i 的值累加到距离 t 步的位置上
        cnt += a[i];//累计当前元素的值到总操作次数
        a[i] = 0;//将当前元素清零
        cout << cnt << '\n';
    }
    return 0;
}