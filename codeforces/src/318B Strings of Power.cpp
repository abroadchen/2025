//
// Created by Psy.C on 2026/1/7.
//

#include <iostream>
#include <string>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


string str2 = "metal", str1 = "heavy";
int main() {
    fast;
    string s; cin >> s;
    const ll l = static_cast<ll>(s.size()); ll hv = 0, cnt = 0;
    for (int i = 0; i < l; ++i) {
        if (s.substr(i, 5) == str1) hv++;
        else if (s.substr(i, 5) == str2) cnt += hv;//将当前hv值加到cnt
    }
    cout << cnt << '\n';
    return 0;
}