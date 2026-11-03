//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
a：长度为 n 的数组，a[i] 是第 i 个位置的数值（1 到 n 的一个排列）。
pos：pos[x] 表示数值 x 出现在数组的哪个下标
f 是长度为 n 的 bool 数组，f[i] 记第 i 个位置是否"已被判定为 A"
res 是结果字符串，长度 n，初始全部为 'B'，稍后会有一部分改成 'A'。
读入 a，同时建立 pos：数值 a[i] 出现在下标 i（a[i]-1 是 0 基下标）
从 i = n 递减到 i = 1。pos[i-1] 是数值 i 所在的下标位置
把下标 j 通过不断减 i 调整到 j < i 的范围（即让起始下标落在 [0, i) 内）。本质上是在数轴上把起始点"折返"回模 i 的等价位置（j %= i 的类似效果，这里是取 j mod i，但其写法是 while 减法）
从该起始下标开始，以步长 i 步进（访问下标 j, j+i, j+2i, ... 直到 ≥ n），枚举所有下标满足 下标 ≡ pos[i-1] (mod i) 的位置：

if (a[j] <= i) continue;：跳过那些数值不超过 i 的位置。
if (!f[j])：如果某个下标 j 还没被标成 A，且 a[j] > i，则说明存在一个比 i 更大、且尚未被标记的"可选位置"，于是把 i 所在位置标记为 A：f[pos[i-1]] = true，并 break。
也就是说：若能在 i 的同余类（mod i）中找到某个位置，其上的数值比 i 大且还没被标 A，那么数值 i 就能移动到那个位置，从而 i 这一格被判定为 'A'
最后，若该位置的 f 被置为 true，把结果串中对应字符改成 'A'。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; i++)
#define int long long
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), pos(n);
    vector<bool> f(n);
    string res(n,'B');
    rep(i,n) cin >> a[i], pos[a[i]-1] = i;
    for (int i = n; i; i--) {
        int j = pos[i-1];
        while (j >= i) j -= i;
        for (; j < n; j += i) {
            if (a[j] <= i) continue;
            if (!f[j]) { f[pos[i-1]] = true; break; }
        }
        if (f[pos[i-1]]) res[pos[i-1]] = 'A';
    }
    cout << res;
}

signed main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}