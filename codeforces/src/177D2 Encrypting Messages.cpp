//
// Created by Psy.C on 2025/11/30.
//
/*
*如果当前位置已经超过滑动窗口的起始位置
从累积和中减去需要移出窗口的元素
i - n + m - 1 计算的是需要移出窗口的b序列元素的索引
*如果当前位置不超过滑动窗口的结束位置
将新的元素加入到累积和中
*将当前累积和与a[i]相加，并对c取模
结果存储回a[i]中
 *输出处理后的数组a的所有元素
 *
*窗口大小: n - m + 1（这是b序列在a序列上能滑动的最大位置数）
移出元素索引: i - n + m - 1（当窗口滑动时需要移出的元素）
移入元素索引: i（当窗口滑动时需要移入的元素）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int n, m, c, a[N], b[N];

int main() {
    fast;
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i >= n - m + 1) sum -= b[i - n + m - 1];
        if (i <= m) sum += b[i];
        a[i] = (a[i] + sum % c) % c;
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << " ";
    return 0;
}