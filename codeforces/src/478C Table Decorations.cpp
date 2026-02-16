//
// Created by Psy.C on 2026/2/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a[3];
int main() {
    fast;
    for (ll& i : a) cin >> i;
    sort(a, a + 3);//a[0] ≤ a[1] ≤ a[2]
    a[2] = min((a[1]+a[0])<<1, a[2]);//任意两边之和大于第三边
    cout << (a[0]+a[1]+a[2])/3 << '\n';//最大三角形数量 每个三角形需要3条边
    return 0;
}