//
// Created by Psy.C on 2026/10/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    if (a > b) swap(a, b);
    int mid = (a+b)>>1, la = mid-a, lb = b-mid,
    pa = (la+1)*la/2, pb = (lb+1)*lb/2;
    cout << pa+pb << '\n';
    return 0;
}