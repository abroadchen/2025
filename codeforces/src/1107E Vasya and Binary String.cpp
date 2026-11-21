//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
状态定义 f[i][j][k]：
表示在区间 [i, j] 中，且 j 后面紧跟着 k 个与 ch[j] 字符相同的元素时，能够获得的最大分数
基础转移（直接消除）：
f[i][j][k] = f[i][j-1][0] + x[k+1]
逻辑：先把 j 及其后面随从的 k 个字符（共 k+1 个）一起消除掉，得分 x[k+1]，再加上剩余区间 [i, j-1] 的最优解
进阶转移（合并消除）：
for (int l = i; l < j; l++) if (ch[l] == ch[j]) ...
逻辑：在区间内寻找一个 l 使得 ch[l] == ch[j]。尝试先消除掉中间的 [l+1, j-1] 部分（得分 f[l+1][j-1][0]），让 ch[l] 与 ch[j] 及其随从合并。此时 ch[l] 后面相当于多了 k+1 个相同字符，状态转移至 f[i][l][k+1]。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 151;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll n, x[N], f[N][N][N];
char ch[N];
int main() {
    fast;
    n = rd(); scanf("%s", ch+1);
    rep(i,n) x[i] = rd();
    for (int i = n; i; i--)
        for (int j = i; j <= n; j++)
            for (int k = 0; k < n; k++) {
                f[i][j][k] = f[i][j-1][0] + x[k+1];
                for (int l = i; l < j; l++) if (ch[l] == ch[j])
                    f[i][j][k] = max(f[i][j][k],f[l+1][j-1][0]+f[i][l][k+1]);
            }
    cout << f[1][n][0] << '\n';
    return 0;
}