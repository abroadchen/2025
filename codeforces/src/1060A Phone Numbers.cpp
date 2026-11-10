//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
while (cin >> n)：多组测试用例，持续读入直到 EOF。
cin >> s：读入 n 位数字串。
循环统计 cnt = 该串中字符 '8' 的个数。
ans = n/11：长度上限——11 个字符组成 1 个号码，n 个字符最多 n/11 个号码。
输出 min(cnt, ans)：取两者较小值，即真正能组成的最大个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 101;

int n;
char s[N];
int main() {
    fast;
    while (cin >> n) {
        int cnt = 0; cin >> s;
        for (int i = 0; i < n; i++)
            if (s[i] == '8') cnt++;
        int ans = n/11;
        cout << min(cnt, ans) << '\n';
    }
    return 0;
}