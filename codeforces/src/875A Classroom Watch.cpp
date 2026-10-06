//
// Created by Psy.C on 2026/10/6.
//
/**
ans = x 先取 x 本身。
while(x): 循环累加 x 的每一位数字到 ans，即 ans = x + digit(x)，其中 digit(x) 是 x 的各位数字之和。
若 ans == n，返回 true——说明 x 是 n 的一个生成元。
例如 n = 100，x = 86：86 + 8 + 6 = 100，所以 86 是 100 的生成元
关键优化是枚举范围：i 从 n-81 到 n。
为什么上界到 n？因为 x + digit(x) = n，显然 x < n（digit(x) >= 1），所以 x <= n-1 < n，上界 n 足够（其实到 n-1 就行，但取 n 不影响，因为 ok(n) 若成立也是解）。
为什么下界是 n-81？由于 x 最多有多少位？x + digit(x) 中 digit(x) 最大值可以估计：即使 x 有 10 位，每位最大 9，digit(x) <= 9*若干位。这里取了保守上界：digit(x) <= 81（假设最多 9 位 × 9 = 81 是最大可能的各位和上限；即使超出也只是少枚举，一般满足）。所以 x >= n - 81 才可能满足 x + digit(x) = n。
枚举这个窄范围，用 ok(i) 判定，把满足的存入 ans，个数 l 自增
先输出解的个数 l，再逐个输出每个生成元（按从小到大排序，因为枚举 i 是从小到大）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 110;
int n, ans[N], l;
bool ok(int x) {
    int ans = x;
    while (x) {
        ans += x % 10;
        x /= 10;
    }
    if (ans == n) return true;
    return false;
}

int main() {
    fast;
    n = rd();
    for (int i = n-81; i <= n; ++i)
        if (ok(i)) ans[++l] = i;
    cout << l << '\n';
    for (int i = 1; i <= l; ++i) cout << ans[i] << '\n';
    return 0;
}