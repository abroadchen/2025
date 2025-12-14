//
// Created by Psy.C on 2025/12/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;


int main() {
    fast;
    int n, k; cin>>n>>k;
    int c[N], s[N], p = 0, ans = 0, mx = 0;
    for (int i = 0; i < n; ++i) cin>>c[i];
    for (int i = 0; i < n; ++i) cin>>s[i];
    for (int i = 0; i < n; ++i) {
        p += s[i] - c[i];//更新累积差值（收益减成本）
        ans += c[i];//累加成本到总答案
        if (i == 0 || mx < s[i]) mx = s[i];
        while (p < 0) { ans += k; p += mx; }//付出代价k
    }
    cout<<ans;
    return 0;
}