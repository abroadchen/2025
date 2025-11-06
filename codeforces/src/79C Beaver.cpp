//
// Created by Psy.C on 2025/11/6.
//
/*
*N = 100086: 主字符串的最大长度
M = 12: 模式串的最大数量
*s[N]: 主字符串（文本）
b[M][M]: 存储M个模式串
l[M]: 存储每个模式串的长度
 *
 *检查位置k是否是某个模式串的结尾位置
*k: 文本中的当前位置
n: 模式串数量
*对每个模式串t：
从模式串末尾开始向前匹配
k - l[t] + i + 1是文本中对应的字符位置
如果字符不匹配则跳出内层循环
如果整个模式串都匹配（i < 0），更新最大起始位置
返回所有匹配模式串中最大的起始位置
 *
*p: 当前安全区域的起始位置
mx: 找到的最长安全子串长度
st: 最长安全子串的起始位置
 *
*遍历文本中的每个位置i
调用solve(i, n)检查位置i是否是某个模式串的结尾
如果是（k != -1）：
计算从p到i-1的安全子串长度
如果更长则更新mx和st
更新安全区域起始位置p为max(p, k + 1)
*处理最后一个安全区域（文本末尾）
输出最长安全子串的长度和起始位置
 *
*O(|s| × n × max(|pattern|))
其中|s|是文本长度，n是模式串数量
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 100086, M = 12;
char s[N], b[M][M];
int l[M];

int solve(const int k, const int n) {
    int mx(-1);
    for (int t = 0, i; t < n; ++t) {
        for (i = l[t] - 1; i >= 0 && k - l[t] + i + 1 >= 0; --i) {
            if (b[t][i] != s[k - l[t] + i + 1]) break;
        }
        if (i < 0) mx = max(mx, k - l[t] + 1);
    }
    return mx;
}


int main() {

    int n; scanf("%s%d", s, &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", b[i]);
        l[i] = strlen(b[i]);
    }
    int p(0), mx(-1), st(0), i;
    for (i = 0; s[i]; ++i) {
        int k = solve(i, n);
        if (k == -1) continue;
        if (i - p > mx) mx = i - p, st = p;
        p = max(p, k + 1);
    }
    if (i - p > mx) mx = i - p, st = p;
    printf("%d %d\n", mx, st);
    return 0;
}