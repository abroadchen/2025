//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
读入字符串 s，len 为长度。
后面要确定的 a（行数）、b（列数），c 是需要补的 * 个数
b = ⌈len/a⌉：把字符串平均分到 a 行，每行 b 个字符。
c = a*b - len：总容量 a*b 比实际长度多出的空格数（用 * 填充）。
条件：列数 b 不超过 20，且补的数量 c 不超过一行 a，能满足就退出，否则换更大的 a（保证每一行末尾的 * 都最后放）。
输出 a 和 b
每一行先输出前 b-(c!=0) 个字符：若还有未补的 c（c!=0 为真，即 b-1 个），否则输出 b 个。
若还有 c 没补完，则在该行末尾补一个 * 并让 c--。
由于前面保证了 c ≤ a，所以 * 只出现在后面若干行的末尾，且每行至多一个，符合题意（把多出来的 * 放在最后一列）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    int len = s.size(), a, b, c;
    rep(a,5) {
        b = len/a + (len%a != 0); c = a*b-len;
        if (b <= 20 && c <= a) break;
    }
    cout << a << ' ' << b << '\n';
    int pos = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b-(c!=0); j++) cout << s[pos++];
        if (c) cout << "*", c--;
        cout << '\n';
    }
    return 0;
}