//
// Created by Psy.C on 2026/10/17.
//
/**
判断一个字符是否是元音（这里把 y 也当元音）。返回 1（是）或 0（不是）
读入字符串长度 n 和字符串 c（cin >> c 读入到 c[0] 起
遍历字符串每个字符。flg 记录前一个字符是否也是元音（是否 "正在连续元音段内"）
当前字符是元音 且 前一个字符也是元音（连续元音）→ 跳过不输出（删除多余元音）
重新更新 flg：当前是元音则置 1，否则置 0。
输出这个没被跳过的字符
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105;

int isv(char a) {
    return a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y';
}

char c[N];
int main() {
    fast;
    int n; cin >> n >> c;
    for (int i = 0, flg = 0; i < strlen(c); ++i) {
        if (isv(c[i]) && flg) continue;
        if (isv(c[i])) flg = 1; else flg = 0;
        cout << c[i];
    }
    return 0;
}