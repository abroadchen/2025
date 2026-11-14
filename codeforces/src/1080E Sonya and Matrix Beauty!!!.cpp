//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
B=31：哈希用的进制（字母集 1..26，31 为质数个基）。
u1, u2：拼接回文串时两端用的哨兵值，防止越界比较。
a[i][j]：字符转数字 1..26。
v[i][j]：行内的前缀异或（按位掩码，记录某行某段字母出现奇偶性）。
pw：进制幂 B^i（用于哈希）。
th/h：行哈希。
c/p：Manacher 用的"扩展串"和回文半径
v[i][j] 是行 i 前 j 个字符的字母出现奇偶性掩码。所以 v[i][j] ^ v[i][k-1] 就是行 i 在列 [k, j] 区间内每个字母出现奇偶性的掩码，__builtin_popcount 表示其中出现奇数次的不同字母数
pw[1..26] = B^1..B^26
固定列区间 [i, j]，对每行动态维护其子串哈希 th[k]（通过字母出现次数按 B 加权），随右边界扩展逐步累加。
剪枝条件：若某行在 [i,j] 内出现奇数次的字母超过 1 个，则 h[k]=0（该行不参与后续计数，因为"行内两两成对回文"要求至多一种出现奇数次——即该行这个区间本身要能构成某种对称/回文结构）。否则 h[k] = th[k]（有效哈希）
把连续有效行的哈希值 h 串起来，中间用 0 分隔、两端放哨兵 u1/u2，跑标准 Manacher 求各位置回文半径 p[k]，每个半径 p[k] 的回文包含 p[k]/2 个以该位置为中心的回文子结构，累加到 res
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ull unsigned long long
using namespace std;

constexpr int N = 300;
constexpr ull u1 = 1145141919810, u2 = 1919810114514, B = 31;

int n, m, a[N][N], v[N][N], ct[N][30], len, p[N<<1], res;
string s;
ull pw[N], th[N], h[N], c[N<<1];
void solve() {
    cin >> n >> m;
    rep(i,n) {
        cin >> s; s = " " + s;
        rep(j,m) {
            a[i][j] = s[j] - 'a' + 1;
            v[i][j] = (1<<(a[i][j]-1))^v[i][j-1];
        }
    }
    pw[0] = 1;
    rep(i,26) pw[i] = pw[i-1]*B;
    rep(i,m) {//左边界 i
        rep(j,n) th[j] = 0;//清空每行哈希
        rep(j,n) rep(k,26) ct[j][k] = 0;//清空每行各字母计数
        for (int j = i; j <= m; j++) {//右边界 j（向右扩展）
            rep(k,n) {//对每一行
                th[k] -= ct[k][a[k][j]]*pw[a[k][j]];//移除旧贡献
                ct[k][a[k][j]]++;
                th[k] += ct[k][a[k][j]]*pw[a[k][j]];//加入新贡献 -> 更新哈希
                if (__builtin_popcount(v[k][j]^v[k][i-1]) > 1) h[k] = 0; else h[k] = th[k];
            }
            rep(l,n) {
                if (!h[l]) continue;//跳过无效行
                int r = l;
                while (r < n && h[r+1]) r++;//找一段连续有效行 [l, r]
                c[len=1] = u1, c[++len] = 0;//构造 Manacher 扩展串（哨兵 u1）
                for (int k = l; k <= r; k++) c[++len] = h[k], c[++len] = 0;
                c[++len] = u2;//尾部哨兵 u2
                //—— 标准 Manacher ——
                rep(k,len) p[k] = 0;
                int mid = 0, mr = 0;
                for (int k = 2; k < len; k++) {
                    if (k <= mr) p[k] = min(mr-k+1,p[2*mid-k]); else p[k] = 1;
                    while (c[k-p[k]] == c[k+p[k]]) p[k]++;
                    if (k+p[k] > mr) mr = k+p[k]-1, mid = k;
                }
                for (int k = 2; k < len; k++) res += p[k]/2;//统计回文对
                l = r;
            }
        }
    }
    cout << res << '\n';
}


int main() {
    fast;
    solve();
    return 0;
}