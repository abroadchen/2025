//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
now：当前字典树节点（引用回写）。
gl：当前位是否已经贴着下界 l（1=贴紧 l，0=已自由）。
gr：当前位是否已经贴着上界 r（1=贴紧 r，0=已自由）。
len：还剩多少位要填。
tag：前导零/特殊标记
若 l、r 长度相同：整段一次插入 ins(rt,1,1,len,1)（全程贴 l 且贴 r）。
若长度不同：分别处理长度 l.size()+1 ... r.size()-1 的自由段（0,0），再处理贴 l 的（1,0）和贴 r 的（0,1）
第一层特殊处理，缺的子连回根 rt。
BFS：逐节点补齐 fail、转移 ch（把不存在的转移指向 fail 的转移，即"自动机化"）
g[now][i] += g[fail(now)][i]：把每个节点 fail 链上的贡献累加到自己（这样走入任意节点即自动获得其 fail 祖先的全部得分），这是 AC 自动机 DP 的前缀贡献累加。因为 g 在同一层循环逐个弹，累加为子孙后代提供累积分数。
g[i][j] += g[i][j-1]：对 j 维做前缀和，使 g[i][j] 变为"长度 ≤ j"的累计得分，供 DP 里按剩余长度一次加总用
dp[i][j]：已经填了 i 位数字、当前位于 AC 自动机节点 j 时的最大累计得分。
状态转移：当前位填数字 z（0-9），跳到节点 to = ch(j,z)，得分增加 g[to][min(M-1, n-i-1)]，即"从 to 出发、剩余 n-i-1 位长度内能获得的最大附加得分（用前缀和一次性取得）"。
dp[i+1][to] = max(...)：做最大值 DP
f[i][j] = 1 表示"从状态 (i,j) 出发存在一条能达到最优 ans 的路径"。
倒推：若 dp[i+1][to] 正好等于从 (i,j) 转移的值，且 (i+1,to) 也标了可最优，则 (i,j) 记为可最优。
这是可行最优路径的标记，用于最终构造答案
先输出最高分 ans，再逐位贪心选数字：从根节点 j=1 出发，每次按 f 标记挑一个能继续通向最优解的 z，输出并沿该转移推进。最终输出一串长度为 n 的数字（即最优数字串），不换行结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
#define rep1(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e4+10, M = 810, B = 2010, inf = 1e9;

struct node {
    int ch[10], fail;
#define ch(x,i) tr[x].ch[i]
#define fail(x) tr[x].fail
} tr[N];

int tot, g[N][M];
string l, r;
void ins(int &now, int gl, int gr, int len, int tag=0) {
    if (!now) now = ++tot;
    if (!len) { g[now][0]++; return; }
    if (gl) {
        if (gr) {
            int L = l[l.size()-len]-'0', R = r[r.size()-len]-'0';
            if (L == R) ins(ch(now,L),1,1,len-1);
            else {
                ins(ch(now,L),1,0,len-1); ins(ch(now,R),0,1,len-1);
                for (int i = L+1; i < R; ++i) ins(ch(now,i),0,0,len-1);
            }
        } else {
            int L = l[l.size()-len]-'0'; ins(ch(now,L),1,0,len-1);
            for (int i = L+1; i < 10; ++i) ins(ch(now,i),0,0,len-1);
        }
    } else {
        if (gr) {
            int R = r[r.size()-len]-'0'; ins(ch(now,R),0,1,len-1);
            for (int i = tag; i < R; ++i) ins(ch(now,i),0,0,len-1);
        } else {
            if (tag) rep(i,10) ins(ch(now,i),0,0,len-1);
            else g[now][len]++;
        }
    }
}

queue<int> q;
int rt, n, dp[B][N];
void build() {
    rep(i,10) {
        if (ch(1,i)) q.push(ch(1,i)), fail(ch(1,i)) = rt;
        else ch(1,i) = rt;//缺的子直接指回根
    }
    while (!q.empty()) {
        int now = q.front(); q.pop();
        rep(i,M) g[now][i] += g[fail(now)][i];
        rep(i,10) {
            if (!ch(now,i)) ch(now,i) = ch(fail(now),i);
            else {
                fail(ch(now,i)) = ch(fail(now),i);
                q.push(ch(now,i));
            }
        }
    }
    rep1(i,tot) rep1(j,M-1) g[i][j] += g[i][j-1];
    rep(i,n+1) rep1(j,tot) dp[i][j] = -inf;
}

int f[B][N];
int main() {
    fast;
    cin >> l >> r >> n;
    if (l.size() == r.size()) ins(rt,1,1,l.size(),1);
    else {
        for (int i = l.size()+1; i < r.size(); ++i) ins(rt,0,0,i,1);
        ins(rt,1,0,l.size(),1);
        ins(rt,0,1,r.size(),1);
    }
    build(); dp[0][rt] = 0;
    rep(i,n) rep1(j,tot) {
        if (dp[i][j] < 0) continue;
        rep(z,10) {
            int to = ch(j,z);
            dp[i+1][to] = max(dp[i+1][to],dp[i][j]+g[to][min(M-1,n-i-1)]);
        }
    }
    int ans = -inf;
    rep1(i,tot) ans = max(ans, dp[n][i]);
    rep1(i,tot) f[n][i] = dp[n][i] == ans;
    cout << ans << '\n';
    for (int i = n-1; i; --i) rep1(j,tot) {
        if (dp[i][j] < 0) continue;
        rep(z,10) {
            int to = ch(j,z);
            f[i][j] |= dp[i+1][to]==dp[i][j]+g[to][min(M-1,n-i-1)] && f[i+1][to];
        }
    }
    int j = 1;
    rep(i,n) rep(z,10) {
        int to = ch(j,z);
        if (!f[i+1][to]) continue;
        if (dp[i+1][to] == dp[i][j]+g[to][min(M-1,n-i-1)]) {
            cout << z;
            j = to; break;
        }
    }
    return 0;
}