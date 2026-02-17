//
// Created by Psy.C on 2026/2/17.
//
/**
m: 操作次数
k: 每组长度
p: 周期
cnt: 计数器
P[N]: 置换数组
C[N]: 循环数组
s[N], t[N]: 原字符串和临时字符串

逐字符读入字符串，直到换行符
s[n] 存储字符，n 计数

每次操作：O(n log(n-k+1))
总时间复杂度：O(m * n * log(n-k+1))
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000006;

int n, c[N];
void get(int *a, const int *b) {//按照索引数组b重新排列数组a
    for (int i = 0; i < n; ++i) c[i] = a[b[i]];
    for (int i = 0; i < n; ++i) a[i] = c[i];
}

int ans[N];
void ksm(int *s, int p) {
    for (int i = 0; i < n; ++i) ans[i] = s[i];
    p--;//ans已经初始化为s
    while (p) {
        if (p&1) get(ans, s);
        get(s, s);
        p >>= 1;
    }
}

int m, k, p, cnt, P[N], C[N];
char s[N], t[N];
int main() {
    while ((s[n]=getchar())!='\n') n++;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &k, &p); cnt = -1;
        for (int x = 0; x < p; ++x)//按周期p重新排列前k个位置
            for (int j = x; j < k; j += p)
                P[++cnt] = j;//按周期排列
        for (int j = k; j < n; ++j) P[j] = j;//后面的元素不变
        for (int j = 0; j < n-1; ++j) C[j] = j+1;//形成循环：0→1→2→...→n-1→0
        C[n-1] = 0;
        get(P, C);//应用循环变换到P
        ksm(P, n-k+1);
        for (int j = 0; j < n; ++j)//根据变换后的索引重新排列字符串
            t[j] = s[ans[j>=n-k+1 ? j-(n-k+1) : j+n-(n-k+1)]];
        for (int j = 0; j < n; ++j)
            putchar(t[j]), s[j] = t[j];//将结果字符串复制回s作为下次操作的输入
        putchar('\n');
    }
    return 0;
}