//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
含义（这里 l[i] = n，是所有串的长度，恰好等于转轮次数 n）：

mp[i][c] = 第 i 个人字符串中字符 c 的出现次数。
l[i] - mp[i][c] = 不等于 c 的其他字符个数，即最多可以通过 n 次修改把多少个其他字符改成 c。
t = n - (l[i] - mp[i][c]) = 即使把其他所有字符都改成 c，还剩下多少次转动可以用在"已经是 c 的字符"上。
分情况：

t >= 0：说明 n 次足够把所有非 c 字符都变成 c，最多能做到全串都是 c，即 l[i] 个。
特判：若原串全部都是 c（mp[i][c]==l[i]）且 t==1（即 n==1），那么必须转一次，把唯一一个 c 改成别的，结果只剩 l[i]-1 个 c。
否则返回 l[i]。
t < 0：即使把所有非 c 都改了也不够 n 次，多余次数只能浪费在已改过的字符上，最终最多 n + mp[i][c] 个相同字符。若这个超过 n 就取 l[i]（由外层对该值封顶，实际不会超，因为 n+mp≤n+n，但 mp≤n 所以 ≤2n……实际最终外层用 s[i] 比较，而 n+mp[i][c] 可能超过 n）。

循环读入直到 EOF。每次读入长度 n 和三个人的字符串。
统计每个字符串中每个字符（含大小写）的出现次数到 mp[i][c]
对每个字符 ch（小写+大写，共 52 个），计算每个人把它做到最多能有多少个相同字符，取每个人各自的最大值存入 s[i]
找 s[i] 的最大值 mx，统计达到最大的人数 cnt。
若 cnt ≥ 2（并列）→ 输出 Draw。
否则输出唯一的胜者名字：0→Kuro、1→Shiro、2→Katie

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+1e2;

int n, l[3];
map<char, int> mp[3];
int get(int i, char c) {
    int t = n - (l[i] - mp[i][c]);
    if (t >= 0) {
        if (mp[i][c] == l[i] && t == 1) return l[i]-1;
        return l[i];
    }
    return n+mp[i][c];
}

map<int, int> m;
int s[3], i, j;
char str[3][N];
int main() {
    fast;
    while (cin >> n) {
        m.clear(); memset(s, 0, sizeof(s));
        for (i = 0; i < 3; ++i) {
            mp[i].clear(); cin >> str[i]; l[i] = strlen(str[i]);
            for (j = 0; str[i][j]; ++j) ++mp[i][str[i][j]];
        }
        for (char ch = 'a'; ch <= 'z'; ++ch) for (i = 0; i < 3; ++i)
            s[i] = max(s[i], get(i, ch));
        for (char ch = 'A'; ch <= 'Z'; ++ch) for (i = 0; i < 3; ++i)
            s[i] = max(s[i], get(i, ch));
        int mx = 0;
        for (i = 0; i < 3; ++i) { mx = max(mx, s[i]); ++m[s[i]]; }
        int cnt = 0, ans = 0;
        for (i = 0; i < 3; ++i) if (s[i] == mx) { ++cnt; ans = i; }
        if (cnt >= 2) cout << "Draw\n";
        else {
            switch (ans) {
                case 0: cout << "Kuro\n"; break;
                case 1: cout << "Shiro\n"; break;
                case 2: cout << "Katie\n"; break;
            }
        }
    }
    return 0;
}