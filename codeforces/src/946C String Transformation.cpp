//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

string s;
char a = 'a';
int main() {
    fast;
    cin >> s;
    rep(i,s.length()) {
        if (s[i] <= a) {
            s[i] = a; a++;
            if (a > 'z') break;
        }
    }
    if (a <= 'z') { cout << "-1"; return 0; }
    cout << s;
    return 0;
}