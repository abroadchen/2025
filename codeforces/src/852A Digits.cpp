//
// Created by Psy.C on 2026/9/29.
//
/**
主循环反复调用 solve()：只要 solve() 返回 true（表示"还得继续调整"），就在 s 里找下一个非零位置 i，把 u[i] 置 1（意思是把 s[i] 和 s[i+1] 拼成一个两位数），然后下标跳过两位继续。直到 solve() 返回 false（表示已经满足要求，并输出了答案）

根据 u[i] 决定是"把 s[i] 当作一位数"还是"把 s[i]s[i+1] 当作一个两位数"来求和，累加到 sm。
这就是数字串的一种"切分求和"。
把 sm 各位拆进数组 a[]（a[] 倒序存各位），同时累加数字和到 ss。
即 ss = 数字根路径的第一层
把 ss 拆进 b[]，累加数字和到 sss
只有当 sss < 10（即经过两层数字和之后结果还是个位数，即达到了稳定的数字根）时，才输出三段表达式并返回 false 结束。
否则返回 true，主循环继续调整 u[] 的分组，直到满足

输出第一段：原始分组的"和式"，形如 11+2+33+...
输出第二段：sm 的各位之和式（倒过来正常顺序），形如 d1+d2+...+dk
输出第三段：ss 的各位之和式
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5;

int n, u[N+5];
char s[N+5];
bool solve() {
    int i, sm = 0, ss = 0, sss = 0, x, y, a[10], an = 0, b[10], bn = 0;
    for (i = 1; i <= n; ++i) {
        if (u[i]) sm += (s[i]-'0')*10+s[i+1]-'0', ++i;
        else sm += s[i] - '0';
    }
    for (x = sm; sm; sm/=10) ss += a[++an] = sm%10;
    for (y = ss; ss; ss/=10) sss += b[++bn] = ss%10;
    if (sss < 10) {
        for (i = 1; i <= n; ++i) {
            if (i > 1) putchar('+');
            putchar(s[i]);
            if (u[i]) putchar(s[++i]);
        }
        puts("");
        for (i = an; i > 1; --i) printf("%d+", a[i]);
        printf("%d\n", a[1]);
        for (i = bn; i > 1; --i) printf("%d+", b[i]);
        printf("%d\n", b[1]);
        return false;
    }
    return true;
}

int main() {
    scanf("%d%s", &n, s+1);
    for (int i = 1; solve(); ) {
        for (; s[i] == '0'; ++i) {}//跳过 0
        u[i] = 1;//标记 u[i]，表示 s[i] 与 s[i+1] 要合并成两位数
        i += 2;
    }
    return 0;
}