//
// Created by Psy.C on 2025/11/9.
//
/*
*s1[N + 1]：存储第一个字符串（模式串）
s2[M + 1]：存储第二个字符串（文本串）
nxt[N+1][K]：状态转移表，nxt[i][c]表示从位置i开始下一个字符c的位置
 *
*构造自动机（状态转移表）：
首先初始化边界条件：在字符串末尾位置n，所有字符的下一个位置都是n（表示不存在）
从后往前遍历s1的每个位置i：
复制位置i+1的状态转移信息到位置i
更新位置i处字符s1[i]的转移位置为i本身
这个构造过程建立了一个DFA（确定有限自动机），可以高效地查找s1的子序列
 *
*ans：记录需要重新开始匹配的次数
cur：当前在s1中的位置，初始化为n（表示匹配完成状态）
遍历s2中的每个字符：
如果s2[i]在s1中根本不存在，输出-1并退出
如果从当前位置cur可以找到字符s2[i]：更新位置到找到位置的下一个
否则（需要重新开始匹配）：增加计数器，从头开始匹配
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1e4, M = 1e6, K = 26;
char s1[N+1], s2[M+1];
int nxt[N+1][K];

int main() {
    scanf("%s%s", s1, s2);
    int n = strlen(s1), m = strlen(s2);
    for (int i = 0; i < K; ++i) nxt[n][i] = n;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < K; ++j) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s1[i] - 'a'] = i;
    }
    int ans(0), cur(n);
    for (int i = 0; i < m; ++i) {
        if (nxt[0][s2[i] - 'a'] == n) { puts("-1"); return 0; }
        if (nxt[cur][s2[i] - 'a'] < n) cur = nxt[cur][s2[i] - 'a'] + 1;
        else { ans++; cur = nxt[0][s2[i] - 'a'] + 1; }
    }
    printf("%d\n", ans);
    return 0;
}