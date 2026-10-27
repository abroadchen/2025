//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
用变量 k 统计前缀中"奇数个数 − 偶数个数"：

若 a[i] 是奇数，k++；是偶数，k--。
k 表示到位置 i 为止，奇数比偶数多多少（可为负）。
当 k == 0 时，说明从序列开头到 i 这一段内奇数和偶数个数相等，可以把这里作为一条分割线，把已经扫描过的这一段单独成段（段内奇偶配平）。此时把切这一刀（在 i 与 i+1 之间）的代价 abs(a[i] − a[i+1]) 记入数组 c
sort(c, c+j)：把所有可行切点的代价从小到大排序。
从最便宜的开始切，只要 c[i] <= b（当前预算够），就花掉 b -= c[i] 并 i++，表示切了这一刀。
最后输出 i，即在总预算 b 内最多能切几刀（贪心：优先切便宜的，才能切更多）
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e6+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, b, a[N], c[N], k, j;
signed main() {
    n = rd(), b = rd();
    for (int i = 1; i <= n; i++) a[i] = rd();
    for (int i = 1; i < n; i++) {
        if (a[i]%2) k++; else k--;
        if (!k) c[j++] = abs(a[i] - a[i+1]);
    }
    sort(c, c+j);
    int i = 0;
    for (; i < j && c[i] <= b; i++) b -= c[i];
    write(i);
    return 0;
}