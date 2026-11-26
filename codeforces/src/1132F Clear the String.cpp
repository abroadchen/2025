//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
记忆化：if (f[i][j]) 直接返回已算结果。
单字符 i==j：1 次操作（把它涂成某色）。
两字符 i+1==j：若相同只需 1 次（整个一次涂色），不同则需要 2 次 → 1 + (s[i]!=s[j])。
空区间 i>j：0。
主转移：
f[i][j] = 1 + min(dfs(i+1,j), dfs(i,j-1))：先涂 s[i]（或 s[j]）这一格，然后处理余下子串 → 代表"首尾分别独立涂，各计一次"的基准。
枚举 k 让 s[k]==s[i]：用一次涂色把 s[i..k]（它们同字符）涂上，然后只需处理 [i+1, k-1] 内部和 [k..j]。即 dfs(i+1,k-1) + dfs(k,j)，利用相同字符可以减少一次操作（不用单独涂 s[i]）。
取以上所有方案的最小值
把 s 变成 1-based，调用 dfs(1,n) 输出最小操作次数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 505;

int f[N][N];
string s;
int dfs(int i, int j) {
    if (f[i][j]) return f[i][j];
    if (i == j) return f[i][j] = 1;
    if (i+1 == j) return f[i][j] = 1 + (s[i] != s[j]);
    if (i > j) return 0;
    f[i][j] = 1 + min(dfs(i+1,j), dfs(i,j-1));//删掉一个端点
    for (int k = i; k <= j; k++) if (s[k] == s[i])
        f[i][j] = min(f[i][j], dfs(i+1,k-1)+dfs(k,j));
    return f[i][j];
}
int n;
int main() {
    fast;
    cin >> n >> s; s = ' ' + s;
    cout << dfs(1,n);
    return 0;
}