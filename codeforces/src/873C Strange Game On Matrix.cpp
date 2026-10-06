//
// Created by Psy.C on 2026/10/6.
//
/**
读入矩阵的行数 n、列数 m、窗口长度 k，以及整个 n×m 矩阵
对每一列 j：
sum、cnt 初始为 0，用来记录该列到目前为止的最优解。
先算该列的前缀和 s[i] = s[i-1] + a[i][j]。
再遍历窗口起点 i，t = s[i+k-1] - s[i-1] 是从第 i 行起、长度 k 的区间和。
比较更新：如果 t > sum 或 (t == sum && s[i-1] < cnt)，也就是窗口和更大，或窗口和相同时、选择前缀起点 s[i-1] 更小的那个，则更新 sum 和 cnt。
遍历完这一列后，把最优窗口和 sum 加到 ans，把对应的前缀和 cnt 加到 tot
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
int a[N][N], s[N], ans, tot;
int main() {
    fast;
    int n = rd(), m = rd(), k = rd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) a[i][j] = rd();
    for (int j = 1; j <= m; ++j) {
        int sum = 0, cnt = 0;
        for (int i = 1; i <= n; ++i) s[i] = s[i-1] + a[i][j];
        for (int i = 1; i <= n; ++i) {
            int t = s[i+k-1] - s[i-1];
            if (t > sum || (t == sum && s[i-1] < cnt))
                sum = t, cnt = s[i-1];
        }
        ans += sum, tot += cnt;
    }
    cout << ans << ' ' << tot << '\n';
    return 0;
}