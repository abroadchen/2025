//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
f[i][j][k] 表示 i 位数字，第 i 位（最高位或某特征位）为 j，并且"特征计数"为 k 时的合法数个数。这里的 k 通常代表某种数字（如某个特定数字）‍出现的次数分类（0、1、≥2 等，3 就是上限）
把 x 的每一位拆出来存进 d[]（低位在前）
把所有位数少于 len 的合法数全部累加（注意首位从1开始，不能是0）
统计恰好 len 位、首位小于 d[len] 的数
从高位向低位枚举，当已固定的前缀中非零数字个数达到上限时，剩余位就不能再增加计数，故 k 的上限变成 3-cnt。这就是数位DP的"贴上限"处理——保证统计不重不漏
query(r+1) - query(l) 得到 [l, r] 区间（含端点）内满足条件的数个数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 25;

int d[N];
ll f[N][N][N];
ll query(ll x) {
    int len = 0; ll ret = 0;
    while (x) d[++len] = x % 10, x /= 10;
    for (int i = 1; i < len; i++) for (int j = 1; j <= 9; j++) rep(k,3)
        ret += f[i][j][k];
    for (int i = 1; i < d[len]; i++) rep(j,3) ret += f[len][i][j];
    for (int i = len-1, cnt = 0; i >= 1; i--) {
        if (d[i]) cnt++;
        rep(j,d[i]-1) rep(k,3-cnt) ret += f[i][j][k];
    }
    return ret;
}

int t;
ll l, r;
int main() {
    fast;
    cin >> t; f[1][0][0] = 1;//位数1、数字0、计数0 → 1种（即"0"）
    for (int i = 1; i <= 9; i++) f[1][i][1] = 1;//1~9 各自 1 种
    //枚举位数 三重循环递推
    for (int i = 2; i <= 19; i++) rep(j,9) rep(k,3) rep(c,9) {
        if (!j) f[i][j][k] += f[i-1][c][k];//当前位是0：计数不变
        else if (k) f[i][j][k] += f[i-1][c][k-1];//当前位非0：计数+1
    }
    while (t--) {
        cin >> l >> r;
        cout << query(r+1)-query(l) << '\n';
    }
    return 0;
}