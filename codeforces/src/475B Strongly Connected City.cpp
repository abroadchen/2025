//
// Created by Psy.C on 2026/2/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;



int main() {
    fast;
    int x; cin >> x >> x;
    string s1; cin >> s1;
    string s2; cin >> s2;
    const string s3 = {s1.front(), s1.back(), s2.front(), s2.back()};
    cout << (s3 == "<>v^" || s3 == "><^v" ? "YES" : "NO");
    return 0;
}