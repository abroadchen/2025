//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 元素个数
m: 操作次数
r: 加法常数
*a[N]: 主要数据数组
b[N]: XOR操作数组
k[N]: 权重数组
p[N]: 重排索引数组
ans: 答案变量
*cnt: 当前操作次数
pre: 上一步是否执行了XOR操作
 *如果操作次数达到上限，返回
*如果剩余操作次数为偶数：
计算当前数组a与权重数组k的内积
更新最大答案ans
 *如果上一步没有执行XOR操作
*对数组a执行XOR操作b
递归调用（标记已执行XOR）
恢复数组a的状态
 *
 *备份当前数组a到x
 *根据置换数组p重排a，并加上常数r
 *递归调用（标记未执行XOR）
 *恢复数组a的状态
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 333
#define inf 1e18
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int n, m, r;
ll a[N], b[N], k[N], p[N], ans;

void dfs(const int cnt, const bool pre) {
    if (cnt == m + 1) return;
    if ((m - cnt) % 2 == 0) {
        ll t = 0;
        rep(i,n) t += a[i] * k[i];
        ans = max(ans, t);
    }
    if (!pre) {
        rep(i,n) a[i] ^= b[i];
        dfs(cnt+1, true);
        rep(i,n) a[i] ^= b[i];
    }
    ll x[N];
    rep(i,n) x[i] = a[i];
    rep(i,n) a[i] = x[p[i]] + r;
    dfs(cnt+1, false);
    rep(i,n) a[i] = x[i];
}

int main() {
    fast;
    while (cin >> n >> m >> r) {
        rep(i,n) cin >> a[i];
        rep(i,n) cin >> b[i];
        rep(i,n) cin >> k[i];
        rep(i,n) cin >> p[i];
        ans = -inf;
        dfs(0, false);
        cout << ans << '\n';
    }
    return 0;
}