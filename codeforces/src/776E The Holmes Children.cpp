//
// Created by Psy.C on 2026/9/11.
//
/**
af 是一个通用 for 宏：af(i, 初值, 终值, dir)，dir=1 则 i 从初值 ++ 到终值，dir=0 则 --
欧拉函数求值：φ(x) = x * Π(1 - 1/p)，对所有质因子 p 累乘 (p-1)/p。
遍历 i 从 2 到 sqrt(x)，若 x%i==0 说明 i 是质因子，ans = ans/i*(i-1)，并 while 除尽 i。
循环结束后若 x>1，说明还剩一个大质因子，再乘一次 (x-1)/x。
返回 φ(x)（经典求法）
读入 n、k。
主循环：for (; k > 0; k -= 2) —— 每轮后 k 减 2。
只要 n > 1，就 n = get(n)（做一次欧拉函数迭代，即 n ← φ(n)）；
一旦 n 变为 1，break 跳出。
循环结束后输出 n % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define STB 1
#define af(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?++i:--i)
using namespace std;
constexpr int mod = 1e9+7;
int get(int x) {
    int ans = x;
    af(i, 2, sqrt(x), STB) {
        if (x%i == 0) {
            ans = ans/i*(i-1);
            while (x%i==0) x /= i;
        }
    }
    if (x > 1) ans = ans/x*(x-1);
    return ans;
}

signed main() {
    fast;
    int n, k; cin >> n >> k;
    for (; k > 0; k -= 2) {
        if (n > 1) n = get(n);
        else break;
    }
    cout << n%mod;
    return 0;
}