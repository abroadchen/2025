//
// Created by Psy.C on 2026/9/23.
//
/**
标准 exgcd，求出 a*x + mod*y = gcd(a, mod) 的一组解。
在 gcd(a, mod)=1 的前提下，get(a, mod) 返回 a 在模 mod 下的逆元 x
S：所有数之和对 T 取模。
arr[i] 先存原始数，再原地改造成前缀和（模 T）‍，且 arr[1] 强制置 0。
所以 arr[i] 现在是「前 i 个数的前缀和 mod T」
用哈希表 hs 记录某个前缀和值是否首次出现，标记 vis[i]=1。
后续 vis[i]=0 的（重复前缀和）答案直接输出 0（在下一段）
d = gcd(S, T)，然后 T、S 同时除以 d 完成约分（标准化到互质情形，保证逆元存在）。
inv = S^{-1} mod T。
注意：这里 T、S 被就地修改了（约分后）。后续 %T 用的是约分后的模数。
每个前缀和 arr[i] 按 arr[i] % d 分类到桶 id[t]。
计算 nos[i] = inv * (arr[i] - t) / d % T——这是经过“约分 + 逆元变换”后的标准化坐标值。
把 nos[i] 插入对应桶的 set 中（set 自动排序、去重，后面用来查后继）。
（因为 arr[i] % d == t，所以 (arr[i]-t) 能被 d 整除，/d 是整数运算，inv*(arr[i]-t)/d 在模 T 下计算。）
对每个首次出现的 i：
找到它所在桶 idx。
在 set 中定位 nos[i] 的位置，++p 得到严格大于它的下一个元素（后继）。
若后继存在：ans = 后继 - nos[i]（正向环形距离）。
若已是该桶最大值（p == end）：则绕回桶内最小值，ans = 最小值 + T - nos[i]，即「从当前点出发绕环一圈回到最小值」的距离。
结果 ans[i] 是「从当前点出发，沿环正向到达桶内下一个点所需的最小步数/最小非负差值」
逐个输出每个位置的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

int ex(int a, int b, int& x, int& y) {
    if (b == 0) { x = 1, y = 0; return a; }
    int ret = ex(b, a%b, y, x);
    y -= a/b*x;
    return ret;
}
int get(int a, int mod) {
    int x, y;
    ex(a, mod, x, y);
    return x;
}

int vis[N], arr[N], nos[N], ans[N];
unordered_map<int, bool> hs;
unordered_map<int, int> id;
set<int> s[N];
signed main() {
    fast;
    int T, n; cin >> T >> n;
    memset(vis, 0, sizeof vis);
    int S = 0;
    for (int i = 1; i <= n; ++i) cin >> arr[i], S = (S+arr[i])%T;
    arr[1] = 0;
    for (int i = 2; i <= n; ++i) arr[i] = (arr[i]+arr[i-1])%T;
    for (int i = 1; i <= n; ++i)
        if (!hs.contains(arr[i])) hs[arr[i]] = 1, vis[i] = 1;
    int d = __gcd(S, T); T/=d; S/=d;
    int inv = get(S, T);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int t = arr[i]%d;
        if (!id[t]) id[t] = ++cnt;
        nos[i] = 1ll*inv*(arr[i]-t)/d%T;
        s[id[t]].insert(nos[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) { ans[i] = 0; continue; }
        int idx = id[arr[i]%d];
        auto p = s[idx].find(nos[i]); ++p;
        if (p == s[idx].end()) ans[i] = (*s[idx].begin()) + T - nos[i];
        else ans[i] = (*p) - nos[i];
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}