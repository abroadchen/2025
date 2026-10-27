//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
n 扇门，力量 m。
p[i] 为每扇门的所需力
从最左（i=0）开始，只要 p[i] <= m 就打开并 sum++；一旦遇到 p[i] > m，break
左端无阻碍开到最右，则全部 n 扇都能打开
从最右端向左开门，能开则 sum++，遇到开不动就 break
如果左右两段没有重叠，则 i-1（左边最后一个能开的）和 j+1（右边最后一个能开的）不相邻或中间还有门，那么 sum = (左边开数) + (右边开数) 正好是总开数；
如果左右两段在中间重叠，这说明重叠的中间那些门左右都能推开，实际能开的门是连续的"左端到右端"整段都 ≤ m 的区间，sum 恰好是这个区间内门的总数。这个性质保证了直接相加不会重复计数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=0;i<n;i++)
#define per(i,n) for(i=n;i>=0;i--)
using namespace std;

constexpr int N = 105;

int n, m, sum, p[N], i, j;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> p[i];
    rep(i,n) {
        if (p[i] <= m) sum++;
        else break;
    }
    if (i == n) { cout << sum << '\n'; return 0; }
    per(j, n-1) {
        if (p[j] <= m) sum++;
        else break;
    }
    cout << sum << '\n';
    return 0;
}