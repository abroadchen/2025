//
// Created by Psy.C on 2026/3/22.
//
/**
nxt[i]表示s[0...i]的最长公共前后缀长度-1
将反转并转换后的b与原字符串a用空格连接
对拼接字符串执行KMP算法 用KMP算法检查转换后的b是否为a的子串
根据最后一位的next值判断结果
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e6+5;
///将方向字符转换为其相反方向
char get(char c) {
    if (c == 'N') return 'S';
    if (c == 'S') return 'N';
    if (c == 'W') return 'E';
    if (c == 'E') return 'W';
    return 0;
}

int len, nxt[N];
void kmp(string s) {
    len = s.length(); nxt[0] = -1;
    for (int i = 1, j = -1; i < len; ++i) {
        while (j != -1 && s[i] != s[j+1])
            j = nxt[j];
        if (s[i] == s[j+1]) j++;
        nxt[i] = j;
    }
}

int n;
string a, b, ans;
int main() {
    cin >> n >> a >> b; n--;
    ranges::reverse(b);
    for (char &c : b) c = get(c);
    ans = b + ' ' + a;
    kmp(ans);
    puts(nxt[len-1] == -1 ? "YES" : "NO");
    return 0;
}