//
// Created by Psy.C on 2025/9/17.
//

#include <ios>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;

const int maxn = 2007;
int t[maxn], v[maxn];
ll f[maxn << 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    int maxt = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> v[i];
        t[i]++;
        maxt = max(maxt, t[i]);
    }
    maxt += n;

    memset(f, 0x7f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = maxt; j >= t[i]; --j)
            f[j] = min(f[j], f[j - t[i]] + v[i]);


    ll ans = 2e12 + 7;
    for (int i = n; i <= maxt; ++i)
        if (f[i] < ans)
            ans = f[i];
    cout << ans << endl;
    return 0;
}