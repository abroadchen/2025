//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
len：该片段代表的已处理长度。
ans：已满足条件的计数。
pre / suf：两个 bitset（长度 N），记录状态片段前/后缀的"可行性/匹配信息"，用来在线性合并时按位快速结算跨接部分的贡献（bitset 的与、移位、count 加速）
合并 a、b 两个字符串片段时，除了各自内部答案相加，还要结算"跨过 a→b 交界处新形成的一整段模式匹配"——用 bitset 的按位与求出交界处能同时满足 a 的后缀形状和 b 的前缀形状的起始位置个数，即 (L&R).count()。这是把 O(len) 的跨接扫描压成 bitset 位运算。

pre(len) 辅助函数返回"长度 len 的全 1 掩码"，用来做带范围的右移/移位裁剪
类型是 node，即每个状态自带一段"串片段"的 pre/suf/len/ans，通过 operator+ 往下传、逐位拼接。
dp[i][j][x] 记录"已经确定前 i 位、模 m 为 j、紧贴状态 x"时对应的字符串片段信息，把不同位的贡献用 + 累积拼装，等价于把数位 DP 的"选位"过程当成片段级联

// 1) 把 R 转成 d 进制，从低位到高位存进 b[1..bl]
    // 2) 初始化第 0 位 dp[0][j][x]：用模式 b0 初始化长度为 1 的片段
    // 3) 数位 DP：从小到大枚举每一位，lim 由 tight 决定
    //    对于每一位要么继承上一位（x && lim==0），要么枚举当前位 v
    //    dp[i][j][x] += dp[i-1][(j+g[v])%m][...]   ← 状态转移，模 m 随 g[v] 前进
    // 4) 返回 dp[bl][0][1].ans（模为 0、tight=1 的最终答案）
状态转移 (j + g[v]) % m 说明：模型的核心是"前缀和/模和"计数 —— 用带权的 g[v]（每个 d 进制位 v 对应一个权重），累积模 m，求总和能被什么条件满足（这里最终要求模为 0）。
dp[0] 的初始化利用模式 b0：pre/suf 位由 j <= b0[...] 比较而得——这是在做字符串匹配 / 字典序类限制：当前状态片段要能被参考模式初始部分接受。
用 x（tight 标志）正确统计所有 ≤ R 的数，经典数位 DP 边界
get(r) 与 get(l+n-2) 分别计算两个前缀，两者相减得到目标区间内的合法计数（做了端点平移：l--、r-- 以及 l+n-2 是配合"窗口长度 n"的对齐偏移，把"滑动窗口内满足条件"换算成可数前缀差）。
两次 get 之间用 init() 清零 dp（因为 dp/b 等是全局，需复位以免污染第二次查询）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e4+10, M = 65, D = 25;

int n;


struct node {
    ll len, ans;
    bitset<N> pre, suf;
} dp[M][M][2];

bitset<N> o;
inline bitset<N> pre(int len) { return o>>(N-len); }
inline node operator+(node a, node b) {
    node c; c.len = a.len+b.len; c.ans = a.ans+b.ans; c.pre = a.pre;
    if (a.len < n) c.pre &= (b.pre>>a.len)|(o<<(n-a.len));
    c.suf = b.suf;
    if (b.len < n) c.suf &= (a.suf<<b.len)|pre(b.len+1);
    if (a.len+b.len >= n) {
        auto L = a.suf;
        if (a.len < n) L &= pre(a.len+1);
        auto R = b.pre;
        if (b.len < n) R &= o<<(n-b.len);
        c.ans += (L&R).count();
    }
    return c;
}

void init() {
    rep(i,63) rep(j,63) rep(x,1) {
        auto &[len, ans, pre, suf] = dp[i][j][x];
        len = ans = 0; pre.reset(), suf.reset();
    }
}

int bl, b[M], d, m, b0[N], g[D];
ll get(ll R) {
    if (R < 0) return 0;
    ll t = R; bl = 0;
    while (t) { b[++bl] = t%d; t/=d; }
    rep(j,m-1) rep(x,1) {
        auto &dt = dp[0][j][x];
        for (int i = 1; i < n; i++) {
            dt.suf[i] = j <= b0[i]; dt.pre[i] = j <= b0[i+1];
        }
        if (n == 1) dt.ans = j <= b0[1];
        dt.len = 1;
    }
    for (int i = 1; i <= bl; i++) rep(j,m-1) rep(x,1) {
        int lim = x?b[i]:d-1;
        dp[i][j][x] = dp[i-1][j][x&&lim==0];
        for (int v = 1; v <= lim; v++)
            dp[i][j][x] = dp[i][j][x] + dp[i-1][(j+g[v])%m][x&&v==lim];
    }
    ll ans = dp[bl][0][1].ans;
    init();
    return ans;
}

int main() {
    fast;
    o.set();
    cin >> d >> m;
    rep(i,d-1) cin >> g[i];//每个数字 v 的权重 g[v]
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> b0[i];
    ll l, r; cin >> l >> r; l--, r--;//端点减 1（转为"位置"而非"数值"）
    ll v1 = get(r), v2 = get(l+n-2);
    cout << v1-v2 << '\n';
    return 0;
}