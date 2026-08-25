//
// Created by Psy.C on 2026/5/9.
//
/**
第i个节点在第bit位为s时的查询结果
(i>>bit&1)^1获取的是与i在该位上相反的值
 */
#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1007, inf = 1e9;

int n, a[N][13][2], tag[N];
void get(int s, int bit) {
    int t = 0;//统计tag[i]==s的元素数量
    for (int i = 1; i <= n; ++i)
        if (tag[i] == s) ++t;
    printf("%d\n", t);
    for (int i = 1; i <= n; ++i)
        if (tag[i] == s) printf("%d ", i);//满足条件的元素索引
    putchar('\n'); fflush(stdout);
    for (int i = 1; i <= n; ++i)
        a[i][bit][s] = rd();
}

int main() {
    n = rd();
    for (int i = 0; 1<<i <= n; ++i) {//枚举每一位（从第0位开始），直到2^i > n
        for (int j = 1; j <= n; ++j)
            if (j>>i&1) tag[j] = 1;//第j个数的第i位是1，则标记tag[j]=1
        get(0, i), get(1, i);//分别查询tag值为0和1的情况
        for (int j = 1; j <= n; ++j) tag[j] = 0;//清空tag数组，准备下一轮查询
    }
    puts("-1");//结束标志
    for (int i = 1; i <= n; ++i) {
        int ans = inf;
        for (int bit = 0; 1<<bit <= n; ++bit)
            ans = min(ans, a[i][bit][(i>>bit&1)^1]);
        printf("%d ", ans);
    }
    fflush(stdout);
    return 0;
}