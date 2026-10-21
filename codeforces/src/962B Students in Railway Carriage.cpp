//
// Created by Psy.C on 2026/10/21.
//
/**
提前终止：若 a 和 b 都已用完（!a && !b），直接跳出。
跳过障碍：c[i]=='*' 的格子跳过（* 是不可用/障碍格）。
情况一：当前格可独立放置（i==1，或前一个格是 . 或 *，即左邻不是 A/B）：
若 a > b 则放 A（用掉一个 a）；否则放 B（用掉一个 b）；ans++。
注意：这里因为 !a && !b 已 break，故 a、b 至少一个 >0，必有资源可用。
情况二：前一个格是 A 且还有 b → 把前一个格改成 B（c[i-1]='B'; --b; ++ans）。
情况三：前一个格是 B 且还有 a → 把前一个格改成 A（--a; ++ans）
输出总共放置/计数次数 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, a, b, len, ans;
char c[N];
int main() {
    fast;
    read(n); read(a); read(b); scanf("%s", c+1); len = strlen(c+1);
    for (int i = 1; i <= len; i++) {
        if (!a && !b) break;
        if (c[i] == '*') continue;
        if (i == 1 || c[i-1] == '.' || c[i-1] == '*') {
            if (a > b) c[i] = 'A', --a, ++ans;
            else c[i] = 'B', --b, ++ans;
        }
        else if (c[i-1] == 'A' && b) c[i-1] = 'B', --b, ++ans;
        else if (c[i-1] == 'B' && a) c[i-1] = 'A', --a, ++ans;
    }
    cout << ans;
    return 0;
}