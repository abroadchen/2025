//
// Created by Psy.C on 2026/3/20.
//
/**
q：查询次数
n：当前查询的数字
ans：结果
cnt：2的幂次的个数
sum：2的幂次的和
ans = (1+n)*n/2：计算从1到n的自然数和（等差数列求和公式）
x = 1：从2^0 = 1开始
while (x <= n)：寻找不超过n的所有2的幂次
x <<= 1：x乘以2（相当于x = x * 2）
cnt++：计数有多少个2的幂次不超过n
sum = (1ll<<cnt) - 1：计算所有2的幂次的和
1ll<<cnt = 2^cnt
2^0 + 2^1 + 2^2 + ... + 2^(cnt-1) = 2^cnt - 1（等比数列求和）
ans -= sum; ans -= sum;：从总和中减去2的幂次的和，减两次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int q;
ll n, ans, cnt, sum;
int main() {
    fast;
    cin >> q;
    while (q--) {
        cin >> n;
        ans = (1+n)*n/2; cnt = 0;
        int x = 1;
        while (x <= n) {
            cnt++;
            x <<= 1;
        }
        sum = (1ll<<cnt) - 1;
        ans -= sum; ans -= sum;
        cout << ans << '\n';
    }
    return 0;
}