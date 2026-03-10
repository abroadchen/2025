//
// Created by Psy.C on 2026/3/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '0') {
            cout << "YES\n0\n";
            return 0;
        }
        if (s[i] == '8') {
            cout << "YES\n8\n";
            return 0;
        }
    }
    for (int i = 0; i < s.size(); ++i)
        for (int j = i + 1, p; j < s.size(); ++j) {
            p = (s[i] - '0')*10 + (s[j] - '0');
            if (p%8 == 0) {
                cout << "YES\n" << p << '\n';
                return 0;
            }
        }
    for (int i = 0; i < s.size(); ++i)
        for (int j = i + 1; j < s.size(); ++j)
            for (int k = j + 1, p; k < s.size(); ++k) {
                p = (s[i] - '0')*100 + (s[j] - '0')*10 + (s[k] - '0');
                if (p%8 == 0) {
                    cout << "YES\n" << p << '\n';
                    return 0;
                }
            }
    cout << "NO\n";
    return 0;
}