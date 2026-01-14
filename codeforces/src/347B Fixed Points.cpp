//
// Created by Psy.C on 2026/1/14.
//
/**
* if (c > 0)：如果有2-循环，可以处理一对元素（+2）
else if (b != n)：如果没有2-循环但不是所有元素都在正确位置，可以处理一个元素（+1）
 *
 *O(n)，只需遍历数组一次
 *
* 在排列中，一个k-循环是指k个元素形成的一个封闭的置换链，例如：
1-循环：a[i] = i（元素在自己的位置，不动点）
2-循环：a[i] = j 且 a[j] = i（两个元素互换位置）
3-循环：a[i] = j, a[j] = k, a[k] = i（三个元素轮换）
 *
*2-循环的性质
两个元素互换位置
只需要一次操作就能让两个元素都回到正确位置
比单个错位元素更"经济"
 *
*在置换群中：
任何置换都可以分解为不相交的循环的乘积
2-循环又称为对换（transposition）
一个2-循环可以通过一次对换操作还原
 *
 *一个置换的阶 = 所有循环长度的最小公倍数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000000
using namespace std;


int main() {
    fast;
    int n, b = 0, c = 0; cin >> n; ll a[N];
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        if (a[i] == i) b++;//元素值等于索引
        else if (a[a[i]] == i) c++;
    }
    if (c > 0) b += 2;  else if (b != n) b += 1;
    cout << b;
    return 0;
}