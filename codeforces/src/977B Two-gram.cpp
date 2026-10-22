//
// Created by Psy.C on 2026/10/22.
//
/**
N = 27：字符下标范围（0..26），用于 26 个大写字母。
M = 64：ASCII 偏移基准。大写字母 'A'(65) 减 64 = 1，'Z'(90) 减 64 = 26，正好落在 1..26 的表范围内。
a[N][N]：二维计数数组，a[x][y] 表示二元组 (x, y) 的出现次数。
s：输入字符串
读入 n 与字符串 s。
遍历 i=0..n-2，对每个相邻字符对 (s[i], s[i+1])：
把两个字符都减去 M=64 得到 1..26 的整数下标。
a[下标][下标]++ 计数。
r、c 用于记录答案二元组的下标，mx 记录最大次数
双重循环遍历 1..26 × 1..26 的所有二元组下标。
用 mx < a[i][j]（严格小于）更新：找到出现次数最大的二元组，记录其行列下标到 r、c。
因是严格 <，遇到相同次数不会覆盖，所以取的是第一个出现的最大（若并列取字典序更小者，因为行优先遍历）
把下标 r、c 各自加回 M=64 转回字符，输出两个字符。
即输出出现次数最多的相邻二元组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 27, M = 64;

int n, i, j, a[N][N];
string s;
int main() {
    fast;
    cin >> n >> s;
    int mx = 0, r = 0, c = 0;
    for (i = 0; i < n-1; i++) a[s[i]-M][s[i+1]-M]++;
    for (i = 1; i <= N-1; i++)
        for (j = 1; j <= N-1; j++)
            if (mx < a[i][j]) {
                mx = a[i][j]; r = i; c = j;
            }
    cout << static_cast<char>(r + M) << static_cast<char>(c + M) << '\n';
    return 0;
}