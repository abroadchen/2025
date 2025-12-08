//
// Created by Psy.C on 2025/12/7.
//
/*
*读取参数：k（模数）、b（目标余数）、n（数组长度）
创建map用于统计前缀和出现次数，初始化mp[0] = 1
变量初始化：
cur：连续0的计数器
s1：统计特殊子数组个数（全0子数组）
s2：统计满足条件的子数组个数
p：前缀和
 *
*读取当前元素t
如果t非零，重置连续0计数器
如果t为零，增加连续0计数器，并累加到s1
s1统计所有全0子数组的个数
 *
*更新前缀和：p = (p + t) % (k-1)
查找满足条件的前缀和个数并累加到s2
条件：两个前缀和的差模(k-1)等于b
更新当前前缀和的计数
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int k, b, n; cin >> k >> b >> n;
    map<int, int> mp; mp[0] = 1;
    ll cur = 0, s1 = 0, s2 = 0, p = 0;
    for (int i = 1, t; i <= n; ++i) {
        cin >> t;
        if (t) cur = 0;
        else { cur++; s1 += cur; }
        p = (p + t) % (k - 1);//将当前元素t加入到之前的前缀和p中
        s2 += mp[static_cast<int>((p - b + k - 1) % (k - 1))];//安全地计算 (p - b) mod (k-1)
        mp[static_cast<int>(p)]++;
    }
    if (b == 0) cout << s1 << '\n';
    else if (b == k - 1) cout << s2 - s1 << '\n';
    else cout << s2 << '\n';
    return 0;
}