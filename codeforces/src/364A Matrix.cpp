//
// Created by Psy.C on 2026/1/20.
//
/*
* 预处理：O(n²)
查询：O(结果数量)
总体：O(n²)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000100
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;


int main() {
    fast;
    int a, sum[N]; cin >> a;
    char s[N]; string str; cin >> str;
    const int n = static_cast<int>(str.length());
    strcpy(s + 1, str.data());
    rep(i,n) sum[i] = sum[i-1] + s[i] - '0';//字符转为数字
    ll cnt[N], ans = 0;
    rep(i,n) rep(j,i) cnt[sum[i] - sum[j-1]]++;//从位置j到i的子串对应的数值
    if (a == 0) {
        //包含0子串的所有组合数 减去重复计算的部分
        cout << cnt[0] * n * (n + 1) - cnt[0] * cnt[0] << '\n';
        return 0;
    }
    rep(i,n) rep(j,i) {//遍历所有子串
        if (const int num = sum[i] - sum[j-1]; num != 0 && a % num == 0 && a / num < N)
            ans += cnt[a/num];//：累加对应因子的数量
    }
    cout << ans << '\n';
    return 0;
}