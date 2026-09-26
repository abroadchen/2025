//
// Created by Psy.C on 2026/9/25.
//
/**
n：题目第一行读入的某个值（通常是字符串个数或类似参数）。
cnt：当前字符串中大写字母的个数（计数用）。
mx：到目前为止看到的所有字符串中，大写字母数量的最大值。
s[200]：存放读入的字符串
读入 n（但注意：代码后面没有用 n 来控制循环，说明 n 可能只是题目给定的一个参考值，真正输入靠下面的while 逐个词读取）
while (-scanf("%s", s))：不断读入一个以空白（空格/换行）分隔的单词存入 s。
读取失败时 scanf 返回 EOF（即 -1），-(-1) == 0，循环结束。
遇到文件末尾或输入结束就自动停止，直到把所有字符串读完。
每读进一个字符串：
重置 cnt = 0。
遍历字符串每个字符，若是大写字母 'A' 到 'Z'（即 s[i] >= 'A' && s[i] <= 'Z'），就 cnt++ 计数。
用 mx = max(cnt, mx) 更新历史最大值
输出所有字符串中单个字符串包含大写字母数量的最大值
 */
#include <bits/stdc++.h>
using namespace std;

int n, cnt, mx;
char s[200];
int main() {
    scanf("%d", &n);
    while (~scanf("%s", s)) {
        cnt = 0;
        int len = strlen(s);
        for (int i = 0; i < len; ++i)
            if (s[i] >= 'A' && s[i] <= 'Z')
                cnt++;
        mx = max(cnt, mx);
    }
    printf("%d\n", mx);
    return 0;
}