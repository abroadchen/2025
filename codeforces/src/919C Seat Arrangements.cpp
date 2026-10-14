//
// Created by Psy.C on 2026/10/14.
//
/**

n, m, k：网格行数、列数、目标连续长度 k。
s：结果累计（符合条件的连续段数量）。
cnt：当前连续 '.' 的长度计数器。
用两重 rep 从 1 到 n、1 到 m 读入每个格子字符（注意下标从 1 开始
对每一行，从左到右维护 cnt（以当前位置结尾的连续 . 的长度）。
一旦 cnt >= k，说明以当前格为右端点，能形成一段长度至少为 k 的连续 .，方案数 s++。
这种写法等价于：一段长度为 L（L≥k）的连续 .，会贡献 L-k+1 个计数。
遇到 . 之外（即 #）则 cnt=0 重新计数
与横向完全对称，只是外层固定列 j、内层遍历行 i，统计每列纵向连续 . 的长度
当 k==1 时，单个 . 格子在横向和纵向各被统计一次，造成重复，所以 s 除以 2；否则不除。
输出最终方案数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 2e3+1;
char a[N][N];
int n, m, k, s, cnt;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,1,n) rep(j,1,m) cin >> a[i][j];
    s = 0;
    rep(i,1,n) {
        cnt = 0;
        rep(j,1,m) {
            if (a[i][j] == '.') cnt++;
            else cnt = 0;
            if (cnt >= k) s++;
        }
    }
    rep(j,1,m) {
        cnt = 0;
        rep(i,1,n) {
            if (a[i][j] == '.') cnt++;
            else cnt = 0;
            if (cnt >= k) s++;
        }
    }
    cout << s/(k==1?2:1) << '\n';
    return 0;
}