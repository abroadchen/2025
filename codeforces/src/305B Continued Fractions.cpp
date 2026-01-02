#include <iostream>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll p, q, n, i, a; cin >> p >> q >> n;
    for (i = 0; i < n; ++i) {
        cin >> a;
        if (q == 0) break;
        if (a > p / q) break;
        p -= a * q;
        swap(p, q);
    }
    cout << (i < n || q != 0 ? "NO" : "YES");
    return 0;
}