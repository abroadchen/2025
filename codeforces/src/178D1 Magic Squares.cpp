//
// Created by Psy.C on 2025/11/30.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 100, M = 5;
int n, m, arr[N];

int h[M], l[M], mp[M][M];
bool ok() {
    for (int i = 1; i <= n; ++i) {
        if (h[i] != m) return false;
        if (l[i] != m) return false;
    }
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n; ++i) {
        sum1 += mp[i][i];
        sum2 += mp[i][n - i + 1];
    }
    if (sum1 != m || sum2 != m) return false;
    return true;
}

bool vis[N];
void dfs(const int x) {
    if (x > n * n) {
        if (ok()) {
            cout << m << '\n';
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j)
                    cout << mp[i][j] << ' ';
                cout << '\n';
            }
            exit(0);
        }
        return;
    }
    const int nx = (x - 1) / n + 1, ny = (x - 1) % n + 1;
    for (int i = 1; i <= n * n; ++i) {
        if (!vis[i]) {
            if (nx == n) if (l[ny] + arr[i] != m) continue;
            if (ny == n) if (h[nx] + arr[i] != m) continue;
        }
        h[nx] += arr[i], l[ny] += arr[i], vis[i] = true, mp[nx][ny] = arr[i];
        dfs(x + 1);
        h[nx] -= arr[i], l[ny] -= arr[i], vis[i] = false;
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n * n; ++i) cin >> arr[i], m += arr[i];
    m /= n;
    dfs(1);
    return 0;
}