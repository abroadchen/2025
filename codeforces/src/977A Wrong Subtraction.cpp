//
// Created by Psy.C on 2026/10/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, k;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        if (n%10 != 0) n -= 1;//个位非 0 → n 减 1
        else n/=10;//个位为 0 → 删掉末位（整除 10）
    }
    cout << n << '\n';
    return 0;
}