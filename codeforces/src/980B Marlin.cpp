//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
第一行打印 n 个 .。
若 k 为奇数走奇分支，为偶数走偶分支。
最后一行再打印 n 个 .。
所以网格是 4 行 × n 列，# 组成一条从左上/左下到右上/右下的通路
k 为奇数，且 k ≤ n-2
中间这一行：两侧各 (n-k)/2 个点，中间连续 k 个 #——一整行横向通路。
再下面一行：n 个点（空行）。
可确证：奇数且 k≤n-2 时，第三行打印 (n-k)/2 个点 + k 个 # + (n-k)/2 个点（共 n 字符），第四行 n 个点
k 为奇数，且 k > n-2（即 k=n-1 或更大
第一中间行：. + (n-2) 个 # + .——几乎整行都是通路，只留两端点。
第二中间行：. + 若干 # + 中间点 + 若干 # + .，通过两侧的 # 把多余的通路格子（k-n+2 个）分配到两端。
可确证：奇数且 k>n-2 时，用两端补格子的方式拼出 k 个 #
k 为偶数
连续两行：每行 . + k/2 个 # + n-k/2-1 个 .。
两行各放 k/2 个 #，合计恰好 k 个 #，构成"两行 L 形"通路。
可确证：偶数时打印两行各 k/2 个 #
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define int long long
using namespace std;

int n, k, i, j;
signed main() {
    fast;
    cin >> n >> k;
    cout << "Yes\n";
    rep(i,n) cout << '.'; cout << '\n';
    if (k&1) {
        if (k <= n-2) {
            rep(i,(n-k)/2) cout << '.';
            rep(i,k) cout << '#';
            rep(i,(n-k)/2) cout << '.'; cout << '\n';
            rep(i,n) cout << '.'; cout << '\n';
        } else {
            cout << '.';
            rep(i,n-2) cout << '#';
            cout << '.' << '\n' << '.';
            rep(i,(k-n+2)/2) cout << '#';
            rep(i,n-(k-n+2)-2) cout << '.';
            rep(i,(k-n+2)/2) cout << '#'; cout << '.' << '\n';
        }
    } else {
        rep(i,2) {
            cout << '.';
            rep(j,k/2) cout << '#';
            rep(j,n-k/2-1) cout << '.';
            cout << '\n';
        }
    }
    rep(i,n) cout << '.';
    return 0;
}