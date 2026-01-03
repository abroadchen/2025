//
// Created by Psy.C on 2026/1/3.
//
/**
 *
*a[N]：记录数组a中每个二进制位的计数
b[N]：记录数组b中每个指数的计数
s[N]：存储2的幂次（s[i] = 2^i）
 *
*一个在位置idx的数位代表值：1 × 2^idx
这个值可以分解为：(2^(idx-k)) × (2^k) = (s[idx-k]) × (2^k)
所以1个idx位置的值 = s[idx-k]个k位置的值
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 41
using namespace std;

ll a[N], b[N], s[N];
int solve(const ll k) {//用更高位来表示当前位的需求
    ll x = 0, idx = 0;
    for (ll i = k + 1; i < N; ++i) if (a[i]) {
        x = 1; idx = i; break;
    }
    if (!x) return 0;//没有找到可用的更高位
    const ll t = b[k] / s[idx - k];//需要多少个更高位来替换
    if (t == 0) {
        for (ll i = k + 1; i < idx; ++i) a[i] += 1;//中间位加1
        a[k] += 2;//k位置加2
        a[idx] -= 1;//高位减1
        return 1;
    }
    const ll mn = min(t, a[idx]);
    a[idx] -= mn;
    a[k] += mn * s[idx - k];
    return 1;
}


int main() {
    fast;
    for (int i = 0; i < N; ++i) s[i] = 1ll * (1<<i);
    ll n, m, k, ans = 0; cin >> n >> m;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (ll i = 0; i < n; ++i) {
        cin >> k;
        for (ll j = 0; j < N && k >= s[j]; ++j) if (k & s[j]) a[j]++;//统计k的二进制表示
    }
    for (ll i = 0; i < m; ++i) { cin >> k; b[k]++; }//统计数组b中每个指数的出现次数
    int flg = 1;
    for (ll i = 0; i < N; ++i) {
        while (b[i]) {//还有未处理的元素时
            const ll t = min(a[i], b[i]);
            a[i] -= t;//减去匹配的数量
            b[i] -= t;
            ans += t;//累加匹配数量到答案
            if (b[i]) { if (!solve(i)) { flg = 0; break; } } else break;//尝试解决剩余部分
        }
        if (!flg) break;//如果无法解决，跳出循环
    }
    cout << ans << '\n';
    return 0;
}