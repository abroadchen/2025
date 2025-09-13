//
// Created by Psy.C on 2025/9/12.
//


#include <iostream>
#include <vector>
using namespace std;

static const int MAXN=10;
int n, a, b, ans, h[MAXN+10];
vector<int> v;
vector<int> res;


void dfs(int pos, int cnt, int t1, int t2) {
    if (pos == n && h[n] - t2 < 0) {
        if (ans > cnt) {
            ans = cnt;
            res.clear();
            for (int i = 0; i < v.size(); ++i) res.push_back(v[i]);
        }
        return;
    }
    if (cnt >= ans || pos >= n) return;
    for (int i = max(0, (h[pos - 1] - t1 >= 0) ? (h[pos - 1] - t1)/b + 1 : 0);
        i <= max((h[pos - 1] - t1 >= 0) ? (h[pos - 1] - t1)/b + 1 : 0,
            max((h[pos] - t2 >= 0) ? (h[pos] - t2)/a + 1 : 0, (h[pos + 1] >= 0) ? h[pos + 1]/b + 1 : 0));
            ++i) {
        for (int j = 1; j <= i; j++) v.push_back(pos);
        dfs(pos + 1, cnt + i, t2 + i * a, i * b);
        for (int j = 1; j <= i; j++) v.pop_back();
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) cin >> h[i];
    ans = 0x3f3f3f3f;
    dfs(2, 0, 0, 0);
    cout << ans << endl;
    for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << endl;
    return 0;
}