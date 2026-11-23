//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
bool msk[1<<M][M][M];   // msk[状态][a][b]: 是否存在一个 "相邻 ab 且中间已删" 的冲突对
bool f[1<<M];           // f[状态]: 该状态(保留字母集合 V)下是否存在冲突
bool g[1<<M];           // g[状态]: 该状态能否作为"保留字母"集合被实现（无相互冲突）
int nxt[N][M];          // nxt[i][j]: 从 i 起下一个字符为 j 的位置（用于检查相邻关系）
int cnt[M];             // 每种字符在 s 中出现次数
bool ok[M][M];          // ok[i][j]: i,j 可否相邻
p ≤ 18 → 用 1<<p 位表示保留哪些字母。
统计每种字母数量，后面算"删除后剩余长度"时用 保留n−∑ 保留cnt
nxt[i][j] = 从位置 i 之后第一次出现字符 j 的位置（逆推，O(n⋅p)）。
用于判定"相邻关系"是否被中间未删字符隔开。
只看"相邻"位置
i（字符为 s[i]）与其后第一次出现字符 j 的位置。
若它们不相容（ok=0）且确实存在这样的 j，并且 字符 s[i] 的下次出现位置早于 j 的下次出现（即先遇到 s[i] 再遇 j）——排除反方向。
st = 在"i 和 j 之间"出现的字符集合（这些字符若保留就会夹在中间破坏直接相邻）。
调 dfs(st, s[i]-'a', j)：任何包含 st 中字符的保留状态都会让
ij 产生"中间夹了别的东西"的冲突。
DFS 的作用是向上传播：如果当前这个状态含冲突，那么任何"再保留更多字符"的超集也含冲突
msk[st][a][b] 记录"该三元组是否已检查/仍可达"避免重复。
一旦 st 有冲突，把 f[st]=0 打上标记；并且继续向超集递归打标记。
最终 f[状态] = 0 表示该保留字母集合内存在无法调和的两字符（需把中间所有都删光也不够）→ 不可保留。
简言之：f=1 表示该集合可以安全共存，f=0 表示有绊脚石冲突。
g[状态] = 该状态是否为"可被构造的合法保留集合"（无冲突且能逐步加入得到）。
从空集开始，只有 f 允许（无冲突）且不在集合中的新字母可加入 → 传播 g。
结果：g 为真的状态都是可以保留、且内部无冲突的字母集合
对每个合法保留集合
i：保留字母 j 的所有出现次 → 剩余长度 = n−∑ j∈i	cnt[j]。
取最小剩余长度——即"至少要留下（或等价问：最少删到多长）"。输出这个最小剩余长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;

constexpr int N = 1e5+5, M = 18, inf = 0x3f3f3f3f;

bool msk[1<<M][M][M], f[1<<M];
int p;
void dfs(int st, int a, int b) {
    if (!msk[st][a][b]) return;
    msk[st][a][b] = f[st] = 0;//标记不可保留 / 有冲突
    rep(i,p) if (!(st&(1<<i)) && i != a && i != b)
        dfs(st|(1<<i),a,b);//递归加入新字母，冲突仍存在
}

int n, nxt[N][M], cnt[M], q;
char s[N];
bool ok[M][M], g[1<<M];
int main() {
    fast;
    cin >> n >> p;
    memset(nxt,inf,sizeof nxt); memset(f,1,sizeof f);
    memset(msk,1,sizeof msk); q = 1<<p;
    cin >> s;
    rep(i,n) cnt[s[i]-'a']++;
    for (int i = n-2; i >= 0; i--) {
        rep(j,p) nxt[i][j] = nxt[i+1][j];
        nxt[i][s[i+1]-'a'] = i+1;
    }
    rep(i,p) rep(j,p) cin >> ok[i][j];
    rep(i,n) rep(j,p) {
        if (ok[s[i]-'a'][j] || nxt[i][j] == inf || nxt[i][s[i]-'a'] < nxt[i][j]) continue;
        int st = 0;
        rep(k,p) if (nxt[i][k] < nxt[i][j]) st |= 1<<k;
        dfs(st,s[i]-'a',j);
    }
    g[0] = 1;
    rep(i,q) if (f[i] && g[i])
        rep(j,p) if (!(i&(1<<j)) && f[i|(1<<j)])
            g[i|(1<<j)] |= g[i];
    int res = inf;
    rep(i,q) {
        if (!g[i]) continue;
        int sum = n;
        rep(j,p) if (i&(1<<j)) sum -= cnt[j];//保留集合内字母的字符被留下
        res = min(res, sum);//剩下 n - (保留字母总数) 是要删掉的
    }
    cout << res << '\n';
    return 0;
}