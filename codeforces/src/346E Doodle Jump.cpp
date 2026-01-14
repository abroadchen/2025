//
// Created by Psy.C on 2026/1/14.
//
///O(log(min(a,p)))
/**
*第一部分：a * n / p
a * n 除以 p 的整数部分
这是 a*n 中包含多少个完整的 p
第二部分：(a * n % p < p / a * a - a)
a * n % p：a*n 除以 p 的余数
p / a * a - a：floor(p/a) * a - a
比较余数和这个表达式的大小
结果是布尔值（0或1）
 *
*第一项：(p + a - 1) / a * a - p
(p + a - 1) / a：向上取整 ceil(p/a)
* a：乘以a，得到 ceil(p/a) * a
- p：减去p
这实际上计算的是：ceil(p/a) * a - p，即a的倍数中大于p的最小值减去p

第二项：p % a
p 除以 a 的余数
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int dfs(const int a, const int n, const int p) {
    if (a * n < p) return max(a, p - a * n);//不需要考虑模p的运算
    const int x = a * n / p - (a * n % p < p / a * a - a);
    return dfs(min((p + a - 1) / a * a - p, p % a), x, a);
}


signed main() {
    fast;
    int q, a, n, p, h; cin >> q;
    while (q--) {
        cin >> a >> n >> p >> h; a %= p;//将a规约到[0, p-1]范围内
        if (a <= h || (a * n > p && dfs(a, n, p) <= h)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}