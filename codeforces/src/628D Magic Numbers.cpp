//
// Created by Psy.C on 2026/3/28.
//
/**
len: 当前处理数字的长度
b[N]: 存储数字各位的数组（从1开始）
d: 特殊数字
m: 除数
dp[N][N]: 记忆化数组，dp[pos][res]表示在位置pos，余数为res时的方案数

pos: 当前处理的位置
res: 当前数字对m的余数
lim: 是否受到上界限制的标志
到达末尾时，只有余数为0才满足条件
ed: 当前位置数字的上界
遍历所有可能的数字
根据位置奇偶性检查约束条件
传递新的余数和限制状态

将字符串转换为数组b（从索引1开始）
从位置1开始，余数0，受限制状态开始DFS
get(a2): 小于等于a2的满足条件的数字个数
get(a): 小于等于a的满足条件的数字个数
ok(a): 如果a本身满足条件则加1
最终得到区间[a, a2]内满足条件的数字个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2005, mod = 1e9+7;

int len, b[N], d, m;
ll dp[N][N];
ll dfs(int pos, int res, int lim) {
    if (pos == len+1) return res == 0;
    if (!lim && dp[pos][res] != -1)
        return dp[pos][res];
    ///如果lim == 1（受限制）：ed = b[pos]（当前位的最大可能值）
    ///如果lim == 0（不受限）：ed = 9（最大数字）
    int ed = lim ? b[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= ed; ++i) {
        if (pos % 2 == 1 && i == d) continue;//奇数位不能是d
        if (pos % 2 == 0 && i != d) continue;//偶数位必须是d
        ans = (ans + dfs(pos+1, (res*10+i)%m, lim&&i==ed))%mod;
    }
    if (!lim) dp[pos][res] = ans;//只有在不受限的情况下才能记忆化
    return ans;
}
ll get(string s) {
    for (int i = 0; i < len; ++i)
        b[i+1] = s[i] - '0';
    return dfs(1, 0, 1);
}
///验证字符串s是否满足所有条件
ll ok(string s) {
    int res = 0;
    for (int i = 1; i <= len; ++i) {
        if (i%2 == 0 && s[i-1]-'0' != d) return 0;//检查偶数位约束
        if (i%2 == 1 && s[i-1]-'0' == d) return 0;
        res = res*10+(s[i-1]-'0'); res %= m;//计算余数
    }
    if (res) return 0;//检查是否整除m
    return 1;
}
string a, a2;
int main() {
    fast;
    memset(dp, -1, sizeof dp);
    cin >> m >> d >> a >> a2; len = a.size();
    cout << (get(a2) - get(a) + ok(a) + mod) % mod << '\n';
    return 0;
}