//
// Created by Psy.C on 2025/12/5.
//
/*
 *
*b[s2[i]] += i;: 将当前索引i累加到字符s2[i]对应的b数组位置
ans += 1. * (n - i + 1) * (a[s2[i]] + b[s1[i]]);:
计算从位置i到末尾的元素个数：(n - i + 1)
获取字符s2[i]在a数组中的累积值和字符s1[i]在b数组中的累积值之和
将这些值的乘积累加到ans中
a[s1[i]] += i;: 将当前索引i累加到字符s1[i]对应的a数组位置
 *
*对最终结果进行归一化处理，使用公式将结果除以n(n+1)(2n+1)/6
这个公式是计算1²+2²+3²+...+n²的求和公式
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
using namespace std;

constexpr int M = 300;
int n;
char s1[N], s2[N];//存储输入的字符串
double ans, a[M], b[M];

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s1[i];
    for (int i = 1; i <= n; ++i) cin >> s2[i];
    for (int i = 1; i <= n; ++i) {
        b[s2[i]] += i;
        ans += 1. * (n - i + 1) * (a[s2[i]] + b[s1[i]]);
        a[s1[i]] += i;
    }
    ans = 6. * ans / n / (n + 1) / (n * 2 + 1);
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}