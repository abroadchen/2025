//
// Created by Psy.C on 2026/4/15.
//
/**
上方向：如果字符串包含'1','2','3'，说明不需要向上移动（u=0）
左方向：如果字符串包含'1','4','7','0'，说明不需要向左移动（l=0）
下方向：如果字符串包含'7','9','0'，说明不需要向下移动（d=0）
右方向：如果字符串包含'6','9','3','0'，说明不需要向右移动（r=0）
如果还有任何一个方向标志为1，说明该方向是必需的，输出"NO"
否则：所有方向都不是必需的，输出"YES"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, l, r, u, d;
char s[N];
int main() {
    fast;
    cin >> n; cin >> s; l = r = u = d = 1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1' || s[i] == '2' || s[i] == '3') u = 0;
        if (s[i] == '1' || s[i] == '4' || s[i] == '7' || s[i] == '0') l = 0;
        if (s[i] == '7' || s[i] == '9' || s[i] == '0') d = 0;
        if (s[i] == '6' || s[i] == '9' || s[i] == '3' || s[i] == '0') r = 0;
    }
    if (d || u || l || r) cout << "NO\n"; else cout << "YES\n";
    return 0;
}