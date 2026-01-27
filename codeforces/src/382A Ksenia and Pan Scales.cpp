//
// Created by Psy.C on 2026/1/26.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    string s1, s2; cin >> s1 >> s2;
    string ls, rs;//存储左右部分
    ll idx = 0;//管道符的位置
    for (ll i = 0; i < s1.length(); ++i) if (s1[i] == '|') {
        idx = i; break;
    }
    for (ll i = 0; i < idx; ++i) ls += s1[i];
    for (ll i = idx + 1; i < s1.length(); ++i) rs += s1[i];
    const ll l = static_cast<ll>(ls.length()),
    r = static_cast<ll>(rs.length()),
    tot = l + r + static_cast<ll>(s2.length()), t = abs(l - r);
    if (t <= s2.length() && tot % 2 == 0) {
        ls += s2.substr(0, (tot>>1) - l);
        rs += s2.substr((tot>>1) - l, (tot>>1) - r);
        cout << ls << '|' << rs << '\n';
    } else cout << "Impossible\n";
    return 0;
}