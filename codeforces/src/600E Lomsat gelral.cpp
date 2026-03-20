//
// Created by Psy.C on 2026/3/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

int c[N];
ll cl[N], mx, sum;
void dfs(int pos, int fa, int p) {
    cl[c[pos]]++;
    if (cl[c[pos]] > mx) mx = cl[c[pos]], sum = c[pos];
}

int main() {
    fast;

    return 0;
}