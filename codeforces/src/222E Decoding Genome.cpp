//
// Created by Psy.C on 2025/12/8.
//
/*
*n：字符串长度
ans[N][N]：转移矩阵 能否从字符i转移到字符j
m：字符集大小
k：禁止的字符对数量
 *
*如果是小写字母a-z，返回0-25
如果是大写字母A-Z，返回26-51
 *
*c[N][N]：临时结果矩阵
memset(c, 0, sizeof(c))：将结果矩阵初始化为0
 *将计算结果从临时矩阵c复制回矩阵a
 *
 *时间复杂度：O(m³ × log n)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(int i=0;i<n;++i)
#define N 100
#define mod 1000000007
using namespace std;

ll n, ans[N][N];
int m, k;

int get(const char x) {
    if (x >= 'a' && x <= 'z') return x - 'a';
    return x - 'A' + 26;
}

ll c[N][N];
void mul(ll a[][N], ll b[][N]) {
    memset(c, 0, sizeof(c));
    rep(i,m) rep(j,m) rep(x,m) {
        c[i][j] = (c[i][j] + a[i][x] * b[x][j]) % mod;
    }
    memcpy(a, c, sizeof(c));
}

ll t[N][N];
void pw(ll p) {
    memset(t, 0, sizeof(t));
    rep(i,m) t[i][i] = 1;//单位矩阵（对角线为1）
    while (p > 0) {
        if (p & 1) mul(t, ans);
        mul(ans, ans);
        p >>= 1;
    }
    memcpy(ans, t, sizeof(t));
}

char s[3];
int main() {
    fast;
    cin>>n>>m>>k;
    rep(i,m) rep(j,m) ans[i][j] = 1;//表示默认都可以转移
    rep(i,k) {
        cin >> s;
        ans[get(s[0])][get(s[1])] = 0;//禁止该转移
    }
    if (n == 1) { cout << m << '\n'; return 0; }
    pw(n - 1); ll cnt = 0;
    rep(i,m) rep(j,m) cnt = (cnt + ans[i][j]) % mod;
    cout << cnt << '\n';
    return 0;
}