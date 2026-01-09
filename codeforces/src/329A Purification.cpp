//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define N 109
using namespace std;


int main() {
    fast;
    int n; cin >> n; char a[N][N];
    rep(i,n) rep(j,n) cin >> a[i][j];
    vector<ii> v;
    rep(i,n) rep(j,n) if (a[i][j] == '.') {
        v.emplace_back(i, j); break;//每行找第一个'.'
    }
    if (v.size() == n) {//每行都有'.' 除非n=1
        for (auto [fst, snd] : v) {
            cout << fst << ' ' << snd << '\n';
        }
        return 0;
    }
    v.clear();
    rep(i,n) rep(j,n) if (a[j][i] == '.') {
        v.emplace_back(j, i); break;
    }
    if (v.size() == n) {
        for (auto [fst, snd] : v) {
            cout << fst << ' ' << snd << '\n';
        }
        return 0;
    }
    cout << -1;
    return 0;
}