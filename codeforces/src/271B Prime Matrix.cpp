//
// Created by Psy.C on 2025/12/22.
//O(n×m×log(素数个数) + n×log(n) + m×log(m))

/*
*pri数组：存储找到的所有素数
num：记录已找到的素数个数
 *
*lower_bound(pri, pri + num, w[i][j])：在pri数组中查找第一个大于等于w[i][j]的元素位置
减去pri得到相对于数组起始位置的偏移量
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 100010
#define M 502
using namespace std;

bool vis[N];
int pri[N], num;
void f() {//生成素数表(埃拉托斯特尼筛法的优化版本)
    memset(vis,false,sizeof(vis));//假设所有数都是素数
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) pri[num++] = i;
        for (int j = 0; j < num && i * pri[j] < N; ++j) {//对当前数i，用它与已找到的每个素数相乘，标记这些乘积为合数
            vis[i * pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
    vis[1] = vis[0] = true;//需要变成素数的数
}


int main() {
    fast;
    int n, m, w[M][M], a[M], b[M]; cin >> n >> m; f();
    rep(i,n) rep(j,m) {
        cin >> w[i][j];//矩阵第i行第j列的元素值。
        if (vis[w[i][j]]) {//大于等于w[i][j]的最小素数
            const int t = static_cast<int>(lower_bound(pri, pri + num, w[i][j]) - pri);
            a[i] += pri[t] - w[i][j];//第i行需要的操作数 将w[i][j]变成素数pri[t]需要pri[t]-w[i][j]次操作
            b[j] += pri[t] - w[i][j];//第j列需要的操作数
        }
    }
    sort(a + 1, a + 1 + n); sort(b + 1, b + 1 + m);
    const int ans = min(a[1], b[1]);
    cout << ans << "\n";
    return 0;
}