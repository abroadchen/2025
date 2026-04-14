//
// Created by Psy.C on 2026/4/13.
//
/**
将字符串转换为整数
处理负号
逐位解析数字

计算多项式在x=k处的值模m
使用霍纳法则：a[n]*k^n + ... + a[1]*k + a[0]

flag: 未知数('?')的数量
sur: 已知数的数量
hf: 交替标志
读入n+1个系数
如果是'?'，增加未知数计数
如果是数字，解析并标记已知，翻转hf标志

特殊情况：k=0
如果a[0]未知，根据hf决定结果
如果a[0]已知，根据是否为0决定结果
有未知数的情况
如果未知数个数和已知数个数奇偶性不同，输出"No"
否则输出"Yes"
无未知数的情况（数值验证）
使用随机模数验证多项式是否为0
进行100次随机测试
如果存在某个模数下多项式值不为0，说明多项式不恒为0，输出"No"
如果所有测试都通过，输出"Yes"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

int get(const char *s) {
    int flag = 1, res = 0;
    if (s[0] == '-') flag = -1;
    else res = s[0] - '0';
    for (int i = 1; s[i]; ++i)
        res = res * 10 + s[i] - '0';
    return flag * res;
}

int n, k, a[N];
bool get(ll m) {
    ll res = 0;
    for (int i = n; i >= 0; --i) {
        res = res*k%m + a[i];
        res %= m;
    }
    return res;
}

char s[10];
bool issur[N];
int main() {
    fast;
    cin >> n >> k;
    int flag = 0, sur = 0, hf = 0;
    for (int i = 0; i <= n; ++i) {
        cin >> s;
        if (s[0] == '?') ++flag;
        else a[i] = get(s), sur++, issur[i] = 1, hf = !hf;
    }
    if (k == 0) {
        if (!issur[0]) cout << (hf ? "Yes" : "No") << '\n';
        else cout << (a[0] ? "No" : "Yes") << '\n';
        return 0;
    }
    if (flag) {
        if (flag % 2 != sur % 2) cout << "No\n";
        else cout << "Yes\n";
    } else {
        for (int i = 0; i < 100; ++i)
            if (get((ll)rand()*11234ll*5135ll*15ll%mod)) {
                cout << "No\n";
                return 0;
            }
        cout << "Yes\n";
    }
    return 0;
}