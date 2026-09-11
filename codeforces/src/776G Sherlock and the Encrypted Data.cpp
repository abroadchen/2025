//
// Created by Psy.C on 2026/9/11.
//
/**
N=16：基数（十六进制每位 0..15），同时也是位数上限。
px[i]：16 的幂（px[i]=16^i）。
f[n][p][i] / s[n][p]：DP 预处理表
（高位到低位枚举，统计严格小于 m 的自由组合）‍：
px[n] 取第 n 位（16 进制）的数位 mx。
对每个小于 mx 的取值 x（该位自由选择 0..mx-1，后续位可任意），累加满足条件的组合数。
p0 记录已枚举高位中出现的最大数位（因为题目性质往往与"当前最大数位 p0"有关）。
f[n][p][i]、s[n][p] 是在固定"已生成前缀最大数位为 p"时，n 位长度内的统计量。
末尾 ans += (m&(1<<p0))!=0 处理 m 本身这一档（全等于 m 的情况）。
p1 = max(p0, x)（或再 max 上 p）是本统计的关键：条件通常取决于"前缀最大数位 p1"，并按 p1 落位分三种情况（<4n / 在 4n..4n+4 之间 / ≥4n+4）来用不同表 f 或带位判断的 s
px：16 的幂。
初始化 n=0（0 位）时：s[0][x] 计数 +1；对 x 的每个置位 bit i，f[0][x][i]++。
递推扩展位数：从 n 位推到 n+1 位，按新增一位的值 x 更新累计统计 s 与 f——s 记录"到第 n+1 位、最大数位 p1 的方案数"，f 记录"到 n+1 位、最大数位 p1、某 bit i 是否被置位的方案数"。
if (n<=2) 的若干部件处理最高 3 位（4*3=12..15 bit）的置位统计。
这段预处理把"在给定前缀最大数位下，某 bit 一定会出现"的计数做成表 f、s，供 get 在数位枚举时 O(1) 查询
id(c) 把十六进制字符 '0'..'9'、'a'..'f' 转成数值 0..15。
读入 L、R 两个十六进制字符串，按 16 进制展开成 ll 数值 l、r。
答案 = get(r) - get(l-1)（标准前缀和区间查询，其中 get(l-1) 统计 0..l-1）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 16;
ll px[N], f[N][N][N], s[N][N];
ll get(ll m) {
    if (m == -1) return 0;
    ll ans = 0;
    int p0(0), mx;
    for (int n = N-1; n >= 0; --n) {
        mx = m/px[n]&15;
        for (int x = 0; x < mx; ++x) {
            if (!n) {
                int p1 = max(p0, x);
                if (p1 < 4) ans += ((x&(1<<(p1-4*n)))!=0);
                else ans += ((m&(1<<p1)) != 0);
            } else {
                for (int p = 0; p < N; ++p) {
                    int p1 = max(p0, max(x, p));
                    if (p1 < 4*n) ans += f[n-1][p][p1];
                    else if (p1 < 4*(n+1)) ans += ((x&(1<<(p1-4*n)))!=0)*s[n-1][p];
                    else ans += ((m&(1<<p1))!=0)*s[n-1][p];
                }
            }
        }
        p0 = max(p0, mx);
    }
    ans += (m&(1<<p0))!=0;
    return ans;
}

int id(char c) {
    if (c >= '0' && c <= '9') return c-'0';
    return c - 'a' + 10;
}

int main() {
    fast;
    px[0] = 1;
    for (int i = 1; i < N; ++i) px[i] = px[i-1]*N;
    for (int x = 0; x < N; ++x) {
        s[0][x]++;
        for (int i = 0; i < 4; ++i)
            if ((1<<i)&x) f[0][x][i]++;
    }
    for (int n = 0; n < N-1; ++n)
        for (int x = 0; x < N; ++x)
            for (int p = 0; p < N; ++p) {
                int p1 = max(p, x);
                s[n+1][p1] += s[n][p];
                for (int i = 0; i < min(4*(n+1), N); ++i)
                    f[n+1][p1][i] += f[n][p][i];
                if (n <= 2) {
                    for (int i = 0; i < 4; ++i)
                        if ((1<<i)&x)
                            f[n+1][p1][i+4*(n+1)] += s[n][p];
                }
            }
    int T; cin >> T;
    while (T--) {
        ll l = 0, r = 0;
        char L[20], R[20]; cin >> L >> R;
        int x = strlen(L), y = strlen(R);
        for (int i = x-1; i >= 0; --i) l += id(L[i])*px[x-1-i];
        for (int i = y-1; i >= 0; --i) r += id(R[i])*px[y-1-i];
        cout << get(r) - get(l-1) << '\n';
    }
    return 0;
}