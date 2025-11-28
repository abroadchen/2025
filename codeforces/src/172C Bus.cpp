//
// Created by Psy.C on 2025/11/28.
//

#include <iomanip>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 123457, M = 555555;
int n, dep[M];
vector<int> v[N];
double ans;

void dfs(const int x, const int p=-1) {
    for (const auto y : v[x]) {
        if (y != p) {
            dep[y] = dep[x] + 1;
            dfs(y, x);
        }
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 0, a, b; i < n - 1; ++i) {
        cin >> a >> b;
        v[a - 1].push_back(b - 1);
        v[b - 1].push_back(a - 1);
    }
    dfs(0);
    for (int i = 1; i <= n; ++i) ans += 1. / (dep[i] + 1);
    cout << fixed << setprecision(17) << ans;
    return 0;
}