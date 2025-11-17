//
// Created by Psy.C on 2025/11/17.
//
/*
*递归函数，判断数字a是否为合数（非质数）
如果a≤i，返回true（递归终止条件）
否则检查a是否能被i整除：
如果a%i≠0且dfs(a,i+1)为true，则返回true
否则返回false
实际上这是在判断一个数是否不是质数
 *
 *统计输入字符串中每个字符的出现次数
 *找到字符计数数组c中的最大元素指针m（出现次数最多的字符）
 *
*遍历字符串位置（从索引1开始）
条件判断：
如果i < n/2（前半部分）
或者i+1不是合数（即i+1是质数）
满足条件时：
将出现次数最多的字符放到位置i：t[i] = m - c
减少该字符的计数：(*m)--
注意：m - c 计算的是字符的ASCII值，因为m是指向c数组中某个位置的指针
 *
 *如果最频繁字符的计数变成负数，说明无法构造，输出"NO"
*填充还没有分配字符的位置：
遍历字符串t，找到值为0（未分配）的位置
找到第一个还有剩余计数的字符p
将字符p分配给位置i，并减少其计数
 *
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

int c[256];

bool dfs(int a, int i) { return a <= i || a % i != 0 && dfs(a, i + 1); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    int n = s.size();
    for (int i = 0; i < n; ++i) c[s[i]]++;
    string t(n, 0);
    int *m = max_element(c, c + 256);
    for (int i = 1; i < n; ++i) {
        if (i < n / 2 || !dfs(i + 1, 2)) {
            t[i] = m - c;
            (*m)--;
        }
    }
    if (*m < 0) { cout << "NO"; return 0; }
    for (int i = 0, p = 0; i < n; ++i) if (!t[i]) {
        while (!c[p]) p++;
        c[t[i]=p]--;
    }
    cout << "YES\n" << t;
    return 0;
}