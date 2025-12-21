//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, r = 0, g = 0, b = 0; cin >> n;
    string s; cin >> s;
    for (int i = 1; i < n; ++i) {
        if (s[i-1] == s[i]) {
            if (s[i] == 'R') ++r;//相邻重复对数
            else if (s[i] == 'G') ++g;
            else if (s[i] == 'B') ++b;
        }
    }
    cout << r + g + b;//所有相邻重复对的总数
    return 0;
}