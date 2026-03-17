//
// Created by Psy.C on 2026/3/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+1, M = 1e3+1;
int n, p[N][2], ans[M];
bool used[M];
int main() {
    fast;
    cin >> n; n<<=1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j < i; ++j) {
            cin >> x;
            p[x][0] = i, p[x][1] = j;//将配对关系存储到p[x]中
        }
    //设置used[0]为已使用（可能是防止访问索引0）
    used[0] = 1;
    for (int i = N-1; i > 0; --i) {
        if (!used[p[i][0]] && !used[p[i][1]]) {
            used[p[i][0]] = 1; used[p[i][1]] = 1;
            ans[p[i][0]] = p[i][1];//建立配对关系 相互指向对方
            ans[p[i][1]] = p[i][0];
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';//每个位置的配对对象
    return 0;
}