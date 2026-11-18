//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
递推计算组合数 C(i,j) 模 mod（标准的帕斯卡三角）。
计算 1..p 的模逆（用于后面的除法取模）
" 球放入盒子 + 容斥"计数：

含义：把 n 个"单位"分配到 m 个盒子里，每个盒子有上限（取值 ≤ 某限制），求总分配方案数。
具体公式：
无上限时，m 个非负整数和为 n 的方案数 = C(n+m-1, m-1)（隔板法）。
每个盒子值 ≤ …（这里通过 i 个盒子"爆上限 x"来容斥）。
让我精确拆解：

get(n, m, x) 计算的是满足 ∑ 每个变量取值,且每个变量有某个上界 x 的方案数：

变量有 m 个，每个取 0..（上限）的整数，总和为 n。
通过容斥：枚举 i 个盒子超过上限（每个"爆"的量用 x 抵消），用 C(m,i) 选超限盒子，再用隔板 C(n - i*x + m-1, m-1) 分配剩余，符号交替即容斥。
返回方案数（若 n=0 直接返回 1，即无单位可分配只有一种空方案）。
更标准表达：这计算的是"m 个非负整数，每个 ≤ 某上界，和为 n"的方案数，用容斥：
∑ᵢ (-1)^i C(m,i) C(n-i·X + m-1, m-1)，其中 X 是单盒子可超的量（这里传入的 x）。
外层枚举 x（从 r 到 s），内层枚举 y（1..p）‍：
这一层对应"枚举某个关键分界"——看起来是枚举"最小的那个值/一定阈值 x 且正好有 y 个变量取到该值附近"。
条件 (p-y)*(x-1)+x*y >= s：用于筛选有效的 (x,y) 组合，保证分配可行。
累加项 = C(p-1, y-1) · inv[y] · get(s-x*y, p-y, x)：
C(p-1, y-1)：从 p 个里选 y-1 个（其余）的组合。
inv[y]：除以 y（用于"轮流"或排列去重）。
get(s-x*y, p-y, x)：剩余 p-y 个变量用容斥计数分配剩余和 s-x*y，每个有上界 x。
最后除以总方法数 C(s-r+p-1, p-1)：
这是分母（某种总分配/总结果数），ksm(分母) 即乘以其模逆。
得到最终概率（0-mod 内的模数）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105, M = 5005, mod = 998244353;

int c[N+M][M], inv[N], s, p;
void init() {
    c[0][0] = c[1][0] = inv[1] = 1;
    for (int i = 1; i <= s+p; i++, c[i][0] = 1)
        for (int j = 1; j <= i && j <= p; j++)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    for (int i = 2; i <= p; i++)
        inv[i] = (-1ll*inv[mod%i]*(mod/i)%mod+mod)%mod;
}
int get(int n, int m, int x) {
    if (!n) return 1;
    int res = 0, xs = 1;
    for (int i = 0; i <= m && i*x <= n; i++, xs *= -1)
        res = (res+1ll*xs*c[m][i]%mod*c[n-i*x+m-1][m-1]%mod+mod)%mod;
    return res;
}
int ksm(int x, int y=mod-2) {
    int z = 1;
    while (y) {
        if (y&1) z=1ll*x*z%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return z;
}

int r, ans;
int main() {
    fast;
    cin >> p >> s >> r; init();
    for (int x = r; x <= s; x++)
        for (int y = 1; y <= p && x*y <= s; y++)
            if ((p-y)*(x-1)+x*y >= s)
                ans = (ans+1ll*c[p-1][y-1]*inv[y]%mod*get(s-x*y,p-y,x)%mod)%mod;
    ans = 1ll*ans*ksm(c[s-r+p-1][p-1])%mod;
    cout << ans << '\n';
    return 0;
}