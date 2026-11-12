//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
a：长度 n 的 0/1 串；b：长度 m 的 0/1 串
pre[i] = b[1..i] 里 1 的个数
bs：当前位对应的权重 2^k（从 2^0 递增）。
若 a[i]==1，则累加 bs × pre[max(0, m-(n-i))]。
m - (n-i)：从 a 的第 i 位（它到 a 尾部距离）反推到 b 串可参与取位的有效长度。
pre[有效长度] = b 串前若干位中 1 的个数——即这一位能贡献多少个"1"

从 a 的第 i 位（由右往左），它左侧还有 i-1 位；而 b 串参与匹配的方向是 b 的高位往低位。
n - i 表示 a 中第 i 位右侧的元素个数（到数组尾）。
那么 b 中能与之对齐参与的有效前缀长度 = m - (n - i)，取 max(0, …) 兜底防止负数。
pre[该长度] 恰好是这个有效前缀中 1 的个数，也就是该位能被"填充为 1"的次数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5, mod = 998244353;

int n, m, a[N], b[N], pre[N], ans;
char c;
signed main() {
    fast;
    cin >> n >> m;
    rep(i,n) { cin >> c; a[i] = c - '0'; }
    rep(i,m) {
        cin >> c; b[i] = c - '0';
        pre[i] = pre[i-1] + b[i];
    }
    int bs = 1;
    for (int i = n; i; i--) {//从最低位（右边）往左扫
        if (a[i] == 1) ans = (ans+bs*pre[max(0ll,m-(n-i))]%mod)%mod;
        bs = bs*2%mod;
    }
    cout << ans;
    return 0;
}