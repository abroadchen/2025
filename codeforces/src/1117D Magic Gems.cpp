//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
b：递推转移矩阵（乘一次 = 递推一步）。
a：初始行向量/矩阵（状态初值）。
核心逻辑 while(n){ if(n&1) a=a*b; b=b*b; n>>=1; }：标准矩阵快速幂，求 a * b^n（即推进 n 步），最后答案取 a.num[1][1]。
快速幂中 a 实际承担“结果累积器”的作用，b 是自乘的底数
前面 m 行都取 −1，配合 a.num[1][m+1]= -1 这类补偿系数，实现带交替/相消的递推式
rep(i,2,m) b.num[i-1][i]=1 是标准移位置，表示把高阶项映射为下一状态（伴随矩阵的经典结构）。
末尾两行 (m+1、m+2) 用于处理常数项求和（把累计和/边界常数塞进状态），这是带“求和/前缀和”递推的常用增广技巧
a 是 1×(m+2) 的行向量（初始状态）。
第 m+2 位（常数列）=1，第 1 位=1（a1初值），第 m+1 位=1（某个边界/累积初值）。
各维初值与 b 的设计对应，共同决定递推初值条件
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i <= k; i++)
#define int long long
using namespace std;

constexpr int N = 110, mod = 1e9+7;

struct node {
    int num[N][N]; int len;
    node operator*(node o) const {
        node ans{};
        memset(ans.num, 0, sizeof(ans.num));
        rep(i,1,len) rep(j,1,len) rep(k,1,len) {
            ans.num[i][j] += num[i][k]*o.num[k][j];
            ans.num[i][j] %= mod;
        }
        ans.len = len;
        return ans;
    }
} a, b;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


signed main() {
    fast;
    int n = rd(), m = rd()-1; a.len = m + 2; b.len = m + 2;
    memset(a.num, 0, sizeof(a.num));
    a.num[1][m+2] = 1; a.num[1][1] = 1; a.num[1][m+1] = 1;
    memset(b.num, 0, sizeof(b.num));
    rep(i,1,m) b.num[i][m+1] = -1;
    b.num[m+1][m+1] = 2; b.num[m+2][m+1] = 1; b.num[m+2][m+2] = 1;
    rep(i,2,m) b.num[i-1][i] = 1;
    rep(i,1,m) b.num[i][1] = -1;
    b.num[m+2][1] = b.num[m+1][1] = 1;
    while (n) {
        if (n&1) a = a*b;
        b = b*b;
        n >>= 1;
    }
    cout << a.num[1][1] << '\n';
    return 0;
}