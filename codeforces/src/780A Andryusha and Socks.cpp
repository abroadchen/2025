//
// Created by Psy.C on 2026/9/12.
//
/**
多组测试数据（while 读 n）。
mx 记录最大同时在车人数，初始 0。
a[数组] 清零（a[k] 表示编号 k 当前在车状态）
每个编号出现两次：第一次 = 上车，第二次 = 下车。
if (a[k])：若编号 k 已在车上（a[k] 为真），说明这是第二次出现 → 下车：a[k]--（标记下车），sum--（车上人数减一）。
else：编号 k 不在车上（第一次出现）→ 上车：sum++（人数加一），mx = max(sum, mx)（更新历史最大值），a[k]++（标记在车）
输出这组数据的最大同时在车人数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10;
int n, a[N];
int main() {
    fast;
    while (cin >> n) {
        int mx(0);
        memset(a, 0, sizeof(a));
        for (int i = 1, k, sum = 0; i <= 2*n; ++i) {
            cin >> k;
            if (a[k]) a[k]--, sum--;
            else sum++, mx = max(sum, mx), a[k]++;
        }
        cout << mx << '\n';
    }
    return 0;
}