//
// Created by Psy.C on 2026/10/15.
//
/**
N=21：数位最多 20 位 + 1 余量（long long 最多约 19 位十进制，留一位缓冲）。
M=18010：自动机状态总数上限。
B=81：位掩码长度上限（__int128 可用的低位数量），代表了"和/差值"的可能范围 0-81。
g[M]：每个自动机状态对应的"代表值"（见后面 build 中取最低位的位置）。
a[N]：数位数组，存拆分出的各位数字（a[1] 是个位）。
tr[M][10]：状态转移表，tr[st][c] 表示在状态 st 时"走数字 c"到达的下一个状态。
f[N][M][N]：记忆化数组，f[dep][st][k] 记录结果
dep：还剩多少位没填。
eq：是否仍贴着上界（等于原数前缀）。eq=1 时只能枚举到 a[dep]；eq=0 时自由枚举 0-9。
st：当前自动机状态。
边界：!dep 时判断最终状态 g[st] <= k，是其则计 1。
记忆化：!eq 时结果可缓存（因为只有不贴界才能复用），存入 f[dep][st][k]。
枚举当前位数字 i，沿 tr[st][i] 转移到下一状态，递归累加。
注意这里第三维用 k（全局变量）作为记忆化下标，所以 k 变化时需保证 f 不混用（实际因 k 是全局且每次题目单独跑，能凑合用；但严格讲若同一程序多次不同 k 混用会出错，这里单次计数没问题）
把 x 逐位拆到 a[1..len]（个位在前）。
以 dep=len、eq=1（贴界）、st=1（初始状态）开始数位 DP
mp 做状态去重（同一掩码只建一次），tot 记录状态总数。
初始调用 build(o) 即 build(1)，掩码二进制第 0 位为 1。
对每个状态 st：
取 st 中最小的置位下标 i 存入 g[id]（代表该状态对应的"可表达值"的最小值）。这也是 dfs 边界里判断 g[st] <= k 的依据。
对每个数字 c（0-9）构造转移：遍历 st 中每个置位 i，产生两个新置位 i+c 和 |i-c|（都限制在 B 内）。把这些置位的并集作为下一状态 nxt，递归建 tr[id][c]。
数学含义：掩码的每一位表示"是否能用前面已处理数位通过某种加减组合得到当前累计值"。即这个自动机在追踪：给定的数位集合，能通过 + 与 - 而非负加绝对差的方式表达出的所有可能和。最终 g[st] 是最小的可表达值。g[st] <= k 判断该前缀组合能否给出 ≤ k 的结果
先 memset(f, -1, sizeof f) 初始化记忆化，再 build(o) 构建完整自动机（每个询问共享同一自动机）。
读入询问数 q。每次 cin >> l >> r >> k。
优化分支：若 k >= 9，直接输出区间长度 r-l+1（说明所有数都满足条件，无需 DP）。因为 B=81、可表达值范围有限，k 大到覆盖全部情况时就全满足。
否则用前缀法：get(r) - get(l-1) 统计 [l, r] 内符合条件的个数
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 21, M = 18010, B = 81;

int g[M], k, a[N], tr[M][10];
ll f[N][M][N];
ll dfs(int dep, int eq, int st) {
    if (!dep) return g[st] <= k;
    if (!eq && f[dep][st][k] != -1) return f[dep][st][k];
    int ed = eq ? a[dep] : 9;
    ll ret = 0;
    for (int i = 0; i <= ed; ++i)
        ret += dfs(dep-1, eq&&i==ed, tr[st][i]);
    if (!eq) f[dep][st][k] = ret;
    return ret;
}

int len;
ll get(ll x) {
    len = 0;
    while (x) a[++len] = x%10, x/=10;
    return dfs(len, 1, 1);
}

map<__int128, int> mp;
int tot;
__int128 o = 1;
ll build(__int128 st) {
    if (mp[st]) return mp[st];
    int id = mp[st] = ++tot;
    for (__int128 i = 0; i <= B; ++i)
        if ((st>>i)&1) { g[id] = i; break; }
    for (int c = 0; c <= 9; ++c) {
        __int128 nxt = 0;
        for (__int128 i = 0; i <= B; ++i)
            if ((st>>i)&1) {
                if (i+c <= B) nxt |= o<<(i+c);
                if (i >= c) nxt |= o<<(i-c);
                else nxt |= o<<(c-i);
            }
        tr[id][c] = build(nxt);
    }
    return id;
}





ll l, r;
int q;
int main() {
    memset(f, -1, sizeof f); build(o);
    cin >> q;
    while (q--) {
        cin >> l >> r >> k;
        if (k >= 9) cout << r - l + 1 << '\n';
        else cout << get(r) - get(l-1) << '\n';
    }
    return 0;
}