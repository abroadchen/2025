//
// Created by Psy.C on 2026/3/19.
//
/**
N = 5e6+5：最大数组大小
n：字符串长度
s[N]：原字符串
l[N], r[N], t：Lyndon分解相关数组和计数
k：操作次数
ans[N]：答案字符串
ss[N<<1]：双倍长度字符串
z[N], p[N]：Z算法和扩展KMP相关数组

get：Duval算法实现Lyndon分解
t = 0：初始化分解段数
i = 1：当前处理位置
j = i, k = i + 1：双指针比较
while (k <= n && s[j] <= s[k])：比较字符大小
j = s[j] == s[k++] ? j + 1 : i：相等则继续比较，否则回到起始位置
while (i <= j) i += k - j：更新位置
r[++t] = i - 1, l[t] = k - j：记录段的结束位置和长度

f1()：处理k=1的情况
比较字符串与其反转的字典序
如果反转后字典序更小，则反转原字符串
输出结果
f3()：处理k>=3的情况
输出最后一段Lyndon词
更新k值和t值

update(char *s)：更新答案为字典序更小的字符串
逐字符比较字典序
如果传入字符串更小，则更新ans
update2()：反转字符串后更新答案，然后恢复
update3()：找字符串的最小表示（循环同构中的字典序最小串）
将字符串复制一遍到ss
使用Lyndon分解的思想找到最小表示
更新答案

get(char *s, int n, int *z)：Z算法，计算z数组
z[i]表示s[i...n]与s[1...n]的最长公共前缀长度
使用滑动窗口优化，时间复杂度O(n)
ex：扩展KMP算法
计算字符串s的每个后缀与模式串t的最长公共前缀

modify()：复杂的字符串处理函数
使用扩展KMP找到最佳分割点
通过多次反转和更新找到最优解
modify2()：基于Lyndon分解的处理
找到相同的Lyndon词段
通过比较和反转更新最优解

读取输入字符串和k值
如果k=1，直接处理并输出
否则反转字符串，进行Lyndon分解
处理k>=3的情况
如果还有剩余长度，调用solve函数
输出最终答案

s[i+z[i]]：字符串 s[i...n] 中的第 z[i]+1 个字符
s[z[i]+1]：字符串 s[1...n] 中的第 z[i]+1 个字符

j：当前认为的最佳分割点（后面要反转的边界）
i：候选分割点
p[]：扩展KMP数组，p[k] = s_reverse[k...n] 与 s[1...n] 的LCP长度
z[]：Z数组，z[k] = s[k...n] 与 s[1...n] 的LCP长度

比较从位置j-1开始的后缀与从位置1开始的前缀的匹配情况
p[j-1]：s_rev[j-1...n] 与 s[1...n] 的LCP长度
j - i：从位置j-1到位置i的距离（即待比较的长度）
p[j-1] < j - i：如果LCP长度小于待比较长度
s[j-1-p[j-1]] < s[p[j-1]+1]：比较第一个不匹配的字符
s[j-1-p[j-1]]：反转后字符串中第p[j-1]+1个字符（从后往前数）
s[p[j-1]+1]：原字符串中第p[j-1]+1个字符
如果反转后的字符更小，更新j = i

比较从位置j-i+1开始的后缀与原字符串的匹配情况
z[j-i+1]：s[j-i+1...n] 与 s[1...n] 的LCP长度
i - 1：待比较的长度
z[j-i+1] < i - 1：如果LCP长度小于待比较长度
s[z[j-i+1]+1] < s[j-i+1+z[j-i+1]]：比较第一个不匹配的字符
s[z[j-i+1]+1]：原字符串中LCP之后的第一个字符
s[j-i+1+z[j-i+1]]：从位置j-i+1开始的字符串中LCP之后的第一个字符
如果原字符串的字符更小，更新j = i

p：当前检查的Lyndon词段索引
r[p]：第p个Lyndon词段的结束位置
l[p]：第p个Lyndon词段的长度
p = t + 1; while (--p > 1)：从最后一个Lyndon词段向前遍历
for (int i = r[p-1]+1, j = r[p-2]+1; ok && i <= r[p]; ++i, ++j)：
i = r[p-1]+1：第p-1个Lyndon词段结束后的位置（第p个词段的开始）
j = r[p-2]+1：第p-2个Lyndon词段结束后的位置（第p-2个词段的开始）
比较第p个词段和第p-2个词段是否完全相同

q = p：从第一部分找到的位置开始
++q <= t：继续向后遍历Lyndon词段
for (int i = r[q-1], j = r[q-2]+1+n-i; i > r[q-2]; --i, ++j)：
i = r[q-1]：第q-1个词段的结束位置（倒序遍历）
j = r[q-2]+1+n-i：计算对应的比较位置
这里是从后往前比较字符
这是一个复杂的索引计算，目的是找到与s[i]对应的比较字符
n-i：从末尾到位置i的距离
r[q-2]+1：第q-2个词段的开始位置
整体是为了找到对称位置进行比较
if (s[i] == s[j]) continue;：字符相等，继续比较
if (s[i] < s[j]) p = q;：如果当前字符更小，更新p为q
break;：遇到不相等的字符就停止当前词段的比较

 */
#include <bits/stdc++.h>
using namespace std;
///快速读取字符串函数
void rds(char *s, int &n) {
    n = 0;
    char ch = getchar();
    while (ch != '\n' && ch != EOF && !isspace(ch)) {//读取直到换行、EOF或空格
        s[++n] = ch;//将字符存入数组，长度自增
        ch = getchar();
    }
}
template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 5e6+5;

void get(char *s, int n, int *r, int *l, int &t) {
    t = 0;
    int i = 1;
    while (i <= n) {
        int j = i, k = i + 1;
        while (k <= n && s[j] <= s[k])
            j = s[j] == s[k++] ? j + 1 : i;
        while (i <= j) i += k - j;
        r[++t] = i - 1, l[t] = k - j;
    }
}

int n;
char s[N];
void f1() {
    for (int i = 1; i <= n; ++i) {
        if (s[n+1-i] == s[i]) continue;
        if (s[n+1-i] < s[i]) reverse(s + 1, s + n + 1);
        break;
    }
    for (int i = 1; i <= n; ++i) putchar(s[i]);
}

int l[N], r[N], t, k;
void f3() {
    for (int i = r[t-1]+1; i <= r[t]; ++i) putchar(s[i]);
    k -= l[t] != 1 || l[t-1] != 1, --t;
}

char ans[N];
void update(char *s) {
    for (int i = 1; i <= n; ++i) {
        if (s[i] > ans[i]) return;
        if (s[i] < ans[i]) break;
    }
    for (int i = 1; i <= n; ++i) ans[i] = s[i];
}

void update2() {
    reverse(s + 1, s + n + 1);
    update(s);
    reverse(s + 1, s + n + 1);
}

char ss[N<<1];
void update3() {
    for (int i = 1; i <= n; ++i) ss[i] = ss[i+n] = s[i];
    int i = 1, o = 0;
    while (i <= n) {
        o = i;
        int j = i, k = i + 1;
        while (k <= n<<1 && ss[j] <= ss[k])
            j = ss[j] == ss[k++] ? j + 1 : i;
        while (i <= j) i += k - j;
    }
    update(ss + o - 1);
}

void get(char *s, int n, int *z) {
    for (int i = 1; i <= n; ++i) z[i] = 0;
    z[1] = n;//自己与自己的LCP是整个长度
    for (int i = 2, l = 0, r = 0; i <= n; ++i) {
        if (i <= r) z[i] = min(z[i-l+1], r-i+1);
        while (i + z[i] <= n && s[i+z[i]] == s[z[i]+1]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

void ex(char *s, int n, char *t, int m, int *z, int *p) {
    get(t, m, z);
    for (int i = 1; i <= n; ++i) p[i] = 0;
    for (int i = 1, l = 0, r = 0; i <= n; ++i) {
        if (i <= r) p[i] = min(z[i-l+1], r-i+1);
        while (i + p[i] <= n && s[i+p[i]] == t[p[i]+1]) ++p[i];
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
}

int z[N], p[N];
void modify() {
    for (int i = 1; i <= n; ++i) ss[i] = s[i];
    reverse(ss + 1, ss + n + 1);
    ex(ss, n, s, n, z, p);
    reverse(p + 1, p + n + 1);
    int j = n;
    for (int i = n - 1; i; --i) {
        if (p[j-1] < j - i) {
            if (s[j-1-p[j-1]] < s[p[j-1]+1])
                j = i;
        } else if (z[j-i+1] < i - 1) {
            if (s[z[j-i+1]+1] < s[j-i+1+z[j-i+1]])
                j = i;
        }
    }
    reverse(s + 1, s + j);
    reverse(s + 1, s + n + 1);
    update(s);
    reverse(s + 1, s + n + 1);
    reverse(s + 1, s + j);
}

void modify2() {
    int p = t + 1;
    while (--p > 1) {
        bool ok = 1;
        for (int i = r[p-1]+1, j = r[p-2]+1; ok && i <= r[p]; ++i, ++j)
            if (s[i] != s[j]) ok = 0;
        if (!ok) break;
    }
    int q = p;
    while (++q <= t) {
        for (int i = r[q-1], j = r[q-2]+1+n-i; i > r[q-2]; --i, ++j) {
            if (s[i] == s[j]) continue;
            if (s[i] < s[j]) p = q;
            break;
        }
    }
    reverse(s + r[p-1] + 1, s + n + 1);
    reverse(s + 1, s + n + 1);
    update(s);
    reverse(s + 1, s + n + 1);
    reverse(s + r[p-1] + 1, s + n + 1);
}

void solve() {
    for (int i = 1; i <= n; ++i) ans[i] = s[i];
    update2(), update3(), modify(), modify2();
}



int main() {
    rds(s, n), rd(k);
    if (k == 1) return f1(), 0;
    reverse(s + 1, s + n + 1);
    get(s, n, r, l, t);
    while (k >= 3 && t) f3();
    if ((n=r[t])) solve();
    for (int i = 1; i <= n; ++i) putchar(ans[i]);
    return 0;
}