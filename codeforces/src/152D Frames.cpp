//
// Created by Psy.C on 2025/11/23.
//

#include <algorithm>
#include <ios>
#include <iostream>
#include <set>
#include <vector>
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef pair<int,int> ii;
constexpr int N = 1010, M = 2010;
int n, m, sum;
char buf[N];
bool isf[N][N], ok[M][M], nok[M][M], f[M][M];
vector<ii> v;
set<ii> st, stt;

bool check(ii a, ii b) {
    int mnx = min(a.first, b.first), mxx = max(a.first, b.first),
    mny = min(a.second, b.second), mxy = max(a.second, b.second);
    if (mxx - mnx < 2 || mxy - mny < 2) return false;
    for (int i = mny; i <= mxy; ++i) {
        if (!isf[mnx][i]) return false;
        st.insert({mnx, i});
    }
    for (int i = mny; i <= mxy; ++i) {
        if (!isf[mxx][i]) return false;
        st.insert({mxx, i});
    }
    for (int i = mnx; i <= mxx; ++i) {
        if (!isf[i][mny]) return false;
        st.insert({i, mny});
    }
    for (int i = mnx; i <= mxx; ++i) {
        if (!isf[i][mxy]) return false;
        st.insert({i, mxy});
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    rep(i,n) {
        cin >> buf[i];
        for (int j = 0; j < m; ++j) if (buf[j] == '#') {
            isf[i][j+1] = true;
            sum++;
        }
    }
    rep(i,n) rep(j,m) if (isf[i][j]) {
        if ((isf[i-1][j]+isf[i+1][j]==1) || (isf[i][j-1]+isf[i][j+1]==1) ||
            (isf[i-1][j]+isf[i+1][j]+isf[i][j-1]+isf[i][j+1]==4)) ok[i][j] = true;
    }
    rep(i,n) {
        int s = 0;
        rep(j,m) if (ok[i][j]) {
            s++;
            if (s <= 2) nok[i][j] = true;
        }
        s = 0;
        for (int j = m; j >= 1; --j) if (ok[i][j]) {
            s++;
            if (s <= 2) nok[i][j] = true;
        }
    }
    rep(i,n) rep(j,m) {
        ok[i][j] = nok[i][j];
        nok[i][j] = false;
    }
    rep(j,m) {
        int s = 0;
        rep(i,n) if (ok[i][j]) {
            s++;
            if (s <= 2) nok[i][j] = true;
        }
        s = 0;
        for (int i = n; i >= 1; --i) if (ok[i][j]) {
            s++;
            if (s <= 2) nok[i][j] = true;
        }
    }
    rep(i,n) rep(j,m) if (nok[i][j]) v.emplace_back(i,j);
    if (v.size() > 1000) { cout << "NO"; return 0; }
    for (int i = 0; i + 1 < v.size(); ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            if (check(v[i],v[j])) f[i][j] = true;
        }
    }
    for (int i = 0; i + 1 < v.size(); ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            if (!f[i][j]) continue;
            st.clear();
            check(v[i],v[j]);
            stt = st;
            for (int k = i; k + 1 < v.size(); ++k) {
                for (int l = k + 1; l < v.size(); ++l) {
                    if (!f[k][l]) continue;
                    st = stt;
                    check(v[k],v[l]);
                    if (st.size() == sum) {
                        cout << "YES" << '\n';
                        cout << min(v[i].first, v[j].first) << ' ' <<
                            min(v[i].second, v[j].second) << ' ' <<
                                max(v[i].first, v[j].first) << ' ' <<
                                    max(v[i].second, v[j].second) << '\n';
                        cout << min(v[k].first, v[l].first) << ' ' <<
                            min(v[k].second, v[l].second) << ' ' <<
                                max(v[k].first, v[l].first) << ' ' <<
                                    max(v[k].second, v[l].second);
                        return 0;
                    }
                }
            }
        }
    }
    cout << "NO";
    return 0;
}