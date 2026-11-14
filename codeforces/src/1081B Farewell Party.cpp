//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
读入每个 a[i]，然后 a[i] = n - a[i]（翻转一下），再按翻转后的值把下标 i 放进对应的桶 v[值]
每个桶 i 里的位置数必须能被 i 整除，否则输出 Impossible。
把桶 i 里的位置每 i 个划为一组，同一组内全部赋同一个编号 cnt，下一组 cnt 再 +1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 1e5+5;
int n, a[N], ans[N], cnt(1);
vector<int> v[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> a[i]; a[i] = n - a[i]; v[a[i]].push_back(i); }
    rep(i,n+1) {
        if (sz(v[i]) && sz(v[i])%i != 0) { cout << "Impossible"; return 0; }
        for (int j = 0; j < sz(v[i]); j += i) {
            rep(k,i) ans[v[i][j+k]] = cnt;
            cnt++;
        }
    }
    cout << "Possible" << '\n';
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}