//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int main() {
    fast;
    ll w, h; cin >> w >> h;
    cout << (w * w - w % 2) * (h * h - h % 2) / 16;
    return 0;
}