//
// Created by Psy.C on 2026/10/9.
//
/**
有 3 个小球/数字（1、2、3），其中有一个是"答案/被藏起来的"。
初始时认为答案可能在 1 或 2（v[1]=v[2]=1），不可能是 3（v[3]=0）。
h[i] 是第
i
i 次操作中"给出的提示数字"
if (v[h[i]] == 0)：如果当前提示 h[i] 已经被排除（v[h[i]]=0），说明这个"答案"不可能是它，却把它当作答案提示 → 矛盾，输出 NO 结束。

否则执行一次"状态翻转（toggle）‍"：把所有与 h[i] 不同的候选取反（0↔1）
即：除了 h[i] 之外的另外两个候选，把它们的"可能存在"状态翻转一遍。h[i] 本身不动

这是这类题的经典 trick：当提示给出数字
h
[
i
]
h[i] 时，意味着"答案在这三个里换了一个"，导致另外两个候选的"可能在/不在"身份互换。所以对非
h
[
i
]
h[i] 的两个做状态的异或翻转，等价于维持"三个里只有一个是答案"的排他约束。

很像 "Fermi / 猜拳排除"或 CSES 里的 Three Doors、CF "Ball in 3 boxes" 的思维：每次出现一个数字，就把它之外的两个"未知状态"取反
若全程没有出现"提示了已被排除的数字"，则流程自洽，输出 YES。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int h[110];
bool v[4];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    v[1] = 1; v[2] = 1;
    for (int i = 1; i <= n; ++i) {
        if (v[h[i]] == 0) { cout << "NO"; return 0; }
        for (int j = 1; j <= 3; ++j) {
            if (j != h[i] && v[j] == 1) v[j] = 0;
            else if (v[j] == 0) v[j] = 1;
        }
    }
    cout << "YES";
    return 0;
}