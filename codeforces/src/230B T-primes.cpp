//
// Created by Psy.C on 2025/12/10.
//
/*
 * O(N log log N + T)，其中T是查询次数
 *
*从3开始，只检查奇数（步长为2）
只需检查到√N，因为大于√N的因子已经被标记过了
如果i是质数（prime[i]为false），则标记其所有倍数为合数
从i²开始标记（因为小于i²的倍数已被之前的质数标记过）
步长为2*i，只标记奇数倍数（偶数倍数已被2标记）
 *
*r * r == n: 检查n是否为完全平方数（确保平方根是整数）
!prime[r]: 检查平方根r是否为质数
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000001
using namespace std;

bool prime[N];
void f() {//生成质数表
    int i;
    prime[0] = prime[1] = true;
    for (i = 4; i < N; i += 2) prime[i] = true;//标记所有大于2的偶数为合数（因为它们都能被2整除

    for (i = 3; i * i <= N; i += 2) {
        if (!prime[i]) {
            for (int j = i * i; j < N; j += 2 * i) prime[j] = true;
        }
    }
}

int main() {
    fast;
    f();
    ll t, n; cin>>t;
    for (int i = 1; i <= t; ++i) {
        cin>>n; const ll r = static_cast<ll>(sqrt(n));
        if (r * r == n && !prime[r]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}