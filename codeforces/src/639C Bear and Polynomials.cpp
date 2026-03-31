//
// Created by Psy.C on 2026/3/31.
//
/**
n：多项式最高次项指数
a[N]：存储多项式系数（a[0]到a[n]）
k：目标阈值

寻找第一个使 tv 为奇数的系数位置 p
计算过程：tv = tv/2 + a[i]（整数除法）
当 tv 为奇数时（tv&1），记录位置 p 并中断
从高次项开始，计算 val = val*2 + a[i]
溢出检查：如果绝对值超过 inf，提前返回
最终 val = val*2 + tv（tv是第一次循环结束时的值）
从位置 p 开始向前遍历
检查条件：|val - a[i]| ≤ k
特殊处理：如果 i == n && val == a[i]，不计入结果
每次迭代将 val 左移一位（相当于乘以2）
持续溢出检查
时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

int n, a[N], k;
int get() {
    ll tv = 0, p = n;
    for (int i = 0; i <= n; ++i) {
        tv = tv/2 + a[i];
        if (tv&1) { p = i; break; }
    }
    ll val = 0; int ret = 0;
    for (int i = n; i > p; --i) {
        val = val*2 + a[i];
        if (abs(val) > inf) return ret;
    }
    val = val*2 + tv;
    if (abs(val) > inf) return ret;
    for (int i = p; i >= 0; --i) {
        if (abs(val - a[i]) <= k) {
            if (i == n && val == a[i]) {}
            else ++ret;
        }
        val <<= 1;
        if (abs(val) > inf) return ret;
    }
    return ret;
}

int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i <= n; ++i) cin >> a[i];
    cout << get() << '\n';
    return 0;
}