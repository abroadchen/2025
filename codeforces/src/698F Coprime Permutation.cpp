//
// Created by Psy.C on 2026/4/17.
//
/**
W:随机值, sqf:平方因子, w:异或值

质数处理：
w[i] = W[n/i]：质数i的异或值
sqf[i] = i：质数的平方因子为其自身
++C[n/i]：计数
mx[i] = i：最大质因子
合数处理：
w[v] = w[i]^w[pri[j]]：异或操作（当i与pri[j]互质时）
sqf[v] = sqf[i]*sqf[pri[j]]：平方因子计算
w[v] = w[i], sqf[v] = sqf[i]：当i包含pri[j]因子时

筛法：O(n)
验证：O(n)
计算答案：O(∑c[i] + ∑C[i])
总体：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ut unsigned int
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;
int get() {
    int x; cin >> x;
    return x;
}
mt19937 rnd;///梅森旋转算法随机数生成器
ut W[N], sqf[N], w[N];
int mx[N], C[N], pri[N], cnt, c[N], mp[N], pm[N];
bool b[N];//是否为合数
int main() {
    fast;
    int n = get();
    for (int i = 1; i <= n; ++i) W[i] = rnd();
    sqf[1] = 1; mx[1] = n; ++C[1]; w[1] = W[1];
    for (int i = 2; i <= n; ++i) {
        if (!b[i]) pri[cnt++] = i, w[i] = W[n/i], sqf[i] = i, ++C[n/i], mx[i] = i;
        for (int j = 0; j < cnt && i*pri[j] <= n; ++j) {
            int v = i*pri[j]; b[v] = 1; mx[v] = mx[i];
            if (i%pri[j]) w[v] = w[i]^w[pri[j]], sqf[v] = sqf[i]*sqf[pri[j]];
            else {
                w[v] = w[i];
                sqf[v] = sqf[i];
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i) ++c[sqf[i]];
    for (int i = 1; i <= n; ++i) {
        int x = get();
        if (x == 0) continue;
        //异或值必须相同（意味着相同的结构）
        if (w[i] != w[x]) return cout << "0\n", 0;
        //映射一致性
        if (mp[mx[i]] && mp[mx[i]] != mx[x]) return cout << "0\n", 0;
        //双射一致性
        if (pm[mx[x]] && pm[mx[x]] != mx[i]) return cout << "0\n", 0;
        if (!mp[mx[i]] && !pm[mx[x]]) --C[n/mx[i]];//更新计数
        mp[mx[i]] = mx[x]; pm[mx[x]] = mx[i];//建立映射
        --c[sqf[i]];//更新平方因子计数
    }
    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= c[i]; ++j)//计算c[i]的阶乘
            ans = ans*1ll*j%mod;
        for (int j = 1; j <= C[i]; ++j)//计算C[i]的阶乘
            ans = ans*1ll*j%mod;
    }
    cout << ans << '\n';
    return 0;
}