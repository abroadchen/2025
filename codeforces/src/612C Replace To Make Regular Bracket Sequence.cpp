//
// Created by Psy.C on 2026/3/24.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

bool ok(char r, char l) {
    return (r == '}' && l != '{') || (r == '>' && l != '<') ||
            (r == ')' && l != '(') || (r == ']' && l != '[');
}

char s[N], t[N];
int main() {
    fast;
    cin >> s;
    int ans = 0, k = 0, cnt = 0;
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '{' || s[i] == '<' || s[i] == '(' || s[i] == '[')
            t[k++] = s[i];
        else {
            if (k == 0) { ans = -1; break; }
            if (ok(s[i], t[k-1])) cnt++;
            k--;
        }
    }
    if (k != 0 || ans == -1) cout << "Impossible\n";
    else cout << cnt << '\n';
    return 0;
}