//
// Created by Psy.C on 2026/3/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 8;
int w, b;
string s;
int main() {
    fast;
    for (int j = 0; j < N; ++j) {
        cin >> s;
        for (int i = 0; i < N; ++i) {
            if (s[i] == 'Q') w += 9;
            else if (s[i] == 'R') w += 5;
            else if (s[i] == 'B' || s[i] == 'N') w += 3;
            else if (s[i] == 'P') w += 1;
            else if (s[i] == 'q') b += 9;
            else if (s[i] == 'r') b += 5;
            else if (s[i] == 'b' || s[i] == 'n') b += 3;
            else if (s[i] == 'p') b += 1;
        }
    }
    if (w > b) cout << "White\n";
    else if (w < b) cout << "Black\n";
    else cout << "Draw\n";
    return 0;
}