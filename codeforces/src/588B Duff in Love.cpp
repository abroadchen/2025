//
// Created by Psy.C on 2026/3/18.
//
/**
从2开始枚举所有可能的质因子i，直到i² ≤ n
如果i能整除n（即i是n的一个因子）
当i²能整除当前的n时，不断将n除以i
这个操作会消除n中的平方因子
时间复杂度：O(√n)
空间复杂度：O(1)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
int main() {
    fast;
    cin >> n;
    for (ll i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            while (n % (i*i) == 0)
                n /= i;
        }
    cout << n;
    return 0;
}