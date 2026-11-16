//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
读入 n。
读入 a[0..6] 七个值，并累加得到 x = Σa[i]（一周 7 天里"有效天"的某种计数总和）
w = (n-1)/x：先看看这 n 次之前能完整走多少个"周块"（每个周块贡献 x 次）。
初始 ans = N（先假设最坏在当周第 N 天完成）。
思路：因为每周有效次数是 x，用除法先跳过完整的周，剩下不足一周的部分在那一周内逐天找答案
对每个起始天 i（0 到 6，即一周每个可能的起点都试一遍）：

y = n - w*x：这是跳过整周期后，还差几次就够 n。
从 j = 1 到 7，依次看第 (i+j)%7 天（即从 i 往后数 j 天的那一天）。
若那天的 a[...] 非零（该天是"有效天"），就让 y 减 1。
当 y 减到 0 时，说明这一天就是第 n 次，记录 ans = min(ans, j)（j 表示"从这个起点在第几天"）。
因为"从哪个起点开始算整周"会影响余数落在第几天，所以枚举所有 7 个可能的起点，取最小答案
w*N：完整走过的周数 × 7（天）。
+ ans：加上"余数落在第几天"。
输出完成后处理下一组。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;

constexpr int N = 7;

int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        vector<int> a(N);
        int n; cin >> n;
        int x = 0;
        rep(i,N) { cin >> a[i]; x += a[i]; }
        int w = (n-1)/x, ans = N;
        rep(i,N) {
            int y = n - w*x;
            for (int j = 1; j <= N; ++j) if (a[(i+j)%N]) {
                --y;
                if (!y) { ans = min(ans, j); break; }
            }
        }
        cout << w*N+ans << '\n';
    }
    return 0;
}