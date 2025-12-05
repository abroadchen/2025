//
// Created by Psy.C on 2025/12/4.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int main() {
    fast;
    int n, a[N]; cin>>n;
    double ans = 0., sum = 0.;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    ans = sum / n;
    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}