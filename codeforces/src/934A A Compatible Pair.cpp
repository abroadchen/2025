//
// Created by Psy.C on 2026/10/16.
//
/**
删除一个 a[i]（恰删除一项）。
对剩下的所有 a[j]（j≠i）与所有 b[x] 相乘，得到 n-1 * m 个乘积。
取这些乘积的最大值。
对每种删除方案得到的最大值，再取最小值作为答案
外层 i：枚举删除哪个 a[i]。
中层 j：遍历所有 a[j]，跳过被删除的 i（if (i != j)）。
内层 x：遍历所有 b[x]，计算乘积 a[j]*b[x] 并更新 mx（当前删除方案下的最大乘积）。
外层每轮结束后，mx 就是"删除 a[i] 后所有合法乘积的最大值"；用 ans = min(ans, mx) 在所有删除方案的最大值里取最小
三层循环：O(n * n * m)。因为 n,m ≤ 50（N = 55 边界），最多 50*50*50 = 125000 次，完全可接受
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr ll N = 55, inf = 0x7fffffffffffffff;
ll n, m, a[N], b[N], mx, ans(inf);
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,n) cin >> a[i];
    rep(i,1,m) cin >> b[i];
    rep(i,1,n) {
        mx = -inf;
        rep(j,1,n) if (i != j) {
            rep(x,1,m) mx = a[j]*b[x] > mx ? a[j]*b[x] : mx;
        }
        ans = mx < ans ? mx : ans;
    }
    cout << ans << '\n';
    return 0;
}