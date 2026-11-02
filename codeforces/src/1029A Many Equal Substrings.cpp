//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
目标是找出一个偏移量：当第二次拼接到这个位置时，能"复用"已输出的部分，从而每次只需真正新增 x 个字符。
具体做法：for i 从 1 起找第一个 s[i] == s[0] 的位置，并验证 s[i..n-1] 与 s[0..] 的前缀逐字符相等（flg）。
若成立，说明 s 以 s[0..i-1] 为循环节，重叠复用长度 n-i，即每次新增 x = n-i 个字符。找到第一个就用 break 退出。
若找不到，x 保持默认 0
先输出完整 s（第一次拼接的名副其实为整串）。
之后每次只需输出 s[x..n-1] 共 n-x 个字符，即复用开头 x 个字符。
通过这样做，最终得到一个以 s[0..x-1] 为循环节、叠加 k 次的长串，且保证相邻拼接处合法
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2505;

int n, k, x;
char s[N];
int main() {
    fast;
    cin >> n >> k >> s;//s 长度 n，要拼 k 次
    for (int i = 1; i < n; i++) if (s[i] == s[0]) {//找到能让拼接重叠的起点
        int k = 1, flg = 1;
        for (int j = i+1; j < n; j++, k++) if (s[j] != s[k]) flg = 0;//检查 s[i..] 是否等于 s[0..] 的前缀
        if (flg) { x = n - i; break; }//找到最长可用重叠 → 记录节长
    }
    cout << s;
    while (--k) {//再重复 (k-1) 次
        for (int i = x; i < n; i++)//每次只输出后缀 s[x..n-1]（x 个字符）
            cout << s[i];
    }
    cout << '\n';
    return 0;
}