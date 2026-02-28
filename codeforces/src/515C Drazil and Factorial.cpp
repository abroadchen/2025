//
// Created by Psy.C on 2026/2/28.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 16;

int n;
char s[N], x[N][N] = {
    "", "", "2", "3", "322", "5", "53", "7", "7222", "7332"
}, ans[101];
int main() {
    fast;
    cin >> n;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int len = strlen(x[s[i]-'0']);
        for (int j = 0; j < len; ++j)
            ans[cnt++] = x[s[i]-'0'][j];
    }
    sort(ans, ans + cnt); reverse(ans, ans + cnt);
    for (int i = 0; i < cnt; ++i) cout << ans[i];
    cout << '\n';
    return 0;
}