//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, a[51]; cin>>n>>k;
    for (int i = 0; i < n; ++i) cin>>a[i];
    sort(a, a+n, greater<>());
    a[n] = 0;//在数组末尾设置哨兵值0
    if (k > n) cout << -1 << '\n';
    else cout << a[k-1] << ' ' << 0 << '\n';//第k大元素
    return 0;
}