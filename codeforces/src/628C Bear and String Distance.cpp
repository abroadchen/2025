//
// Created by Psy.C on 2026/3/28.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, k;
char s[N];
int main() {
    fast;
    cin >> n >> k >> s;
    int num = 0;
    for (int i = 0; i < n; ++i) num += max(s[i] - 'a', 'z' - s[i]);
    if (k > num) cout << "-1\n";
    else {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum = max(s[i] - 'a', 'z' - s[i]);
            if (sum <= k) {
                k -= sum;
                if (s[i] - 'a' > 'z' - s[i]) s[i] = 'a';
                else s[i] = 'z';
            } else if (sum > k && k != 0) {
                if (s[i] - 'a' >= k) s[i] -= k;
                else s[i] += k;
                k = 0;
            }
            cout << s[i];
        }
    }
    return 0;
}