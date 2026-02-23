//
// Created by Psy.C on 2026/2/21.
//
///O(n×m)，每个位置最多被访问常数次
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int n, m;
char s[N][N];
bool vis[N];//哪些行被保留
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    int cnt = 0;
    for (int j = 0; j < m; ++j) {//确保每列都是非递减的
        bool flag = true;
        for (int i = 0; i < n; ++i) {//遍历相邻行对 (i, i+1)
            if (i + 1 < n && !vis[i+1])//下一行未被标记为保留
                if (s[i+1][j] < s[i][j]) {//存在逆序，需要删除一行
                    cnt++;
                    flag = false;
                    break;
                }
        }
        if (flag) {
            for (int i = 0; i < n; ++i) {
                if (i + 1 < n && !vis[i+1])
                    if (s[i+1][j] > s[i][j])
                        vis[i+1] = true;//标记那些与上一行相比更大的行
            }
        }
    }
    cout << cnt << '\n';
    return 0;
}