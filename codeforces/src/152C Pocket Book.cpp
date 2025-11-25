//
// Created by Psy.C on 2025/11/23.
//
/*
*st[N]：N个字符集合，用于存储每列的不同字符
s[N][N]：二维字符数组，用于存储输入的字符串
 *n（字符串数量）和m（字符串长度）
 *
*外层循环遍历每个字符位置i（0到m-1列）
内层循环遍历每个字符串j（0到n-1行）
将第j个字符串的第i个字符插入到第i个集合st[i]中
由于set自动去重，每个集合st[i]存储第i列的所有不同字符
 *
*对于每一列i，取出该列不同字符的数量sz(st[i])
将ans乘以该数量并对mod取模
这实际上是计算每列可选字符数的乘积
 *
 *时间复杂度是O(n×m)，空间复杂度是O(m)
 *
 */
#include <iostream>
#include <set>
#define rep(i,n) for(int i=0;i<n;++i)
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;
constexpr int N = 105, mod = 1000000007;
set<char> st[N];
char s[N][N];

int main() {
    int n, m; cin >> n >> m;
    rep(i,n) cin >> s[i];
    rep(i,m) rep(j,n) st[i].insert(s[j][i]);
    ll ans = 1;
    rep(i,m) ans = ans * sz(st[i]) % mod;
    cout << ans % mod << '\n';
    return 0;
}