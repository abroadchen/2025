//
// Created by Psy.C on 2025/11/19.
//
/*
*f[7] 存储的是数字 -3 出现的次数
f[13] 存储的是数字 3 出现的次数
f[7] * f[13] 就是数字 -3 和 3 能组成的对数
 *
 *C(z,2) = z*(z-1)/2
 *实际的z已经是 原始z - 1
 *
 *
 */
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 10, M = 28;
ll f[M];

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, t; ll cnt = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        ++f[t + N];//t的范围是[-10, 17]，加上N=10后变成[0, 27]
    }
    for (int i = -10; i < 0; ++i) {
        cnt += f[i + N] * f[abs(i) + N];//i + N 将原始数字 i 映射到数组的有效索引范围
    }
    ll z = f[N];//数字0出现的次数
    if (z) --z;
    cout << cnt + (z * (z + 1) / 2) << '\n';
    return 0;
}