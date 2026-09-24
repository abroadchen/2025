//
// Created by Psy.C on 2026/9/23.
//
/**
第一轮基数排序初始化 sa。
每轮 j 倍增：用第二关键字 y 和第一关键字 x 基数排序合并排名，直到所有后缀排名唯一（p>=n）或 j>n。
这是 O(n log n) 倍增构建 SA 的经典写法
rk[i]：第 i 个后缀的排名。
h[rk[i]]：相邻排名后缀的最长公共前缀（LCP），用经典的 k-- 性质线性求出（da 算法）
建 ST 表，对 h[] 做区间最小值查询
区间最小值的 O(1) 查询
任意两个后缀的 LCP = 二者排名区间 [L+1, R] 内 h 值的最小值（ST 表查询）
把 A 和 B 拼成一个长串 l+1，中间用 1 分隔、结尾用 0 分隔，字符集映射到 [2, 27]（所以 m=60 覆盖了 ASCII 范围）。
这样 A 的子串与 B 的子串的 LCP 可以统一用 lcp() 查询
dp[i][j]：考虑 A 的前缀到位置 i（A 的子串起点搜索范围到 i），用了 j 次操作时，最多能匹配 B 的前 dp[i][j] 个字符。
转移：
跳过位置 i（不从这里取子串）。
从 A 的位置 i 与 B 当前已匹配位置（n+1+dp[i][j]，即 B 中的第 dp[i][j] 位）求 LCP 长度为 t，则用一次操作可取 t 个字符匹配，更新 dp[i+t][j+1]。
最终若某次操作 j 下 dp[n][j] >= m（能匹配完整个 B），输出 YES；否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int t1[N], t2[N], c[N], sa[N];
void build(const int s[], int n, int m) {
    int i, j, p, *x = t1, *y = t2;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) c[x[i]=s[i]]++;
    for (i = 1; i < m; ++i) c[i] += c[i-1];
    for (i = n-1; i >= 0; --i) sa[--c[x[i]]] = i;
    for (j = 1; j <= n; j <<= 1) {
        p = 0;
        for (i = n-j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i)
            if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[y[i]]]++;
        for (i = 1; i < m; ++i) c[i] += c[i-1];
        for (i = n-1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y); p = 1; x[sa[0]] = 0;
        for (i = 1; i < n; ++i)
            x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j] ? p-1 : p++;
        if (p >= n) break;
        m = p;
    }
}

int rk[N], h[N];
void get(const int s[], int n) {
    int i, j, k = 0;
    for (i = 0; i <= n; ++i) rk[sa[i]] = i;
    for (i = 0; i < n; ++i) {
        if (k) k--;
        j = sa[rk[i]-1];
        while (s[i+k] == s[j+k]) k++;
        h[rk[i]] = k;
    }
}

int d[N][19];
void init(int n) {
    for (int i = 1; i <= n; ++i) d[i][0] = h[i];
    for (int k = 1; 1<<k <= n; ++k)
        for (int i = 0; i+(1<<k) <= n; ++i)
            d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
}

int query(int l, int r) {
    int k = 0;
    while (1<<(k+1) <= r-l+1) k++;
    return min(d[l][k], d[r-(1<<k)+1][k]);
}

int lcp(int l, int r) {
    int L = rk[l], R = rk[r];
    if (L > R) swap(L, R), swap(l, r);
    if (L+1 == R) return h[R];
    return query(L+1, R);
}

int n, m, x, a[N], dp[N][32];
char s[N];
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) a[i] = s[i] - 'a' + 2; a[n] = 1;
    cin >> m >> s;
    for (int i = 0; i < m; ++i) a[n+i+1] = s[i] - 'a' + 2;
    int l = n+m+1; a[l] = 0;//结尾哨兵 0
    cin >> x; build(a, l+1, 60); get(a, l); init(l);
    for (int i = 0; i < n+1; ++i)
        for (int j = 0; j < x+1; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (j != x) {
                int t = lcp(i, n+1+dp[i][j]);
                dp[i+t][j+1] = max(dp[i+t][j+1], dp[i][j]+t);
            }
        }
    for (int j = 0; j < x+1; ++j)
        if (dp[n][j] >= m) return 0*puts("YES");
    puts("NO");
    return 0;
}