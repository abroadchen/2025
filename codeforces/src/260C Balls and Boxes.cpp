//
// Created by Psy.C on 2025/12/19.
//
/*
*时间复杂度：O(n + Σa[i])，取决于数组元素的大小
空间复杂度：O(1)，只使用常数额外空间
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
using namespace std;


int main() {
    fast;
    int n, k; cin>>n>>k;
    ll a[N], mn = 2e9, cnt = 0;
    for (int i = 0; i < n; ++i) cin>>a[i];
    for (int i = 0; i < n; ++i) if (mn >= a[i]) mn = a[i];//找到数组中的最小值
    for (int i = 0; i < n; ++i) a[i] -= mn;//所有元素减去最小值
    cnt += mn * n;
    ll p = k - 1;//转换为0-based索引
    while (a[p] > 0) {
        a[p]--;//当前位置减1
        cnt++;//累计减去的总量
        p--;//向前移动
        if (p < 0) p = n - 1;//循环回到数组末尾
    }
    a[p] = cnt;//将累计的计数赋值给最终停止位置
    cout << a[0];//输出结果数组
    for (int i = 1; i < n; ++i) cout << ' ' << a[i];
    cout << '\n';
    return 0;
}