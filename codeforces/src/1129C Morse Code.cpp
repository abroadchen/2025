//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a[]：输入序列，元素为 0/1（二进制串问题）。
tr[N*N][2]：Trie 节点，每个节点两条边（0/1）。cnt=2 是下一个可用节点编号（1 是根？下面 v=1 说明根是 1）。
ans：累计答案；f[]：DP 计数数组
外层每个 i 输出一次 ans（题目要求逐步输出累加答案）。
f[i] = 1：单独以 i 结尾的子序列＝1。
v = 1：Trie 从根开始
g = min(4, i-j)：目前能向后延伸的窗口长度，最多 4。
当 g==4 时，把连续的 4 个元素拼成 4 位二进制 q = a[j]·8 + a[j+1]·4 + a[j+2]·2 + a[j+3]（a[j] 是最高位）。
若 q 等于 3(0011)、5(0101)、14(1110)、15(1111)，则 g--（窗口缩到 3）。
这 4 个模式是被禁止的 4 位子串，出现时不允许跨越到第 4 位。
f[j] = 0，然后 f[j] = Σ_{k=1..g} f[j+k]：以 j 结尾的子序列数 = 后续 g 个位置分别向前接的数量之和（相当于把前面以 j+k 结尾的子序列前加 a[j]，构造以 j 结尾的新子序列）。
取模
若当前 Trie 节点 v 沿 a[j] 的边还没建立，说明"以 a[j] 为下一字符"的这条子序列路径是第一次出现 → 把 f[j]（以 j 结尾的这类新子序列数量）‍加入 ans，并新建节点。
v = tr[v][a[j]]：沿该子串下行。
若边已存在，说明该前缀已在之前出现过，不再重复计数（去重核心）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int mod = 1e9+7, N = 5e3;
int n, a[N], v, tr[N*N][2], cnt = 2;
ll ans, f[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    rep(i,n) {
        f[i] = 1; v = 1;
        for (int j = i-1; j >= 0; j--) {
            int g = min(4,i-j);
            if (g == 4) {
                int q = a[j]*8+a[j+1]*4+a[j+2]*2+a[j+3];
                if (q == 3 || q == 5 || q == 14 || q == 15) g--;
            }
            f[j] = 0;
            rep(k,g) f[j] += f[j+k]; f[j] %= mod;
            if (!tr[v][a[j]]) {
                ans = (ans + f[j]) % mod;
                tr[v][a[j]] = cnt++;
            }
            v = tr[v][a[j]];
        }
        cout << ans << '\n';
    }
    return 0;
}