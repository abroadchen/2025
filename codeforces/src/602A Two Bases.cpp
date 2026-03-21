//
// Created by Psy.C on 2026/3/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n1, m1, n2, m2, x;
ll s1, s2;
int main() {
    fast;
    cin >> n1 >> m1;
    for (int i = 0; i < n1; ++i) {
        cin >> x; s1 = s1*m1 + x;
    }
    cin >> n2 >> m2;
    for (int i = 0; i < n2; ++i) {
        cin >> x; s2 = s2*m2 + x;
    }
    if (s1 > s2) cout << ">\n";
    else if (s1 < s2) cout << "<\n";
    else cout << "=\n";
    return 0;
}