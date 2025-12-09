//
// Created by Psy.C on 2025/12/8.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
using namespace std;

int a[N], b[N];

int main() {
    fast;
    int n, cnt = 0; cin>>n;
    for (int i = 0; i < n; ++i) { cin>>a[i]; b[i] = a[i]; }
    sort(b, b+n);
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) cnt++;
    if (cnt <= 2) cout<<"YES\n";
    else cout<<"NO\n";
    return 0;
}