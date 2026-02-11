//
// Created by Psy.C on 2026/2/11.
//
/**
预处理：O(n)计算阶乘对数
主循环：O(n²)遍历所有x,y组合
总体：O(n²)
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define N 100005
using namespace std;

ld f[N];//log(i!)
//log(C(n,m)) = log(n!) - log(m!) - log((n-m)!)
ld C(const int n, const int m) { return f[n] - f[m] - f[n-m]; }

int n, m, k;
int main() {
    fast;
    f[0] = 0;//0! = 1，log(1) = 0
    for (int i = 1; i <= 1e5; ++i) f[i] = f[i-1] + log(1.*i);
    cin >> n >> m >> k;
    ld ans = 0;
    for (int x = 0; x <= n; ++x)
        for (int y = 0; y <= n; ++y)
            if (n*(x+y) - x*y <= k) {
                const int z = n*(x+y) - x*y;
                const ld t = C(n, x) + C(n, y) + C(m-z, k-z) - C(m, k);
                ans = min((ld)1e99, ans + exp(t));//exp(t)：将对数转换回原数值
            }
    printf("%.10f\n", (double)ans);
    return 0;
}