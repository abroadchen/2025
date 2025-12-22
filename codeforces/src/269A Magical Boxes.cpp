//
// Created by Psy.C on 2025/12/21.
//
/*
 * 4为底的对数的上界，即找到最小的m使得4^m ≥ a
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, mx = 0; cin>>n;
    while(n--) {
        int k, a, t = 1, m = 0; cin>>k>>a;
        while (t < a) { t *= 4; ++m; }//需要多少步才能使t >= a
        if (mx < k + m) mx = k + m;//当前的k+m大于记录的最大值mx，则更新mx
        if (mx == k) ++mx;
    }
    cout<<mx<<"\n";
    return 0;
}