//
// Created by Psy.C on 2026/2/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1;
char s[N];
int main() {
    fast;
    cin >> s;
    const int len = strlen(s);
    int cnt = 0;
    for (int i = len-1; i >= 0; --i) {
        if (s[i] == ')') cnt++;
        if (s[i] == '(') {
            cnt--;
            if (cnt < 0) {
                cout << "-1\n";
                return 0;
            }
        }
        if (s[i] == '#') break;
    }
    cnt = 0;
    int tot = 0;
    for (int i = 0; i < len; ++i) {
        if (s[i] == '(') cnt++;
        if (s[i] == ')' || s[i] == '#') {
            cnt--;
            if (s[i] == '#') tot++;
            if (cnt < 0) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    for (int i = 0; i < tot-1; ++i) cout << "1\n";
    cout << cnt+1 << '\n';
    return 0;
}