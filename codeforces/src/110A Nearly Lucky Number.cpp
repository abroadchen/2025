//
// Created by Psy.C on 2025/11/14.
//

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; getline(cin, s);
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '4' || s[i] == '7')
            ++ans;
    }
    cout << ((ans == 4 || ans == 7) ? "YES" : "NO") << '\n';
    return 0;
}