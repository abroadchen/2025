//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int n, ans, num[N];
char str[N];

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> str[i];
    for (int i = 0; i < n; ++i) num[i] = str[i] - '0';
    if (num[0] == 0) {
        cout << "1\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (num[i]&1) ans++;
        else if (num[i-1]==1&&num[i]==0) { ans++; break; }
        else break;
    }
    cout << ans << "\n";
    return 0;
}