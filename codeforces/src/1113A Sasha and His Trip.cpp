//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
n = 城市数（要走的里程是 n-1），v = 出发时油箱里的油量
情况一：油箱够直接开到终点
情况二：油不够，需要中途买油
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, v;
int main() {
    fast;
    cin >> n >> v;
    if (v >= n-1) cout << n-1;
    else cout << (n+n*n+v*v+v)/2-n*v-1;
    return 0;
}