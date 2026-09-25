//
// Created by Psy.C on 2026/9/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int s, v1, v2, t1, t2;
int main() {
    fast;
    cin >> s >> v1 >> v2 >> t1 >> t2;
    int s1 = t1*2+s*v1, s2 = t2*2+s*v2;
    if (s1 < s2) cout << "First\n";
    if (s1 > s2) cout << "Second\n";
    if (s1 == s2) cout << "Friendship\n";
    return 0;
}