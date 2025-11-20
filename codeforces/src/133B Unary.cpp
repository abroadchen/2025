//
// Created by Psy.C on 2025/11/19.
//

#include <iostream>
#include <map>
using namespace std;

const int mod = 1e6+3;
map<char, int> mp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    mp['>'] = 8; mp['<'] = 9; mp['+'] = 10;
    mp['-'] = 11; mp['.'] = 12; mp[','] = 13;
    mp['['] = 14; mp[']'] = 15;
    int len = s.size(), sum = 0;
    for (int i = 0; i < len; ++i)
        sum = ((sum * 16) % mod + mp[s[i]]) % mod;
    cout << sum << '\n';
    return 0;
}