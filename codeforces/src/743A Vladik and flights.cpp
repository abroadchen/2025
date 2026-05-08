//
// Created by Psy.C on 2026/5/8.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
string s;
int n, a, b;
int main() {
    fast;
    while (cin >> n >> a >> b) {
        cin >> s;
        --a, --b;//1基索引到0基索引
        if (s[a] == s[b]) cout << "0\n";
        else cout << "1\n";
    }
    return 0;
}