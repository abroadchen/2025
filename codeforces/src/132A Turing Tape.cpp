//
// Created by Psy.C on 2025/11/19.
//
/*
*m = n（用于计算）
s = 1（权重因子）
x = 0（结果）
y = 0（位数计数器）
 *
*计算n的最高位权重：
不断将m除以2
如果m仍大于0，则将s乘以2
最终s是大于等于n的最小2的幂次
 *
*将n的二进制位反转：
取n的最低位(n%2)，乘以权重s，加到结果x中
权重s除以2（右移一位）
n除以2（去掉最低位）
位数计数器y加1
 *
 *将结果左移，确保总共有8位（补足前导零的效果）
 */
#include <vector>
#include <iostream>
using namespace std;

const int mod = 256;

typedef long long ll;
ll func(ll n) {
    ll m = n, s = 1, x = 0, y = 0;
    while (m > 0) {
        m /= 2;
        if (m > 0) s *= 2;
    }
    while (n > 0) {
        x += n % 2 * s;
        s /= 2;
        n /= 2;
        y++;
    }
    for (int i = 0; i < 8 - y; ++i) x *= 2;
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string a; getline(cin, a);
    vector<int> q(a.size() + 1, 0);
    for (int i = 0; i < a.size(); ++i) q[i+1]= func(a[i]);
    for (int i = 1; i <= a.size(); ++i)
        cout << (q[i-1]-q[i]+mod)%mod << '\n';
    return 0;
}