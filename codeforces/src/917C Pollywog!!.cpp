//
// Created by Psy.C on 2026/10/13.
//
/**
msk: 状态编号→位掩码; b: 位掩码→状态编号; c: 每种转移的花费
operator* —— 普通矩阵乘法（min-plus 变体）‍，即“取小”的矩阵乘，用于快速幂倍增：
operator/ —— 向量右乘（I/pw[j] 表示把当前行向量 I 乘一个转移矩阵），只更新第 1 行
tr：基础转移矩阵；
pw[27]：pw[i] = tr^(2^i)，即 tr 的 2 的幂次幂（用于倍增跳步）；
I：行向量（初始状态）
x：当前在一段内要移动的步数相关参数（注意变量名 x 同时被"位数为 x"复用，见下）；
k：状态窗口大小（k 位二进制）；
n：棋盘/总步数；
q：特殊位置（带额外花费的"石头"）的个数
__builtin_popcount(i) 统计 i 的二进制中 1 的个数。
对所有"1 的个数正好等于 x"的掩码 i 分配状态编号：b[i]（掩码→编号）、msk[编号]（编号→掩码），sz 递增
这是"滑动窗口"式的状态转移：窗口右移一位，若最右位是 1 则要把一个新的 1 补进来（可选位置 p，花费 c[p]）；若最右位是 0 则直接右移（免费）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 75;//状态数上限（状压出的合法状态数）

void chkmin(ll &x, ll y) { x = x < y ? x : y; }

int sz;//当前加入的状态数（压缩状态总数）
struct mat {
    ll a[N][N]{};
    mat() { memset(a, 0x3f, sizeof a); }
    mat operator*(const mat &x) const {
        mat y;
        rep(i,1,sz) rep(j,1,sz) rep(k,1,sz)
            chkmin(y.a[i][k],a[i][j]+x.a[j][k]);
        return y;
    }
    mat operator/(const mat &x) const {
        mat y;
        rep(i,1,sz) rep(j,1,sz)
            chkmin(y.a[1][j],a[1][i]+x.a[i][j]);
        return y;
    }
} tr, pw[27], I;

struct stone {
    int p, w;
    bool operator<(const stone &o) const { return p < o.p; }
} s[N];

int msk[N], b[1<<8], c[N];
map<int, int> mp;//位置→额外花费
int main() {
    fast;
    int x, k, n, q; cin >> x >> k >> n >> q;
    for (int i = 0; i < 1<<k; ++i)
        if (__builtin_popcount(i) == x)
            msk[b[i]=++sz] = i;
    rep(i,1,k) cin >> c[i];
    for (int i = 0; i < 1<<k; ++i) {
        if (!b[i]) continue;
        //最低位是 0：直接右移，花费 0
        if (i&1^1) { tr.a[b[i]][b[i>>1]] = 0; continue; }
        rep(p,1,k) {
            if (i>>p&1) continue;//该位已被占，跳过
            tr.a[b[i]][b[(i|1<<p)>>1]] = c[p];//最低位是 1：把 p 位变成 1，右移，花费 c[p]
        }
    }
    pw[0] = tr;
    for (int i = 1; 1<<i < n; ++i) pw[i] = pw[i-1]*pw[i-1];
    rep(i,1,q) cin >> s[i].p >> s[i].w, mp[s[i].p] = s[i].w;
    sort(s+1, s+q+1);
    //若最后一个石头没到终点 n，补一个位置 n 的哨兵
    if (s[q].p < n) s[++q] = {n}; I.a[1][1] = 0;//行向量初始：状态 1 处为 0（起点）
    for (int i = 1, cur = 1; i <= q; ++i) {//对每个特殊位置 s[i] 处理一段，cur 是当前已推进到的位置，初始为 1
        int to = min(n-x+1, s[i].p);//本段要推到的位置（不超过 s[i].p 与 n-x+1 的较小者）
        for (int j = 26; ~j; --j) {
            if (cur+(1<<j) > to-k) continue;//若这一大步会跳过有效范围，就跳过
            cur += 1<<j, I = I/pw[j];//跳 2^j 步，行向量乘上矩阵 pw[j]
        }
        while (cur < to) {
            mat nxt; memset(nxt.a, 0x3f, sizeof nxt.a);//每次重新构造一个小转移
            rep(j,1,sz) {
                int S = msk[j];
                if (S&1^1) {//最低位是 0：右移免费
                    chkmin(nxt.a[1][b[S>>1]], I.a[1][j]);
                    continue;
                }
                rep(p,1,k) {//最低位是 1：选位置 p 补 1
                    if (S>>p&1) continue;
                    //花费 = 已有代价 + 补位花费 c[p] + (当前位置是否为石头 ? 其额外花费 : 0)
                    ll t = I.a[1][j]+c[p]+(!mp.contains(cur+p) ? 0 : mp[cur+p]);
                    chkmin(nxt.a[1][b[(S|1<<p)>>1]], t);
                }
            }
            cur++, I = nxt;//推进 1 步
        }
    }
    cout << I.a[1][1] << '\n';//行向量回到状态 1（初始化状态的编号）的最小代价
    return 0;
}