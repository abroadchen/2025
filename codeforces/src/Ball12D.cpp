//
// Created by Psy.C on 2025/9/15.
//

#include <iosfwd>
#include <iostream>
#include <cstring>
#define rep(i,a) for(int i=0;i<a;++i)
using namespace std;
const int N = 500010;

struct node {
    int x, y, z;
} rec[N];

bool operator<(node a, node b) {
    return a.x != b.x ? a.x > b.x : a.y < b.y;
}
int h[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    rep(i,n) cin >> rec[i].x;
    rep(i,n) cin >> rec[i].y, h[i] = rec[i].y;
    rep(i,n) cin >> rec[i].z;
    sort(h, h + n);
    sort(rec, rec + n);
    rep(i,n) rec[i].y = n - (lower_bound(h, h + n, rec[i].y) - h);

    memset(h, 128, sizeof(h));
    int ans = 0;
    rep(i,n) {
        int tmp = -0x7fffffff;
        for (int j = rec[i].y - 1; j; j -= j & -j) tmp = max(tmp, h[j]);
        if (tmp > rec[i].z) ans++;
        for (int j = rec[i].y; j <= n; j += j & -j) h[j] = max(h[j], rec[i].z);
    }
    cout << ans << endl;
    return 0;
}