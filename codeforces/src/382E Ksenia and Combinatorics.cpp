//
// Created by Psy.C on 2026/1/26.
//
/*
* 有一个根节点，所以总的可分配位置是 siz-1
当左右子树大小相等时，还需要考虑额外的对称性约束，导致进一步减少1

状态0 (state=0)：根节点不受约束或未被占用
只有当左右子树都处于状态1时，当前结构才能处于状态0
这可能表示：根节点可以被"使用"或"参与配对"
所以转移是：[状态1] × [状态1] → [状态0]
状态1 (state=1)：根节点受到约束或已被占用
可以通过多种方式到达状态1：
左子树状态1 × 右子树状态0 → 状态1
左子树状态0 × 右子树状态1 → 状态1
左子树状态0 × 右子树状态0 → 状态1

对于 dp[siz][mac][0]：
需要恰好使用 mac 个特殊元素
左右子树的特殊元素总数 = lm + rm = mac
对于 dp[siz][mac][1]：
可能有一个特殊元素被"占用"或"消耗"了
左右子树分配的特殊元素总数 = lm + rm = mac-1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
#define N 60
using namespace std;

void add(ll& a, const ll b) { a = (a + b) % mod; }

int main() {
    fast;
    ll n, k; cin >> n >> k;
    if (k<<1 > n) { cout << "0"; return 0; }
    ll c[N][N]={}, dp[N][N][2]={};
    for (ll i = 0; i <= n; ++i) c[i][0] = 1;//从i个元素中选择j个的组合数
    for (ll i = 1; i <= n; ++i) for (ll j = 1; j <= i; ++j) {
        c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
    }
    dp[1][0][0] = dp[0][0][1] = 1;
    for (ll siz = 2; siz <= n; ++siz) for (ll mac = 1; mac <= k; ++mac) {
        for (ll ls = 0, rs = siz - 1; ls <= rs; ++ls, --rs) {
            for (ll lm = 0, rm = mac; lm <= mac; ++lm, --rm) {
                if (lm<<1 > ls || rm<<1 > rs) continue;
                const ll t = (ls == rs ? c[siz-2][ls-1] : c[siz-1][ls]) * (siz == n ? 1 : siz) % mod;
                add(dp[siz][mac][0], dp[ls][lm][1] * dp[rs][rm][1] % mod * t % mod);
            }
        }
        for (ll ls = 0, rs = siz - 1; ls <= rs; ++ls, --rs) {
            for (ll lm = 0, rm = mac-1; lm < mac; ++lm, --rm) {
                if (lm<<1 > ls || rm<<1 > rs) continue;
                const ll t = (ls==rs ? c[siz-2][ls-1] : c[siz-1][ls]) * (siz==n ? 1 : siz) % mod;
                add(dp[siz][mac][1], dp[ls][lm][1] * dp[rs][rm][0] % mod * t % mod);
                add(dp[siz][mac][1], dp[ls][lm][0] * dp[rs][rm][1] % mod * t % mod);
                add(dp[siz][mac][1], dp[ls][lm][0] * dp[rs][rm][0] % mod * t % mod);
            }
        }
    }
    cout << (dp[n][k][0] + dp[n][k][1]) % mod;
    return 0;
}