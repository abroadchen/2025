//
// Created by Psy.C on 2025/9/19.
//
/*
*定义二维字符数组s存储3个字符串
定义数组l存储3个字符串的长度
定义ans存储最短合并长度
定义seq存储字符串排列顺序
 *
*next数组用于记录字符串的最长相等前后缀长度
i从2开始，j从0开始（next[1]=0）
当字符不匹配时，回退到next[j]位置继续匹配
 *
*使用KMP算法在字符串a中查找字符串b的最大匹配后缀长度
首先为字符串b构建next数组
在字符串a中匹配字符串b
返回最大匹配长度（即字符串b的前缀与字符串a的后缀的最大重合长度）
 *
 *
*计算按顺序a->b->c合并三个字符串的最短长度
首先计算字符串a和b的最大重合长度t
临时保存字符串a，然后将b的部分内容追加到a后面
计算新的a与c的最大重合长度
恢复原始字符串a，计算最终合并长度
返回总长度（避免实际修改原字符串）
 *
 *
*读取3个字符串，存储在s[i][1]开始的位置（便于KMP处理）
计算初始总长度ans（不重合的情况）
初始化排列数组seq为{0,1,2}
遍历所有排列组合（共6种），找到最小合并长度
输出最短长度
 *
 *
 *时间复杂度：O(6 × (l1+l2+l3)) = O(l1+l2+l3)，其中li是第i个字符串的长度
 *
 *
 *
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

static const int maxn=3e5+10;
char s[3][maxn];
int l[3], ans, seq[3], nxt[maxn];

void get_next(int k) {
    for (int i = 2, j = 0; i <= l[k]; ++i) {
        while (j && s[k][i] != s[k][j + 1]) j = nxt[j];
        if (s[k][i] == s[k][j + 1]) j++;
        nxt[i] = j;
    }
}


int kmp(int a, int b) {
    get_next(b);

    int j = 0;
    for (int i = 1; i <= l[a]; ++i) {
        while (j && s[a][i] != s[b][j + 1]) j = nxt[j];
        if (s[a][i] == s[b][j + 1]) j++;
        if (j == l[b]) return j;
    }
    return j;
}



int calc(int a, int b, int c) {
    char tmp[maxn]; int lt;

    int t = kmp(a, b);
    memcpy(tmp, s[a], sizeof(tmp));
    lt = l[a];

    int res = l[a] + l[b] - t;
    for (int i = 1; i <= l[b] - t; ++i)
        s[a][l[a] + i] = s[b][t + i];
    l[a] = res;

    t = kmp(a, c);
    memcpy(s[a], tmp, sizeof(s[a]));
    l[a] = lt;
    res = res + l[c] - t;
    return res;
}



int main() {

    for (int i = 0; i < 3; ++i) {
        scanf("%s", s[i] + 1);
        l[i] = strlen(s[i] + 1);
        ans += l[i];
        seq[i] = i;
    }

    do {
        ans = min(ans, calc(seq[0], seq[1], seq[2]));
    } while (next_permutation(seq, seq + 3));

    printf("%d\n", ans);
    
    return 0;
}