//
// Created by Psy.C on 2025/12/15.
//

#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10001
using namespace std;


int main() {
    fast;
    int n, a[N]; cin >> n;
    set<int> s;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        int cur = a[i], val = 0;
        for (int j = i + 1; j <= n; ++j) {
            cur |= a[j];
            val |= a[j];
            s.insert(cur);
            if (cur == val) break;
        }
        s.insert(a[i]);
    }
    cout << s.size() << '\n';
    return 0;
}