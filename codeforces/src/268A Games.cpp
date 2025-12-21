//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, cnt = 0; cin>>n;
    vector<int> h(n), a(n);
    for (int i = 0; i < n; ++i) {
        cin>>h[i]>>a[i];
        for (int j = 0; j < i; ++j) {
            if (h[i] == a[j]) cnt++;
            if (a[i] == h[j]) cnt++;
        }
    }
    cout<<cnt<<'\n';
    return 0;
}