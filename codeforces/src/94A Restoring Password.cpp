//
// Created by Psy.C on 2025/11/10.
//

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    string s; getline(cin, s);
    map<string, int> mp;
    for (int i = 0; i < 10; ++i) {
        string t; getline(cin, t);
        mp.insert(pair<string, int>(t, i));
    }
    for (int i = 0; i < 8; ++i) {
        string t = s.substr(10*i, 10);
        cout << mp[t];
    }
    cout << '\n';
    return 0;
}