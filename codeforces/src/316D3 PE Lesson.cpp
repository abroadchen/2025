//
// Created by Psy.C on 2026/1/5.
//
/**
* 计算 (n-m)!：从 m+1 到 n 的乘积 其他字符（非'1'）的全排列数
乘以 f[m]（m 个 '1' 的错排方案数） 不能放在原位置的排列数
 *
 *  f[i] 表示 i 个元素的错排数（D(i) = (i-1) * (D(i-1) + D(i-2))）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
#define mod 1000000007
using namespace std;

int add(int x, const int y) { x += y; return x >= mod ? x - mod : x; }

int f[N], m;
void init() {
    f[0] = f[1] = 1;
    for (int i = 2; i <= m; ++i) f[i] = add(f[i-1],
        static_cast<int>(f[i-2] * 1ll * (i - 1) % mod));
}

int main() {
    fast;
    int n, ans = 1; cin >> n; char c;
    for (int i = 1; i <= n; ++i) {
        for (cin.get(c); c != '1' && c != '2'; cin.get(c)) {}//跳过非 '1'、非 '2' 的字符
        if (c == '1') m++;
    }
    init();
    for (int i = m + 1; i <= n; ++i) ans = static_cast<int>(ans * 1ll * i % mod);
    ans = static_cast<int>(ans * 1ll * f[m] % mod);
    cout << ans << '\n';
    return 0;
}