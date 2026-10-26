//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
逐步：

对每个 i（从 2 到 √n）：

t = to_string(i)：底数 i 的普通十进制字符串。
若 mp 还没有 i 或已有的表示比 t 长，则存 mp[i] = t（即"i 自身"是最短表示）。
内层循环：幂。

j = i*i, k=2 起始（i² 是第一个幂，指数 k=2）。
每次 j *= i, ++k 即 j 变为 i^(k+1)。
当 j 还 ≤ n 时，构造 o = t + "^" + to_string(k) 即 "i^k"。
若 j 没记录过，或已有表示比 o 长，则 mp[j] = o。
目的：把形如 8(=2³)、16(=2⁴)、9(=3²)、25(=5²) 等"完全幂次数"表示为最短的 底^指数 字符串。注意 j 可能超过 ll 上限溢出，但题目约束 n 正常范围（通常 n≤1e9 之类）
最朴素方案：直接用十进制 n。后续尝试更短表示
对 map 中每个 x（x 是一个幂次/普通数字，其最短表示存于 mp）：

x = it->first：当前基数。
a) 商部分 n/x（若不为 1）
若 n/x ≠ 1（即还有商需要表示），先构造商的字符串。
若 n/x 在 mp 中（有更短的幂次表示）且比十进制短 → 用 mp[n/x] 作为商表示。
否则用十进制 y。
后面都加 "*"（乘号）
b) 乘上 x 本身
追加 x 的最短表示 it->second（比如 "2^4"）。
此时表达式形如 (n/x)*x
c) 余数部分 n%x（若不整除）‍
若 n 不能被 x 整除（有余数），则补上 +余数。
余数也用 mp 中最短表示或十进制。
形如 (n/x)*x + (n%x)。
d) 更新最优
若当前组合 o 比现有 ans 更短，更新 ans
输出最短表达式。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
map<ll,string> mp;
string ans;
int main() {
    fast;
    cin >> n; m = sqrt(n);
    for (ll i = 2; i <= m; ++i) {
        string t = to_string(i);
        if (!mp.contains(i) || mp[i].length() > t.length()) mp[i] = t;
        for (ll j = i*i, k = 2; j <= n; j *= i, ++k) {
            string o = t + "^" + to_string(k);
            if (!mp.contains(j) || mp[j].length() > o.length()) mp[j] = o;
        }
    }
    ans = to_string(n);
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        string o;
        ll x = it->first;
        if (n/x != 1) {
            string y = to_string(n/x);
            if (mp.contains(n/x) && mp[n/x].length() < y.length()) o += mp[n/x] + "*";
            else o += y + "*";
        }
        o += it->second;
        if (n%x != 0) {
            string y = to_string(n%x);
            if (mp.contains(n%x) && mp[n%x].length() < y.length()) o += "+" + mp[n%x];
            else o += "+" + y;
        }
        if (o.length() < ans.length()) ans = o;
    }
    cout << ans;
    return 0;
}