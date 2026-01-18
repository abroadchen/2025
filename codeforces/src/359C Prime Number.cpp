//
// Created by Psy.C on 2026/1/18.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define mod 1000000007
using namespace std;

ll ksm(ll x, ll p) {
    ll ans = 1; x = x % mod;
    while (p) {
        if (p&1) ans = ans * x % mod;
        x = x*x % mod;
        p >>= 1;
    }
    return ans % mod;
}


int main() {
    fast;
    ll n, k, sum = 0, a[N]; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i], sum += a[i];
    for (int i = 0; i < n; ++i) a[i] = sum - a[i];//除自身外其他所有元素的和
    a[n] = -1;//哨兵值-1，用于边界检测
    sort(a, a + n);
    ll cnt = 1, ans;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != a[i-1]) {
            ///a[0]...a[i-1] 这些元素都是相同的 a[i] 是一个新的不同值
            //cnt 是这个值 a[i-1] 出现的次数
            if (cnt % k == 0) {//相同元素的个数能被k整除
                cnt /= k;
                //将k个a[i-1]合并为1个(a[i-1]+1) 把这个新值赋给a[i-1]
                a[i - 1] += 1;//合并k个元素为1个更高值的元素
                i--;//回退一步重新检查  数组可能是无序的 重新检查位置i是否与前一个值相同
            } else {
                //a[i-1]就是最终稳定状态的值
                ans = a[i - 1];//记录当前值作为答案
                break;
            }
        } else cnt++;
    }
    ans = min(ans, sum);//限制在不超过原始总和的范围内
    cout << ksm(k, ans) << '\n';
    return 0;
}