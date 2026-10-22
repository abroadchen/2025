//
// Created by Psy.C on 2026/10/22.
//
/**
读入 n（行数）、m（列数）、k（要查询的编号）
第 1 列：行从 1→n，编号 1..n，所以 k<n 时在第 1 列，行 = k+1，列 = 1。✅ 与 k<n → 行k+1列1 吻合。
从第 2 列开始（编号 n+1 起），列的方向取决于列号的奇偶
k1 = k - n：从第 2 列开始计数（去掉第 1 列 n 步）。
q = k1/(m-1)：判断属于哪个"组"，组步长为 m-1。
r = k1%(m-1)：组内第几步（0 起）。
行号统一为 n - q（随组数递增而行号递减）。
若 q 为奇数（(k1/(m-1))%2==1，第奇数组，方向相反）：
列 = m - r（从右往左）。
若 q 为偶数：
列 = r + 2（第 2 列起，r=0 → 列 2）。
这对应一种蛇形路径：从 (1,1) 沿第 1 列走到 (n,1)（编号1..n），然后每往右一"组"在列间蛇形摆动（组步长 m-1，说明横向每次走到对侧列边界再折返）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, k;
int main() {
    fast;
    cin >> n >> m >> k;
    if (k < n) cout << k+1 << ' ' << 1 << '\n';
    else {
        ll k1 = k - n;
        if ((k1/(m-1))%2 == 1)
            cout << n-k1/(m-1) << ' ' << m-k1%(m-1) << '\n';
        else
            cout << n-k1/(m-1) << ' ' << k1%(m-1)+2 << '\n';
    }
    return 0;
}