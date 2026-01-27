//
// Created by Psy.C on 2026/1/27.
//
/**
 * no[i]=true表示i不是质数
 *dp[i]表示与i互质的输入数字个数
 *vis[i]表示数字i在输入中出现的次数
 *
*时间复杂度
get()函数：O(N log N)，类似埃拉托斯特尼筛的时间复杂度
前缀和：O(N)
查询：O(M)，M为查询次数
总体：O(N log N + M)
空间复杂度
O(N)，主要是三个大小为N的数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000005
using namespace std;

bool no[N];
int dp[N], vis[N];
void get() {
    for (int i = 2; i < N; ++i) if (!no[i]) {
        dp[i] += vis[i];//将i本身在输入中的出现次数计入
        for (int j = i + i; j < N; j += i) no[j] = true, dp[i] += vis[j];
    }
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        vis[x]++;
    }
    get();
    for (int i = 2; i < N; ++i) dp[i] += dp[i - 1];
    int m; cin >> m;
    while (m--) {
        int l, r; cin >> l >> r;
        if (l > N) l = N - 1;//如果l或r大于N，限制为N-1
        if (r > N) r = N - 1;
        cout << dp[r] - dp[l-1] << '\n';//区间[l,r]内的符合条件的数字个数
    }
    return 0;
}