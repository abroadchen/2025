//
// Created by Psy.C on 2025/9/18.
//

#include <ios>
#include <iostream>
using namespace std;
typedef long long ll;
int f[100005], sum, now, n, a[100005];
ll ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    f[0] = ans = now = sum = 0; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 3 != 0) {
        cout << "0" << endl;
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        now += a[i];
        f[i] = f[i - 1] + (now * 3 == sum);
    }
    now = 0;

    for (int i = n; i > 2; --i) {
        now += a[i];
        if (now * 3 == sum) {
            if (sum == 0) ans += f[i - 2];
            else ans += f[i - 1];
        }
    }

    cout << ans << endl;
    return 0;
}