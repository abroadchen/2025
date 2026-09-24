//
// Created by Psy.C on 2026/9/23.
//
/**
vis[N]：实际用作「质数 → 编号」的映射（vis[x] 等于质数 x 在第几个质因子编号）。虽然名字叫 vis，这里作映射表。（弱相关小细节，不必深究）
pri[M]：按出现顺序存的质数表。
tot：不同质因子总数
get(cnt, x)：对 x 做质因数分解，把每个质因子的指数累计到 cnt[质因子编号]。
若质数从未出现，分配一个新编号 vis[i] = ++tot。
循环 i*i <= x 后，若 x>1 则剩余的是一个大质数，同样登记。
关键：tot 是全局累计的不同质因子数量。多个 get 调用会不断往里加新的质因子编号，共用同一个质数表和 vis 映射
对每个质因子编号 x，枚举它在「目标数」里的指数取 0..ps[x]，累积乘积 now。
所有质因子枚举完（x > tot）且 now <= n 时 ans++。
实际上这是在统计「所有指数不超过 ps 的约数/组合数中，乘积 ≤ n 的个数」——等价于统计某数所有满足某个上界性质的约数个数
典型的容斥原理搜索：flag = ±1。
pn[x] 是「被约束数」的质因子指数，要选含该质因子的项则需 pn[x] > ps[x]，累乘 xp[x]*pri[x]（xp[x] = pri[x]^ps[x]，再乘一个 pri[x] 变成 pri[x]^(ps[x]+1)，即超过可选上限），并翻符号 -flag。
最终 ans += flag * (m/now) 累加「满足整除关系的倍数个数」（m/now 是 m 中 now 的倍数数量）。
这是「用容斥求：在 1..m 中，不被某些「过小的约数」覆盖的数的个数」之类的模型。
输入 9 个数，分成三组：
前 3 个相乘得 n，指数存 pn。
中 3 个相乘得 m，指数存 pm。
后 3 个相乘得 s，指数存 ps，并且 get(ps, 2); s<<=1 —— 额外乘个 2（对 s 质因子指数加 1，并 s *= 2）。
ps 同时被 dfs 和 dfs2 用作「指数上限」。
注意：n,m,s 初始为 1 再逐项相乘，实际 s 的最终值是「后三个数之积 × 2」。get(ps,2) 会把质因子 2 的指数加 1，s<<=1 等价于 s*=2
T 组测试间要重置指数数组和 vis 映射（vis 清零，否则下组 get 会误判质数已存在）
多组数据，每组 solve()：解析输入 → dfs 统计第一类 → 计算 xp → dfs2 容斥统计第二类 → 输出 ans → init() 清场
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+10, M = 60;
int vis[N], tot, pri[M];
inline void get(int* cnt, int x) {
    for (int i = 2; i*i <= x; ++i)
        if (x%i == 0) {
            if (!vis[i]) vis[i] = ++tot, pri[tot] = i;
            while (x%i == 0) x/=i, cnt[vis[i]]++;
        }
    if (x > 1) {
        if (!vis[x]) vis[x] = ++tot, pri[tot] = x;
        cnt[vis[x]]++;
    }
}

int n, ans, ps[M];
void dfs(int x, int now) {
    if (now > n) return;//超过 n 就剪枝
    if (x > tot) { ans++; return; }//所有质因子分配完，计数
    dfs(x+1, now);//该质因子指数取 0
    for (int i = 1; i <= ps[x]; ++i)
        dfs(x+1, now*=pri[x]);//指数取 1..ps[x]
}

int m, pn[M], xp[M];
void dfs2(int x, int now, int flag) {
    if (now > m) return;
    if (x > tot) { ans += flag*(m/now); return; }
    dfs2(x+1, now, flag);
    if (pn[x] > ps[x])
        dfs2(x+1, now*xp[x]*pri[x], -flag);
}

int s, pm[M];

inline void init() {
    memset(pn, 0, sizeof(pn));
    memset(pm, 0, sizeof(pm));
    memset(ps, 0, sizeof(ps));
    for (int i = 1; i <= tot; ++i) vis[pri[i]] = 0;
}

inline void solve() {
    int t;
    n = m = s = 1, ans = tot = 0;
    cin >> t, get(pn, t), n*=t, cin >> t, get(pn, t), n*=t, cin >> t, get(pn, t), n*=t;
    cin >> t, get(pm, t), m*=t, cin >> t, get(pm, t), m*=t, cin >> t, get(pm, t), m*=t;
    cin >> t, get(ps, t), s*=t, cin >> t, get(ps, t), s*=t; cin >> t, get(ps, t), s*=t;
    get(ps, 2), s<<=1;
    dfs(1, 1);
    for (int i = 1, j; i <= tot; ++i)
        for (j = xp[i] = 1; j <= ps[i]; ++j)
            xp[i] *= pri[i];
    dfs2(1, 1, 1);
    cout << ans << '\n';
    init();
}

signed main() {
    fast;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}