//
// Created by Psy.C on 2026/9/30.
//
/**
N=2010：数据和规模上限。
mod=998244353：常用 NTT 质数，取模用。
P=11：核心模数，本题所有和值都在模 11 下计数（因为 10 ≡ -1 (mod 11)，处理可被 11 整除的整数重排问题）
组合数查表函数，带越界保护（n<m 或负数返回 0）
预处理 0..N-1 的阶乘和组合数表
f[now][j][k]：处理完前 i 个数后，选中 j 个数放"正侧"、且选中侧的和与未选中侧的和之差为 k (mod 11) 的方案数。
转移：第 i 个数
不选（放负侧/未选侧）：差 k 由 (k - a[i]) 转移而来【因为负侧加 a[i] 会使差减少】。
选（放正侧）：差 k 由 (k + a[i]) 转来，且选中个数 +1。
滚动数组只保留 i&1 两层，省空间。
结尾乘 fac[j]*fac[n-j]：把选出的 j 个和未选的 n-j 个各自做排列（因为同一侧内部顺序任意），把"组合计数"变成"排列计数"
读入 n 个数，按十进制位数奇偶分成两组：
位数奇数 → a 组（数量 c1）；
位数偶数 → b 组（数量 c2）。
只保留每个数 mod 11 的余数（因为只需模 11 的和）。
分别对两组做背包 get，得 f（A 组）和 g（B 组）。
（奇偶分组是因为：在最终的排列中，奇数位数字和偶数位数字的贡献符号相反——位权交替 ±1，而 10 的奇数次方 ≡ ±1 mod 11，最终"被 11 整除"取决于奇偶位数字和第二项。）
c = c1/2：A 组中放到"正号侧"的个数（通常奇数位数字里，正负侧个数由奇偶位数决定）。

若 c1=0（全是偶数位数字），直接用 B 组结果 g[c2&1][0][0] 输出（把偶数位数字一字排开，考虑首尾正负），并 continue。

否则枚举 B 组选 j 个放正侧、且 B 组贡献为 k (mod 11)，则：

A 组必须贡献 -k (mod 11) 才能和值为 0 → 查 f[c1&1][c][(P-k)%P]；
用两个组合数 C 把两组数字插入到各自异构位的位置槽中去（星条组合：正侧槽数、负侧槽数），计算排列方式数；
累加所有 (j,k) 组合得到最终答案 ans。
这里两个 C(a+b-1, b-1) 是隔板法：把 j 个 B 组正侧数、以及剩余 B 组负侧数，分别插入对应侧的数量固定的"槽"中，统计分布方式。具体组合数中的 (c1-c)、(c+1) 来自正/负侧可放的位置数（由奇偶位固定槽位决定）。

滚动数组维度：f[2][N][12]、g[2][N][12]，f[n&1] 表示取最后处理层。
(k-a[i]+P)%P 保证模 11 下负数转成正余数。
fac[j]*fac[n-j] 在 get 末尾统一乘上，实现从"组合"到"排列"的切换
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
using namespace std;
constexpr int N = 2e3+10, mod = 998244353, P = 11;

int cc[N][N];
int C(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return cc[n][m];
}

int fac[N];
void get(int n, int a[], int f[][N][12]) {
    f[0][0][0] = 1;
    rep(i,1,n) {
        int now = i&1;//滚动数组第 i 层
        rep(j,0,i) rep(k,0,P-1) {
            //不选第 i 个（a[i] 放"负号侧"或该侧），维持
            f[now][j][k] = f[now^1][j][(k-a[i]+P)%P];
            //选第 i 个（放"正号侧"）
            if (j) f[now][j][k] = (f[now][j][k]+f[now^1][j-1][(k+a[i])%P])%mod;
        }
    }
    rep(j,0,n) rep(k,0,P-1) {//乘上阶乘：给选中/未选中的位置做排列
        f[n&1][j][k] = 1ll*f[n&1][j][k]*fac[j]%mod*fac[n-j]%mod;
    }
}

int n, c1, c2, f[2][N][12], g[2][N][12], a[N], b[N];
int main() {
    fast;
    int T; cin >> T; fac[0] = 1;
    rep(i,1,N-1) fac[i] = 1ll*fac[i-1]*i%mod;
    rep(i,0,N-1) {
        cc[i][0] = cc[i][i] = 1;//边界 C(i,0)=C(i,i)=1
        rep(j,1,i-1) cc[i][j] = (cc[i-1][j]+cc[i-1][j-1])%mod;//杨辉三角
    }
    while (T--) {
        cin >> n; c1 = c2 = 0;
        memset(f, 0, sizeof f); memset(g, 0, sizeof g);
        rep(i,1,n) {
            int x = 0, len = 0, rem; cin >> x, rem = x;
            while (x) len++, x/=10;
            if (len&1) a[++c1] = rem%P;
            else b[++c2] = rem%P;
        }
        get(c1, a, f); get(c2, b, g);
        int ans = 0, c = c1/2;
        if (!c1) {
            cout << g[c2&1][0][0] << '\n';
            continue;
        }
        rep(j,0,c2) rep(k,0,P-1) {
            ans = (ans + 1ll
                *C(j+(c1-c)-1, (c1-c)-1) //组合：把 B 组选 j 个插到"正号侧"位置里
                *C((c2-j)+(c+1)-1,(c+1)-1) //组合：剩余 B 组插到"负号侧"位置里
                %mod
                *f[c1&1][c][(P-k)%P] //A 组：恰选 c 个正、贡献为 -k
                %mod
                *g[c2&1][j][k] //B 组：恰选 j 个正、贡献为 k
                %mod)%mod;
        }
        cout << ans << '\n';
    }
    return 0;
}