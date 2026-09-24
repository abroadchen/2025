//
// Created by Psy.C on 2026/9/23.
//
/**
nxt[N][N]：为所有起点 k 分别保存一份 KMP 的 next 数组（二维）。
s：输入字符串
对每个起点 k，用标准的 KMP 算法构建针对子串 s[k..] 的 next 数组。
注意这里 nxt[k][i] 表示：以 k 为起点、当前位置为 i 时，失配后要跳转到的位置（j）。起点 k 对应的"空"位置（k-1）作为虚拟起点。
这份预处理是后面快速判断循环节用的。
返回整数 x 的十进制位数。用它来算"重复次数 x 需要写几个数字"
对子串 s[i..j]（长度为 L = j-i+1），利用 KMP 的一个经典性质：
最小循环节长度 = L - next[L]
这里通过差值得出循环节长度 x。
如果 L % x != 0，说明无法整除，循环节不成立，直接返回整个长度 L。
否则返回最小循环节 x。
简单说：给定一段区间，算出它能以多短的循环节重复构成
x == y：长度为 1，无法压缩，返回 2（这是 DP 边界，表示单个字符要占 2 个...实际是无意义压缩，仅作为 DP 的初始选择）。
否则：
t = 该区间 [x, y] 的最小循环节长度。
xh = 区间长度 ÷ 循环节长度 = 重复次数。
返回 t + get(xh)：即 "循环节长度 + 次数占的位数"，这就是把该区间写成 (循环节)^次数 的压缩总长度。
dp[i]：表示前 i 个字符被压缩表示后的最短长度。
转移：枚举最后一段的起点 j+1，把 dp[j]（前 j 个字符的最优）加上 solve(j+1, i)（最后一段压缩后的长度）取最小。
dp[0] = 0 是边界。
最后输出 dp[n]，即整个字符串压缩后的最短长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 8e3+10;
int len, nxt[N][N];
char s[N];
void kmp() {
    for (int k = 0; k < len; ++k) {
        nxt[k][k] = k-1;
        int j = k-1, i = k;
        while (i < len) {
            if (j == k-1 || s[i] == s[j]) {
                j += 1; i += 1;
                nxt[k][i] = j;
            } else j = nxt[k][j];
        }
    }
}

int get(int x) {
    int res = 0;
    while (x) { res += 1; x /= 10; }
    return res;
}

int calc(int i, int j) {
    int x = j-i+1-(nxt[i][j+1]-(nxt[i][i]+1));
    if ((j-i+1)%x) return j-i+1;
    return x;
}

int solve(int x, int y) {
    if (x == y) return 2;
    int t = calc(x-1, y-1), xh = (y-x+1)/t;
    return t + get(xh);
}

int dp[N];
int main() {
    fast;
    cin >> s; len = strlen(s); kmp();
    memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
    int n = strlen(s);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j+1 <= i; ++j)
            dp[i] = min(dp[i], dp[j]+solve(j+1, i));
    cout << dp[n] << '\n';
    return 0;
}