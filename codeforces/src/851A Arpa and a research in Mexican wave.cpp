//
// Created by Psy.C on 2026/9/29.
//
/**
f(t)=
⎩
⎨
⎧
​

t
k
n+k−t
​

(0<=t<=k)
(k<t<n)
(n<=t<=n+k)
​

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, t; cin >> n >> k >> t;
    cout << (t < k ? t : t < n ? k : n+k-t);
    return 0;
}