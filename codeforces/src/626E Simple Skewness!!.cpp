//
// Created by Psy.C on 2026/3/27.
//
/**
如果n为1或2，直接输出第一个元素，因为此时最优解总是包含一个元素

len: 最优解的长度参数
mid: 最优解的中间位置
m: 最优解对应的差值
寻找在位置i处的最佳扩展长度
lm和rm是三分的两个分割点
比较a1*(rm*2+1)和a2*(lm*2+1)来决定搜索方向
这里是在寻找平均值最大的区间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

ll n, s[N<<1];
///从位置i-j到i的元素和加上从位置n-j+1到n的元素和
ll sum(int i, int j) {
    return s[n] - s[n-j] + s[i] - s[i-j-1];
}
ll a[N<<1];
int main() {
    fast;
    cin >> n;
    for (ll i = 1; i <= n; ++i) cin >> a[i];
    if (n == 1 || n == 2) {
        cout << "1\n" << a[1] << '\n';
        return 0;
    }
    sort(a + 1, a + n + 1);
    for (ll i = 1; i <= n; ++i) s[i] = s[i-1] + a[i];
    ll len = 0, mid = 1, m = 0;
    for (ll i = 2; i <= n-1; ++i) {//遍历每个可能的中心位置i（从2到n-1）
        ll l = 0, r = min(i-1, n-i);//当前位置i能扩展的最大距离
        while (l < r) {
            ll lm = (2*l+r)/3, rm = (l+2*r+2)/3,
            a1 = sum(i, lm), a2 = sum(i, rm);
            if (a1*(rm*2+1) < a2*(lm*2+1)) l = lm+1;
            else r = rm-1;
        }
        //当前方案的差值：左右两段的和减去中间元素乘以总个数
        ll t = (s[i]-s[i-l-1]+s[n]-s[n-l]) - a[i]*(l*2+1);
        if (t*(len*2+1) > m*(l*2+1)) {//当前方案更优
            m = t; len = l; mid = i;//更新最优解的参数
        }
    }
    cout << len*2+1 << '\n';//最优解的总长度
    //先输出从mid-len到mid的连续元素，再输出最后len个元素
    for (ll i = mid-len; i <= mid; ++i) cout << a[i] << ' ';
    for (ll i = n-len+1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}