//
// Created by Psy.C on 2026/9/20.
//
/**
用一个滑动窗口维护"末尾 k 个元素的和" sum：
每读入一个 a[i]，sum += a[i]（窗口右端扩展）。
当 i >= k 时，窗口已满（正好 k 个），此时把最左边将要滑出的元素 a[i-k] 减去（sum -= a[i-k]），于是 sum 变成"以 i 结尾、长度为 k 的子段和"。
然后 ans += sum，把这个子段和累加到 ans（也就是求和所有长度为 k 的子段和）。
最终 ans = 所有长度 k 的子段和之和。
（注意 a[i-k] 的下标技巧：当 i 从 k 到 n，a[i-k] 正是当前窗口的最左端，减去它窗口就右移一位。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, k;
double a[N], sum, ans;
int main() {
    rd(n), rd(k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf", a+i); sum += a[i];
        if (i >= k) sum -= a[i-k], ans += sum;
    }
    double x = n-k+1;
    printf("%lf\n", ans/x);
    return 0;
}