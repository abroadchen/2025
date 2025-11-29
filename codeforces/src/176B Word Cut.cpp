//
// Created by Psy.C on 2025/11/29.
//
/*
*s[N]: 主字符串
t[N]: 目标字符串
*k: 操作次数
n: 字符串长度
cnt: 满足条件的位置数量
*f[i][0]: i次操作后满足条件的方案数
f[i][1]: i次操作后不满足条件的方案数
 *
*检查字符串s的[l,r]区间是否与字符串t匹配：
从位置l到r逐一比较
如果有任何字符不匹配返回false
全部匹配返回true
 *
 *构造循环字符串：将s的前n个字符复制到s[n+1]到s[2n]位置
 *这样可以方便地处理循环匹配（避免取模运算）
 *
*统计有多少个位置开始的长度为n的子串与t匹配：
遍历1到n的每个起始位置
检查从该位置开始的n个字符是否与t匹配
计数器cnt记录匹配的数量
 *
*初始化DP状态：
ok(1, n) 检查初始状态是否匹配
如果匹配：!ok(1, n) = 0，设置f[0][0] = 1
如果不匹配：!ok(1, n) = 1，设置f[0][1] = 1
 *
*状态0（满足条件）的转移：
cnt * f[i-1][1]: 从不满足状态转移来，有cnt种方式变为满足
(cnt - 1) * f[i-1][0]: 从满足状态转移来，有(cnt-1)种方式保持满足
状态1（不满足条件）的转移：
(n - cnt) * f[i-1][0]: 从满足状态转移来，有(n-cnt)种方式变为不满足
(n - cnt - 1) * f[i-1][1]: 从不满足状态转移来，有(n-cnt-1)种方式保持不满足
 *输出k次操作后满足条件的方案数
 *
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+5, mod = 1e9+7;
char s[N], t[N];
int k, n, cnt;
ll f[N][2];

bool ok(const int l, const int r) {
    int j = 0;
    for (int i = l; i <= r; ++i)
        if (s[i] != t[++j]) return false;
    return true;
}

int main() {
    fast;
    scanf("%s%s%d", s + 1, t + 1, &k);
    n = static_cast<int>(strlen(s + 1));
    rep(i,n) s[i + n] = s[i];
    rep(i,n) if (ok(i, i + n - 1)) cnt++;
    f[0][!ok(1, n)] = 1;
    rep(i,k) {
        f[i][0] = (cnt * f[i-1][1] % mod +
            (cnt - 1) * f[i-1][0] % mod) % mod;
        f[i][1] = ((n - cnt) * f[i-1][0] % mod +
            (n - cnt - 1) * f[i-1][1] % mod) % mod;
    }
    cout << f[k][0] << '\n';
    return 0;
}