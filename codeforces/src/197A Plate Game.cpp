//
// Created by Psy.C on 2025/12/3.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, r; cin>>a>>b>>r;
    const int d = r * 2;
    if (a < d || b < d) cout << "Second\n";
    else cout << "First\n";
    return 0;
}