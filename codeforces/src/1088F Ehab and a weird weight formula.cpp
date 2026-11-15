//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
对非根结点 x：
遍历 i=0..19（倍增二级跳）：
fa[x][i] 先由两段 2^(i-1) 拼出（fa[fa[x][i-1]][i-1]）。
计算通过 fa[x][i]（第 i 级祖先）连接时的代价：(i+1) * v[fa[x][i]] + v[x]，即从祖先往下返回到 x 经过 (i+1) 条边，每条边代价为该祖先权值 v，加上 x 自身权值。用 chkmin 更新 z。
把 z 累加进 ans——x 选它所有祖先中代价最小的路径。
根 rot：倍增表都指向自己。
递归遍历儿子建立倍增亲子关系，fa[now][0] = x
读入建树、从最小权根开始 DFS，输出累加的最小总代价 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 5e5+5, M = 1e6+5;
constexpr ll inf = 1e17;

inline void chkmin(ll &a, ll b) { if (b < a) a = b; }

int tot, head[N], d[M], nxt[M];
inline void add(int f, int w) {
    d[++tot] = w, nxt[tot] = head[f], head[f] = tot;
    d[++tot] = f, nxt[tot] = head[w], head[w] = tot;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, rot, v[N];
void init() {
    n = rd(), rot = 1;
    rep(i,1,n) {
        v[i] = rd();
        if (v[i] < v[rot]) rot = i;//选权值最小的点作根 rot
    }
    rep(i,2,n) add(rd(),rd());//读 n-1 条边
}

int fa[N][20];
ll ans;
void dfs(int x) {
    ll z = inf;
    if (x != rot) {
        rep(i,0,19) {
            if (i) fa[x][i] = fa[fa[x][i-1]][i-1];
            chkmin(z,1ll*(i+1)*v[fa[x][i]]+v[x]);//第 i 级祖先的贡献
        }
        ans += z;//x 的最小向上连接代价
    } else rep(i,0,19) fa[x][i] = x;//根：所有祖先都是自己
    for (int i = head[x]; i; i = nxt[i]) {
        int now = d[i];
        if (now == fa[x][0]) continue;
        fa[now][0] = x, dfs(now);//记录父关系
    }
}


int main() {
    fast;
    init(); dfs(rot);
    cout << ans << '\n';
    return 0;
}