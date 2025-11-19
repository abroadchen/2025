//
// Created by Psy.C on 2025/11/19.
//

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s; int cnt(0);
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') cnt += 1;
    }
    if (cnt == s.length() - 1) {
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] >= 65 && s[i] <= 90) s[i] += 32;
            else if (s[i] >= 97 && s[i] <= 122) s[i] -= 32;
        }
    }
    cout << s << '\n';
    return 0;
}