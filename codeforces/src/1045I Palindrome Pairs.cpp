//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
pw[30]：预存 2 的 0..25 次方，用于把某个字母映射到独立的一位。
mp：键 = 字符串的特征哈希值，值 = 出现次数
pw[k] = 2^k，覆盖 26 个小写字母，每个字母占独立一位。
对每个字符串，逐字符异或 pw[k]（即 2^k）。

由于 x ^ x = 0，异或会抵消成对出现的相同字母。
所以 res 的二进制第 k 位 = 1 ⟺ 字母 k 在字符串中出现次数为奇数。
即：res 压缩记录了每个字母出现次数的奇偶性，与顺序无关、与偶数次字母无关。这是典型的奇偶性哈希 / 可逆哈希指纹。
注意这里用的是 unordered_map<int,int>，说明两个字符串哈希值相同 ⟺ 各字母出现次数的奇偶性完全相同（视为"等价"）。题目显然进一步限定：合法对是"恰好差一个字符"
① 哈希完全相同的串

ans += (num-1)*num/2：有 num 个串哈希值相同，任取两个成一对，即组合数 C(num,2)。

这对应"两串各字母奇偶性完全相同"的配对。
② 哈希恰好差一个字母（一次翻转）的串

对每个当前哈希值 res，枚举 26 个字母位：
若该位已经是 1（res&pw[j] != 0），跳过——因为下面只做"从 0 → 1"的单向补齐，避免重复统计（A 补到 B 和 B 补到 A 只算一次）。
否则计算 ret = res + pw[j]：即把第 j 位置为 1，得到一个"只差这一位是 1"的新哈希。
若该新哈希在 mp 中存在，则 ans += mp[ret] * num（当前这一数值的所有串 × 目标数值的所有串）。
这对应"两个字符串的奇偶性仅在某个字母上相反，其余完全相同"的配对——相当于在奇偶性层面恰好相差一个字符。

用 res = XOR of 2^k 得到每个字符串的奇偶性指纹（26 位掩码）。
mp 哈希表统计每种指纹的出现次数。
遍历所有指纹：
内部自配：C(num,2)；
跨差别一倍的指纹：枚举 26 位把当前指纹补一位置 1，若目标指纹存在则相乘累加。
复杂度近似 O(n × |s| + 种类 × 26)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e6+2;

int n, pw[30];
char s[N];
unordered_map<int,int> mp;
signed main() {
    fast;
    cin >> n; pw[0] = 1;
    for (int i = 1; i < 26; i++) pw[i] = pw[i-1]<<1;
    int res, len, k, num, ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> s; len = strlen(s); res = 0;
        for (int j = 0; j < len; j++) { k = s[j] - 'a'; res ^= pw[k]; }
        mp[res]++;
    }
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        res = it->first, num = it->second; ans += (num-1)*num/2;
        for (int j = 0; j < 26; j++) {
            if ((res&pw[j]) != 0) continue;
            int ret = res + pw[j];
            if (mp.contains(ret)) ans += mp[ret]*num;
        }
    }
    cout << ans;
    return 0;
}