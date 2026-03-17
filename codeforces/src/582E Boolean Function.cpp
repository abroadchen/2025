//
// Created by Psy.C on 2026/3/17.
//
/**
M = 500：最大表达式长度
N = 16：最大变量数

快速沃尔什变换（AND卷积）
op=1：正变换
op=0：逆变换
实现子集卷积的快速计算
快速沃尔什变换（OR卷积）
与AND卷积类似，但变换方向不同
f[i][mask]：第i个节点在掩码mask下的方案数
AND运算的卷积
先对三个数组做正变换
逐位相乘
再做逆变换
OR运算的卷积
类似AND卷积的处理过程

tot：节点编号
cur：当前解析位置
v[5]：存储A-E或a-e的值
s：表达式字符串
如果后两位是)，说明是叶子节点
?：表示任意A-D，对所有可能的值都设置方案数
其他字符：根据是大写(A-D)还是小写(a-d)设置对应位置的方案数

v[i]^m 取反v[i]的低n位

递归处理左右子树
根据运算符|或&执行相应的卷积操作
op^'|'：如果op不是'|'，则执行AND卷积
op^'&'：如果op不是'&'，则执行OR卷积

在表达式前后添加括号，简化解析
逐位读入5个变量（A-E）的值
将第i位的值累加到v[j]的对应位上
v[4]对应E的值
输出根节点在E值对应掩码下的方案数
 */
#include <bits/stdc++.h>
#define add(x,y) (((x+=(y))>=mod&&(x-=mod)))
using namespace std;
constexpr int mod = 1e9 + 7, M = 500, N = 16;

int m;
inline void fwt_a(int *s, const int& op) {
    for (int i = 1; i <= m; i<<=1)
        for (int j = 0; j <= m; j += i<<1)
            for (int k = 0; k^i; ++k)
                op ? add(s[j+k], s[i+j+k]) : add(s[j+k], mod-s[i+j+k]);
}
inline void fwt_o(int *s, const int& op) {
    for (int i = 1; i <= m; i<<=1)
        for (int j = 0; j <= m; j += i<<1)
            for (int k = 0; k^i; ++k)
                op ? add(s[i+j+k], s[j+k]) : add(s[i+j+k], mod-s[j+k]);
}

int f[M+5][1<<N];
inline void mula(const int& x, const int& l, const int& r) {
    fwt_a(f[x], 1), fwt_a(f[l], 1), fwt_a(f[r], 1);
    for (int i = 0; i <= m; ++i)
        f[x][i] = (1ll*f[l][i]*f[r][i] + f[x][i]) % mod;
    fwt_a(f[x], 0), fwt_a(f[l], 0), fwt_a(f[r], 0);
}

inline void mulo(const int& x, const int& l, const int& r) {
    fwt_o(f[x], 1), fwt_o(f[l], 1), fwt_o(f[r], 1);
    for (int i = 0; i <= m; ++i)
        f[x][i] = (1ll*f[l][i]*f[r][i] + f[x][i]) % mod;
    fwt_o(f[x], 0), fwt_o(f[l], 0), fwt_o(f[r], 0);
}

int tot, cur, v[5];
char s[M+5];
int dfs() {
    int x = ++tot, l, r; char op;
    if (s[cur+2] == ')') {//叶子节点
        if (s[cur+1] == '?')//通配符
            for (int i = 0; i^4; ++i) ++f[tot][v[i]], ++f[tot][v[i]^m];
        else (s[cur+1] <= 'D' ? f[tot][v[s[cur+1]-'A']] : f[tot][v[s[cur+1]-'a']^m]) = 1;
        return cur += 3, x;
    }
    ++cur, l = dfs(), op = s[cur], ++cur, r = dfs();
    return op^'|' && (mula(x, l, r), 0), op^'&' && (mulo(x, l, r), 0), ++cur, x;
}

int n, l;
int main() {
    scanf("%s%d", s+1, &n), l = strlen(s+1), s[0] = '(', s[l+1] = ')', m = (1<<n)-1;
    for (int i = 0; i^n; ++i)
        for (int j = 0, x; j^5; ++j) scanf("%d", &x), v[j] |= x<<i;
    return printf("%d\n", f[dfs()][v[4]]), 0;
}