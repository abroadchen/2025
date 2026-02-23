//
// Created by Psy.C on 2026/2/20.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, v[] = {
    2, 7, 2, 3, 3, 4, 2, 5, 1, 2
};
int main() {
    fast;
    cin >> n;
    cout << v[n/10]*v[n%10];
    return 0;
}