//
// Created by Psy.C on 2025/11/18.
//

#include <vector>
#include <iostream>
using namespace std;


int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    vector<int> a(n);
    int od(0), ev(0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] % 2 != 0) od++;
    }
    ev = n - od;
    if (od % 2 == 0) cout << ev << '\n';
    else if (od % 2 != 0) cout << od << '\n';
    return 0;
}