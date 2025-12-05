//
// Created by Psy.C on 2025/12/5.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin>>a[i];
    ll cnt = 0;
    for (int i = 1; i < n; ++i) {//当前元素a[i]小于前一个元素a[i-1]（即出现递减）
        if (a[i] < a[i-1]) cnt += a[i-1] - a[i];
    }
    cout << cnt;
    return 0;
}