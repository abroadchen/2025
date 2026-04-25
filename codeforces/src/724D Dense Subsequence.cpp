//
// Created by Psy.C on 2026/4/24.
//
/**
n, m: 字符串长度和窗口大小
s[N]: 存储输入字符串
检查以字符ch作为"分界符"时，是否能满足约束条件
l: 最近出现目标字符ch的位置
r: 最近出现小于ch的字符的位置
num: 已经插入了多少个字符 ch 来修复违规窗口
当 i - r >= m 时，说明已经有m个连续字符都不小于ch
如果此时 i - l < m，说明距离最近的ch字符在有效范围内，可以插入一个ch字符解决问题
否则返回-1表示无解

从小到大尝试每个可能的"分界符"字符
~x 检查x是否不是-1（即get函数返回有效值）
如果找到了有效的分界符ch:
首先输出所有小于ch的字符（按照原有数量）
然后输出x个ch字符（x是需要插入的ch字符数量）


情况1: i - l < m（当前位置到最近的ch字符的距离小于m）
说明在这个违规窗口中，存在字符 ch
我们假设在这个位置"插入"一个字符 ch 来分割这个违规窗口
更新 r = l（表示插入了一个ch字符，它也起到了分割作用）
num++（记录插入的ch字符数量）
情况2: i - l >= m（当前位置到最近的ch字符的距离大于等于m）
说明在这个违规窗口中，没有字符 ch 可以用来分割
无法修复这个违规窗口，返回 -1（无解）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7, M = 26;

int n, m;
char s[N];
int get(char ch) {
    int l = -1, r = -1, num = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == ch) l = i;//更新 l 为当前位置
        else if (s[i] < ch) r = i;//如果当前字符小于 ch，更新 r 为当前位置
        if (i - r >= m) {//从位置 r+1 到位置 i，长度为 i-r 的连续子串中，没有任何一个小于字符 ch 的字符
            if (i - l < m) r = l, num++;
            else return -1;
        }
    }
    return num;
}

int a[M], x;
int main() {
    fast;
    cin >> m >> s; n = strlen(s);
    for (int i = 0; i < n; ++i) a[s[i]-'a']++;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        x = get(ch);
        if (~x) {
            for (int i = 0; i < ch-'a'; ++i)
                while (a[i]--)
                    printf("%c", 'a'+i);
            while (x--) printf("%c", ch);
            break;
        }
    }
    return 0;
}