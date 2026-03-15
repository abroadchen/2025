//
// Created by Psy.C on 2026/3/15.
//
/**
s[N]：输入字符串
w[N]：字符转换为数值（'a'=1, 'b'=2, ...）
g[i][j]：前i个字符，状态为j的方案数
状态数为8（3位二进制）
n（字符串长度）和m（字符种类数）
将字符'a','b',...转换为1,2,...
g[0][7] = 1：初始状态为111（二进制），表示初始时所有条件都满足
j&1：最低位
j>>1&1：中间位
j>>2&1：最高位

如果当前字符k等于w[i]，则保留原状态的最低位
否则使用原状态的中间位作为新状态的最低位
如果k等于w[i+1]，则保留原状态的中间位作为新状态的中间位
否则，如果(j>>2|S)&1为0，跳过此状态（无效状态）
如果k等于w[i+2]，则保留原状态的最高位作为新状态的最高位
否则使用新状态S的中间位作为新状态的最高位

输出最终状态为0和1的方案数之和
时间复杂度：O(n × 8 × m) = O(8nm)
空间复杂度：O(n × 8) = O(8n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

char s[N];
int w[N];
ll g[N][8];
int main() {
    fast;
    int n = rd(), m = rd(); scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) w[i] = s[i] - 96; g[0][7] = 1;
    for (int i = 0; i <= n-1; ++i)
        for (int j = 0; j < 8; ++j) {
            if (!g[i][j]) continue;
            for (int k = 1; k <= m; ++k) {
                int S = 0;
                if (k == w[i]) S |= j&1; else S |= j>>1&1;
                if (k == w[i+1]) S |= (j>>1&1)<<1;
                else if (((j>>2|S)&1) == 0) continue;
                if (k == w[i+2]) S |= (j>>2&1)<<2;
                else S |= (S>>1&1)<<2;
                g[i+1][S] += g[i][j];
            }
        }
    cout << g[n][0] + g[n][1];
    return 0;
}