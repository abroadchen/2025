//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
线性筛求所有数的最小质因数 mn[i]（比如 mn[6]=2、mn[9]=3）
g[i] = 数 i 的质因数指数列表（g[12]=g[6]+... → {2,1} 指 2²·3¹）。推导关系：i 去一个最小质因子得 i/mn[i]，若因子同则指数累加，否则新增
每个指数多重集按降序排序
dp[state][v]：把"指数多重集 state 对应的值"变成 v 的最小步数。先算 g[1]（空指数集 = 1）到 v 的代价（等于把 v 拆成质数幂的总分解步数）
状态递推：从去掉一个最小指数 t = g[i] 出发，得到新状态 g[i] 的代价（扩展一个指数，代价用交换/合并规则更新）。
这一步本质是 状态转移的 DP，把每个"指数多重集"到各 v 值的最小步数算出来
对每对 (x,y)，枚举一个中间共同值 i，代价 = 把 x 变成 i 的步数 + 把 y 变成 i 的步数，取最小值即为答案


把每个数的质因数指数多重集 g[i] 按降序排序（从大到小）。
greater_equal() 是降序排序的比较器（a ≥ b）。
目的：用降序保证同一个多重集有唯一的标准形态，这样 dp 以 g[i] 为 key 时不同计算路径得到的是同一份结果，不会因顺序不同产生多个不同 key
dp[g[1]]：为"空指数多重集"（数字 1）这个状态创建 DP 表，大小 M。
dp[g[1]][1] = 0：数字 1 变成 1 需要 0 步（本身已经是 1）。这是 DP 的初始条件/边界
对每个 i（2 到 M-1），用最小质因数递推：

mn[i] 是 i 的最小质因数。
递推关系：dp[g[1]][i] = dp[g[1]][i/mn[i]] + mn[i] - 1
含义

要把数字 1 变成 i，先想 i 是怎么由更小的数得到的。

设 i = (i/mn[i]) × mn[i]，即 i 等于它去掉一个最小质因子后的数，再乘上这个最小质因子。

先把 1 变成 i/mn[i]：代价 dp[g[1]][i/mn[i]]
再把 i/mn[i] 乘上 mn[i] 得到 i：把一个数乘以质数 p 需要多少次操作？
关键点：乘以质数 p = 在另一个因子里把 p 的指数加 1，这需要 p−1 次操作（把 p 拆成 p−1 个并合并，或者对应原题意中"把一个因式 p^1 合并进整体"的次数）。

所以：dp[g[1]][i] = dp[g[1]][i/mn[i]] + (mn[i] − 1)



只在 g[i] 这个状态还没算过时才做（避免重复计算；dp 以状态为 key，只算一次）
t = g[i] 去掉最后一个（最小）指数后的状态（pop 掉末尾即最小指数）。
u = dp[t]：源状态（已算好）的 DP 表。
v = dp[g[i]]：当前状态要填的 DP 表，先 resize 成 M 大小。
关键理解：g[i] 就比 t 多了一个"最小指数 e = g[i].back()"。我们要把 u 的答案借用到 v
对每个值 j：v[j] 至少可以是 u[j] + e - 1。
含义：先把原状态 t 变成 j（代价 u[j]），再对"多出的那个指数 e"做操作。把 e 拆开/合并成更小因子所需的额外步数是 e - 1。
直觉：新增的那个质数幂 p^e，要把 p^e 变成能与目标匹配的形式，需要 e-1 次拆分合并。所以任何 v[j] 的上界 = u[j] + (e-1)
这个双层循环做了两种松弛更新，把 v 里更大的值更新为更小的代价。

对每个 j 和 k≥2（且 j*k < M）：

转移 (a)：u[j] + |e - k|
含义：先把源状态 t 变成 j（代价 u[j]），然后把多出的指数 e 调整成 k（代价 |e - k|），最后把 j 和 k 合并成一个数 j*k。
相当于：t → j，然后把新增的 p^e 指数从 e 改成 k，合成 j*k。
转移 (b)：v[j] + k - 1
含义：如果值 j 到 j*k 要乘 k，说明把 j 扩大 k 倍需付出 k-1 次操作（把一个数乘 k 需要的合并步数）。
这是用已更新的 v[j] 继续往后推（类似"乘 k"的转移）。

*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e6+10, M = 300, inf = 0x7f7f7f7f7f7f;

bool ispr[N];
int pri[N], idx, mn[N];
inline void get() {
    for (int i = 2; i < N; i++) {
        if (!ispr[i]) pri[++idx] = i, mn[i] = i;
        for (int j = 1; j <= idx && pri[j]*i < N; j++) {
            ispr[pri[j]*i] = 1;
            mn[pri[j]*i] = pri[j];
            if (!(i%pri[j])) break;
        }
    }
}

vector<int> g[N];
map<vector<int>, vector<int>> dp;
inline void init() {
    for (int i = 2; i < N; i++) {
        g[i] = g[i/mn[i]];//继承去掉最小质因子后的多重集
        if (mn[i] == mn[i/mn[i]]) g[i].back()++;//若因子相同, 该质数指数+1
        else g[i].push_back(2);//否则新增一个指数2
    }
    for (int i = 2; i < N; i++) ranges::sort(g[i], greater_equal());
    dp[g[1]].resize(M), dp[g[1]][1] = 0;
    for (int i = 2; i < M; i++)
        dp[g[1]][i] = dp[g[1]][i/mn[i]] + mn[i] - 1;
    for (int i = 2; i < N; i++) if (!dp.contains(g[i])) {
        vector<int> t = g[i]; t.pop_back();
        vector<int> &u = dp[t], &v = dp[g[i]]; v.resize(M);
        for (int j = 1; j < M; j++) v[j] = u[j] + g[i].back() - 1;
        for (int j = 1; j < M; j++)
            for (int k = 2; j*k < M; k++)
                v[j*k] = min({v[j*k],u[j]+labs(g[i].back()-k),v[j]+k-1});
    }
}

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

int T, x, y;
vector<int> ans;
signed main() {
    get(); init();
    T = rd();
    while (T--) {
        x = rd(), y = rd();
        int t = inf;
        for (int i = 1; i < M; i++) t = min(t, dp[g[x]][i]+dp[g[y]][i]);
        ans.emplace_back(t);
    }
    for (int z : ans) write(z), putchar('\n');
    return 0;
}