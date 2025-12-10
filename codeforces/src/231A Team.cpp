//
// Created by Psy.C on 2025/12/10.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, cnt = 0; cin>>n;
    for (int i = 0, a, b, c, t; i < n; ++i) {
        cin>>a>>b>>c; t = a+b+c;
        if (t > 1) cnt++;
    }
    cout<<cnt;
    return 0;
}