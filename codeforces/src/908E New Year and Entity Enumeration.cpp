//
// Created by Psy.C on 2026/10/11.
//
/**
标准的杨辉三角 / 组合数 c[i][j] = C(i,j)
f[i] = 第 i 个贝尔数（Bell number）‍，即把 i 个元素划分成若干非空子集的划分数
m：列数，n：行数。
读入 n 个长度为 m 的 01 串，存成 bitset a[1..n]，a[i][j]=1 表示第 i 行第 j 列为 1。
M 是全 1 的 mask（位数设为 m）
对每一列 i 计算一个 bitset b[i]：

对第 i 列，遍历每一行 j：
如果 a[j][i] == 1（第 j 行第 i 列为 1），则 b[i] &= a[j]（保留与 a[j] 都为 1 的位）；
否则（该行第 i 列为 0），b[i] &= (a[j] ^ M)，即取 a[j] 的按位取反后再与。
这样 b[i] 的第 k 位为 1，当且仅当 对于所有行 j，a[j][i] == a[j][k]，即第 k 列与第 i 列完全相同（两列在整个矩阵中相等）。

也就是说：b[i] 标记了"所有与第 i 列相等的列"（包括列 i 自己）。这就是把 m 列按"列向量是否完全相同"分组
v[] 标记某列是否已被归入某个组。
遍历列 i，如果列 i 尚未被标记"已使用"（即它是某个等价类的代表），则：
数出 b[i] 中所有未标记的列 j（num++），这些列与列 i 相同，属于同一组。
把这组列标记为已用。
然后把 res *= f[num]，其中 f[num] = Bell(num)，即这组里 num 列能产生的划分方案数。
最终答案 = 各组（相同列的等价类）的 Bell 数之积，即 res = Π f[size of each unique-column class]
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=j; i<=k; i++)
using namespace std;

constexpr int N = 1100, mod = 1e9+7;

inline void add(int& a, const int& b) {
    a += b;
    if (a >= mod) a -= mod;
}

int c[N][N], f[N], m, n;
bitset<N> M, a[N], b[N];
char str[N];
bool v[N];
int main() {
    c[0][0] = 1;
    rep(i,1,N-1) {
        c[i][0] = 1;
        rep(j,1,i) c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
    }
    f[0] = 1;
    rep(i,1,N-1) rep(j,0,i-1) add(f[i], 1ll*c[i-1][j]*f[i-1-j]%mod);
    scanf("%d%d",&m,&n); M.set();
    rep(i,1,n) {
        scanf("%s", str+1);
        rep(j,1,m) if (str[j] == '1') a[i][j] = 1;
    }
    rep(i,1,m) {
        b[i] = M;
        rep(j,1,n) {
            if (a[j][i]) b[i] &= a[j];
            else b[i] &= (a[j]^M);
        }
    }
    int res = 1;
    rep(i,1,m) {
        int num = 0;
        rep(j,i,m) if (b[i][j] && !v[j])
            num++, v[j] = true;
        res = 1ll*res*f[num]%mod;
    }
    printf("%d\n",res);
    return 0;
}