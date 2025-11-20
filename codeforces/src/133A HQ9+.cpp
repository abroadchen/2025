//
// Created by Psy.C on 2025/11/19.
//

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    string ans = "NO";
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'H' || s[i] == 'Q' || s[i] == '9') {
            ans = "YES";
            break;
        }
    }
    cout << ans;
    return 0;
}