//
// Created by Psy.C on 2026/3/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x;
int main() {
    fast;
    cin>>x;
    if (x%5==0) cout << x/5 << '\n';
    else cout << x/5+1 << '\n';
    return 0;
}