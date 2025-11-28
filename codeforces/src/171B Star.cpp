//
// Created by Psy.C on 2025/11/28.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    ll n; cin>>n;
    cout << 6 * n * (n - 1) + 1 << '\n';
    return 0;
}