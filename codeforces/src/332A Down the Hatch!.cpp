//
// Created by Psy.C on 2026/1/10.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, g = 0; string s; cin >> n >> s;
    for (int i = n; i < s.length(); i += n) {
        if (s[i-1] == s[i-2] && s[i-2] == s[i-3]) ++g;
    }
    cout << g << '\n';
    return 0;
}