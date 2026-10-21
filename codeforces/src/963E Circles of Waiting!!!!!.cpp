//
// Created by Psy.C on 2026/10/21.
//
/**
二进制分解 b，逐位平方累乘
以 (r, r) 为圆心、半径 r 的圆。
判断点 (x, y) 是否落在圆内（含边界）：(x-r)² + (y-r)² ≤ r²
a[1..4]：四个方向的权重/概率输入。
p[1..4]：归一化后的四方向概率。
t：临时变量（模逆）。
ans[x][y]：从 (x,y) 出发的某种期望/概率答案。
num[x][k][l][b∈{0,1}]：转移/吸收概率的复杂状态数组
读入 r 与四个权重 a[1..4]。
用费马小定理：(a1+a2+a3+a4)^(mod-2) mod mod 即其模逆。
p[i] = a[i] * 逆元，使 p1+p2+p3+p4 ≡ 1 (mod 1e9+7)，即归一化为模意义下的概率分布
遍历 (0..2r)×(0..2r) 的整点，凡圆内点：
ans[x][y] = 1（先赋初值，后续累积转移贡献）。
若 (i+1,j) 在圆内：num[i][j][j][1] = p[3]。下标含义：num[起点x][k][l][b]，这里 k=l=j、b=1，记录从 (i,j) 向下（?）方向进入下一行某状态的起始概率 p[3]。
若 (i,j+1) 在圆内：num[i][j][j+1][0] = p[4]。
若 (i,j-1) 在圆内：num[i][j][j-1][0] = p[2]

行内消元转移（Gauss 式逐格消元)
同行多个未知数之间的高斯消元（把同行未知数逐个消去）‍：
对第 i 行每个圆内点 j，先求 t = 1 / (1 - num[i][j][j][0])（num[i][j][j][0] 是留在本点自身的系数，1-它 即离开本点的总概率，取其模逆）。
对第 i 行每个其他圆内点 k（k != j）：
用 j 这个"主元"去消 k：
num[i][k][l][0] += num[i][k][j][0] * num[i][j][l][0] * t：把 k 中经由 j 的转移合并进 k→l 的同行子转移（消 j 后 k 的转移被修正/吸收）。
num[i][k][l][1] += num[i][k][j][0] * num[i][j][l][1] * t：同理合并跨行(l→i+1 行)转移项。
ans[i][k] += num[i][k][j][0] * ans[i][j] * t：k 的答案吸收 j 的贡献。
消元完成后 num[i][k][j][0] = 0（清完 k 指向 j 的转移）

行间传递（向下推进到下一行）
把第 i 行处理完的信息通过"向下"的概率 p[1]（第 1 个方向）传递到下一行 i+1：
对每个同时在第 i、i+1 行的圆内点 j：
对 i+1 行每个圆内点 k：num[i+1][j][k][0] += p[1]*num[i][j][k][1] / (1-num[i][j][j][0])（从 i 行 j 点把跨行转移 num[·][·][1] 乘 p[1] 并归一化后，并入 i+1 行 j→k 的转移）。
ans[i+1][j] += p[1]*ans[i][j] / (1-num[i][j][j][0])：下一行答案吸收上一行贡献。
外层循环结束后，所有行间转移都已逐行向下推进

反向回推补全 ans
自下而上（i 从 2r 递减到 0）对每行圆内点 j：
对下一行 i+1 的每个圆内点 k：
ans[i][j] += num[i][j][k][1] * ans[i+1][k] / (1-num[i+1][k][k][0])：把下一行 k 点的答案通过跨行转移 num[·][·][1] 加权回传到当前行 j 点（除以下一行 k 点的留自身系数归一化）。
这一步利用之前保存的跨行转移，把底层答案逐层"反喂"回上层，最终补全所有圆内点的 ans

圆心点 (r, r) 作为起点，其真实答案还需除以它自身留着的系数 1 - num[r][r][r][0]（即乘其模逆），得到最终期望/概率。
输出 %mod 的结果


num[i][j][k][·] 的维度含义：i 是当前行，j 是"源/主元"点，k 是"目标"点，最后一维 0/1 区分别同行转移（仍留在第 i 行）与跨行下行转移（进入第 i+1 行）。第三段/第四段大量使用这两类系数做行间传递与回推。
check 只接受 int 坐标：所以枚举 0..2r 的整点，圆内的离散格点。
取逆都用费马小定理：(模 - 某值)^(mod-2) 求模逆，因为 1e9+7 是素数。
坐标是 0-based：循环 rep(i,r*2) 从 0 到 2r 含端点，把圆所有整点都覆盖到。
负号处理：mod+1-num[...][0] 相当于 (1 - num) mod mod（保证非负）。num[i][j][j][0] 表示点 j 从自己转移到自己的概率系数，1-它 是离开它的总概率，其逆用于归一化消元
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<=i##_end_; i++)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; i--)
#define ll long long
using namespace std;

constexpr int N = 101, mod = 1e9+7;

int ksm(ll a, int b) {
    ll ans = 1;
    while (b) {
        if (b&1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

ll r;
bool check(int x, int y) {
    if ((x-r)*(x-r)+(y-r)*(y-r) <= r*r) return true;
    return false;
}

ll a[5], p[5], t, ans[N][N], num[N][N][N][2];
int main() {
    fast;
    cin >> r >> a[1] >> a[2] >> a[3] >> a[4];
    t = ksm(a[1]+a[2]+a[3]+a[4], mod-2);
    for (int i = 1; i <= 4; i++) p[i] = (a[i]*t)%mod;
    rep(i,r*2) rep(j,r*2) if (check(i,j)) {
        ans[i][j] = 1;
        if (check(i+1,j)) num[i][j][j][1] = p[3];
        if (check(i,j+1)) num[i][j][j+1][0] = p[4];
        if (check(i,j-1)) num[i][j][j-1][0] = p[2];
    }
    rep(i,r*2) {
        rep(j,r*2) if (check(i,j)) {
            t = ksm(mod+1-num[i][j][j][0], mod-2);
            rep(k,r*2) if (j != k && check(i,k)) {
                rep(l,r*2) {
                    if (j != l && check(i,l))
                        num[i][k][l][0]=(num[i][k][l][0]+(num[i][k][j][0]*num[i][j][l][0])%mod*t)%mod;
                    if (check(i+1,l))
                        num[i][k][l][1]=(num[i][k][l][1]+(num[i][k][j][0]*num[i][j][l][1])%mod*t)%mod;
                }
                ans[i][k]=(ans[i][k]+(num[i][k][j][0]*ans[i][j])%mod*t)%mod;
                num[i][k][j][0] = 0;
            }
        }
        rep(j,r*2) if (check(i,j) && check(i+1,j)) {
            rep(k,r*2) if (check(i+1,k))
                num[i+1][j][k][0]=(num[i+1][j][k][0]+
                    (p[1]*num[i][j][k][1])%mod*ksm(mod+1-num[i][j][j][0], mod-2))%mod;
            ans[i+1][j]=(ans[i+1][j]+(p[1]*ans[i][j])%mod*ksm(mod+1-num[i][j][j][0], mod-2))%mod;
        }
    }
    per(i,r*2,0) rep(j,r*2) if (check(i,j)) {
        rep(k,r*2) if (check(i+1,k))
            ans[i][j]=(ans[i][j]+(num[i][j][k][1]*ans[i+1][k])%mod*ksm(mod+1-num[i+1][k][k][0], mod-2))%mod;
    }
    cout << (ans[r][r]*ksm(mod+1-num[r][r][r][0], mod-2))%mod;
    return 0;
}