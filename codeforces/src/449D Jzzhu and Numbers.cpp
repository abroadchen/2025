//
// Created by Psy.C on 2026/2/9.
//
/**
add：计算(x+y) mod mod，返回结果
Add：计算x = (x+y) mod mod，修改原变量

c[N]：预计算的2的幂次数组（模mod）
f[N]：统计每个数字出现的频率
ans：最终答案
b[N]：预计算的popcount（二进制中1的个数）奇偶性

c[i] = 2^i，所以c[i]&j检查j的第i位是否为1
如果j的第i位为1，则将f[j]的值加到f[j^c[i]]上
j^c[i]是将j的第i位取反

c[i] = add(c[i-1], c[i-1]) = 2 * c[i-1]，即c[i] = 2^i mod mod
i^(i&-i)：将i的最低位1置0
b[i] = b[i^(i&-i)]^1：每次将1的个数奇偶性翻转

时间复杂度：O(20 * 10^6 + n) = O(10^7)
空间复杂度：O(10^6)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
#define mod 1000000007
using namespace std;

inline int add(int x, const int y) {
    x += y;
    return x >= mod ? x - mod : x;
}
inline void Add(int& x, const int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int c[N], f[N], ans, b[N];
inline void get() {
    for (int i = 0; i <= 20; ++i)
        for (int j = 1; j <= 1e6; ++j)
            if (c[i]&j) f[j^c[i]] += f[j];
    for (int i = 0; i <= 1e6; ++i)
        Add(ans, b[i] ? add(c[f[i]], mod-1) : add(mod-c[f[i]], 1));
}

int n;

int main() {
    fast;
    cin >> n; c[0] = 1;
    for (int i = 1; i <= 1e6; ++i) c[i] = add(c[i-1], c[i-1]);
    b[0] = 1;
    for (int i = 1; i <= 1e6; ++i) b[i] = b[i^(i&-i)]^1;
    for (int i = 1, x; i <= n; ++i) cin >> x, f[x]++;
    get();
    cout << ans << '\n';
    return 0;
}