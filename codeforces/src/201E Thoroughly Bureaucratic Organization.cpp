//
// Created by Psy.C on 2025/12/5.
//
/*
*计算在给定参数k下的某种"覆盖能力"：
lst：剩余资源，初始为m*k
res：结果计数，初始为1（表示至少能覆盖1个单位）
ad：当前系数，初始为1
 *
*计算组合数C(k,i) = k!/(i!(k-i)!)：
通过递推方式：C(k,i) = C(k,i-1) * (k-i+1) / i
这避免了直接计算阶乘可能导致的溢出
 *
*资源分配逻辑：
如果剩余资源足够支付ad*i的费用，则完全支付
否则只能部分支付：res增加lst/i个单位
然后跳出循环
 *如果结果超过阈值，返回无穷大；否则返回实际结果
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define inf 1000000000
using namespace std;

ll n, m;

ll ok(const ll k) {
    ll lst = m * k, res(1), ad(1);
    for (ll i = 1; i <= k; ++i) {
        ad = ad * (k - i + 1) / i;
        if (lst - ad * i > 0) {
            lst -= ad * i;
            res += ad;
        } else {
            res += lst / i;
            break;
        }
        if (res >= inf) return inf;
    }
    return res;
}

int main() {
    fast;
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        ll l(0), r(n);
        while (l < r) {
            const ll mid = (l + r) >> 1;
            if (ok(mid) >= n) r = mid;
            else l = mid + 1;
        }
        cout << l << '\n';
    }
    return 0;
}