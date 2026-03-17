//
// Created by Psy.C on 2026/3/17.
//
/**
n：数组长度
a[N]：输入数组（扩展为两倍长度）
g[N]：每组中的最大值
f[N]：连续符合条件的位置计数
cnt[N]：欧拉函数前缀和
b[N]：标记数组，表示某位置是否为组内最大值

将数组扩展为两倍长度（循环扩展）
枚举所有可能的周期d（必须是n的因数）
只有当d整除n时才继续处理
清空标记数组
对每个余数k（0到d-1），在所有i≡k(mod d)的位置中找最大值
n<<1等于2*n，即遍历扩展后的数组
标记所有等于组内最大值的位置
动态规划计算以每个位置结尾的连续满足条件的最大长度
如果当前位置被标记为1，则延续之前的连续长度
否则重置为0
限制长度不超过n-1
计算欧拉函数φ的前缀和
gcd(i, n/d) == 1表示i与n/d互质
这是在计算有多少个与周期相关的旋转是有效的

从第二个周期开始统计
f[i]/d：当前连续段包含多少个完整的周期
cnt[f[i]/d]：对于这个长度，有多少个旋转是有效的

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+5;

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

int n, a[N], g[N], f[N], cnt[N];
bool b[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i+n] = a[i];
    }
    int ans = 0;
    for (int d = 1; d < n; ++d) {
        if (n % d == 0) {
            memset(b, 0, sizeof b);
            for (int k = 0; k < d; ++k) {
                g[k] = 0;
                for (int i = k; i < n<<1; i += d) g[k] = max(g[k], a[i]);
                for (int i = k; i < n<<1; i += d)
                    if (g[k] == a[i]) b[i] = 1;
            }
            f[0] = b[0];
            for (int i = 1; i < n<<1; ++i) {
                if (b[i]) f[i] = f[i-1] + 1;
                else f[i] = 0;
                f[i] = min(f[i], n-1);
            }
            cnt[0] = 0;
            for (int i = 1; i < n/d; ++i)
                cnt[i] = cnt[i-1] + (gcd(i, n/d) == 1);
            for (int i = n; i < n<<1; ++i)
                ans += cnt[f[i]/d];
        }
    }
    cout << ans << '\n';
    return 0;
}