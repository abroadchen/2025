//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, k; cin >> n >> k;
    vector<ll> a(n<<1|1);
    //a[1] = 1, a[2] = 2, ..., a[2*n] = 2*n
    for (int i = 1; i <= n<<1; ++i) a[i] = i;//i 个位置设为 i
    for (int i = 1; i <= k; ++i) swap(a[(i<<1)-1], a[i<<1]);//交换相邻两个元素
    for (int i = 1; i <= n<<1; ++i) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}