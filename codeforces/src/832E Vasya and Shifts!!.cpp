//
// Created by Psy.C on 2026/9/25.
//
/**
K = 5：整个运算在模 5 的有限域上进行（最核心的点）。
N=510, M=810：数组上限，说明向量长度 m ≤ 810，向量个数 n+q ≤ 510（行列关系见下）。
mod = 1e9+7：用于 ksm（快速幂）——注意这里求的是大质数 mod 下的答案，不是模 5 的答案
在 mod = 1e9+7 下做快速幂，用于计算 5 的某次幂（见下面的 ans = ksm(K, ...)）
在模 5 下，求 1-4 的乘法逆元。
因为 1,2,3,4 的逆元分别是 1,3,2,4，而 i^3 mod 5：
1³=1 → 1
2³=8≡3 → 2 的逆元是 3 ✓
3³=27≡2 → 3 的逆元是 2 ✓
4³=64≡4 → 4 的逆元是 4 ✓
用 i³ mod 5 来求逆元，是模 5 域的一个特殊简化（因为费马小定理 i^{p-2}=i^3，p=5）
把向量转置存储：a[j][i] 表示"第 j 维（字母位）的第 i 个向量"。
每行读入一个长度为 m 的字符串（每个字符对应模 5 里的一个值，s[j]-'a' 映射 0-4）。
第 i 个原向量存进 a[·][i]（i=1..n）。
第 i 个查询向量存进 a[·][i+n]（i=1..q）。
因此矩阵是 m 行 × (n+q) 列，行 = 维度，列 = 向量。这种转置让高斯消元按列主元进行
按列的高斯消元 / 求秩过程，行为"主元索引 i"、列为"向量索引 pos"：

while(pos<=n)：找列主元——在当前列 pos 上找一个非零行 i（用 swap(a[j], a[i]) 交换整行/列维度的数组，把非零的调到第 i 行）。
若第 i 维上没有非零（a[i][pos]==0），pos++ 跳到下一列继续找。
若 pos > n（列搜完，已没有可消元素），则求秩完毕，此时剩下 n-i+1 个自由列，生成空间大小为 5^{n-i+1}，用它计算答案 ans = ksm(K, n-i+1)（在 mod 1e9+7 下）。
找到主元 a[i][pos]（模5下为 1-4 的非零元），用它消去下方所有行该列的值：
t = a[j][pos] * iv[a[i][pos]] % K 是消元系数（模5逆元）。
对 k = pos..n+q 整行做 a[j][k] -= t*a[i][k]（模5，注意用 +K 保证非负）。
这段同时对 原向量和后面的查询向量 一起放在矩阵里消元——这是高斯消元求"查询向量能否线性表出"的经典技巧：把待测向量并排加入，消元后看它是否变成全 0（若变全 0 说明可被表出）。
对每个查询向量 i（列，n+1..n+q）：
cnt：统计原向量部分（列 1..n）在第 j 维度上非零的个数。
若某维度 j 上，所有原向量在该维都是 0（cnt==0，即该维是自由维/未被主元占据），但查询向量在该维非零（a[j][i] != 0）→ 说明查询向量含有原向量张成空间之外的分量，不能被线性表出，置 t=0。
否则 t 保持为 ans（生成空间大小）。
对每个查询输出 t。
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 510, M = 810, K = 5, mod = 1e9+7;
int ksm(int x, int k) {
    int res = 1;
    while (k) {
        if (k&1) res=res*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return res;
}

int n, m, a[N][M], q, ans, iv[K];
char s[N];
signed main() {
    for (int i = 1; i < K; ++i) iv[i] = i*i*i%K;
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s+1);
        for (int j = 1; j <= m; ++j)
            a[j][i] = s[j] - 'a';
    }
    q = read();
    for (int i = 1; i <= q; ++i) {
        scanf("%s", s+1);
        for (int j = 1; j <= m; ++j)
            a[j][i+n] = s[j] - 'a';
    }
    for (int i = 1, pos = 1; pos <= n; ++i) {
        while (pos <= n) {
            for (int j = i+1; j <= m; ++j)
                if (a[j][pos] > 0) swap(a[j], a[i]);
            if (a[i][pos]) break;
            pos++;
        }
        if (pos > n) { ans = ksm(K, n-i+1); break; }
        for (int j = i+1; j <= m; ++j)
            if (a[j][pos] != 0) {
                int t = a[j][pos]*iv[a[i][pos]]%K;
                for (int k = pos; k <= n+q; ++k)
                    a[j][k] = ((a[j][k]-t*a[i][k])%K+K)%K;
            }
    }
    for (int i = n+1; i <= n+q; ++i) {
        int t = ans;
        for (int j = 1, cnt = 0; j <= m; ++j, cnt=0) {
            for (int k = 1; k <= n; ++k) cnt += a[j][k] > 0;
            if (!cnt && a[j][i]) t = 0;
        }
        cout << t << '\n';
    }
    return 0;
}