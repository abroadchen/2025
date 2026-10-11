//
// Created by Psy.C on 2026/10/11.
//
/**
把字符串数字反转存进 a[1..n]，即 a[i] 是从低位到高位的第 i 位数字
实现 "整数 + 1"：
从低位（a[1]）开始，连续遇到 9 就把它清 0 并进位；
第一个非 9 位加 1；
若全部是 9（如 999→1000），则位数 n 加 1。
最后 reverse，得到从高位到低位的 a[1..n]，即 a 重新代表"原数 +1"之后的各位数字（高位在前）
pw[i][j] = (100 - 9j)^i mod。
这个 100-9j 的由来通常是对"两个 digit 的某种配对"计数：100 是两位数的全部 100 种组合，9j 是"两位值相同的数字"（比如 00..99 有 10 对相等的）中被排除的对数；100-9j 是"差的绝对值满足某条件"的配对数量
外层 i 遍历每一位（高位→低位）‍。
idx[j]：统计已经处理过的更高位中，数字 ≥ j 的个数。
对内层 j=1..9 累加一个贡献，然后更新 idx[j]
pw[idx[j]][10] 和 pw[n-i][j] 都是某种"后缀/前缀计数"的幂。
10*max(a[i]-j,0) + min(a[i],j)：这是对第 i 位取不同值时，与数字 j 的关系做分情况处理——max(a[i]-j,0) 表示第 i 位能取到比 j 大的值的种数，min(a[i],j) 表示能取到 ≤ j 的值的种数。
减去的那一项 a[i]*pw[n-i][10] 表示"第 i 位为固定 a[i]"的总方案数贡献。
这是一个典型的三重思路：对每一个"数位对"（位 i 与数字阈值 j）分别统计其对本位取值的贡献，再减去固定取值时的基线，从而只保留"与第 i 位取值相关"的净增量
inf = 111111112；最后 ans * inf mod 再取正。
由于前面累加里混入了负数（(ans + ...) %= mod 可能得到负数），这里 +mod 保证结果非负。
*inf mod（inf 是 9 的逆元相关？111111112 是 5^9 之类）通常是用来"约掉"累加过程中多乘的某个因子，把中间计数还原成最终答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
#define ll long long
using namespace std;

constexpr int N = 705, mod = 1e9+7, inf = 111111112;


char s[N];
int n, a[N];
ll pw[N][11], ans;
int main() {
    fast;
    cin >> s, n = strlen(s);
    rep(i,1,n) a[i] = s[n-i] - 48;
    int x = 1;
    while (a[x] == 9) a[x++] = 0;
    a[x]++;
    if (x > n) n++;
    reverse(a+1, a+n+1);
    rep(i,1,10) pw[0][i] = 1;
    rep(i,1,n) rep(j,1,10) pw[i][j] = pw[i-1][j]*(100-9*j)%mod;
    int idx[11]{};
    rep(i,1,n) rep(j,1,9) {
        (ans += pw[idx[j]][10]*pw[n-i][j]%mod*(10*max(a[i]-j, 0)+
            min(a[i], j)) - a[i]*pw[n-i][10]) %= mod;
        idx[j] += a[i] >= j;
    }
    cout << (ans*inf%mod+mod)%mod;
    return 0;
}