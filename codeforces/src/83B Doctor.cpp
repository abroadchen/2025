//
// Created by Psy.C on 2025/11/7.
//
/*
*n 元素个数
k 需要移除的元素总数
i 循环变量
a[N] 存储元素的数组
sum 元素总和
 *
 *函数ok，计算如果每个元素最多保留x个时，总共能保留多少个元素
 *对每个元素a[i]，最多保留min(a[i], x)个
 *
*二分搜索找到最大的x，使得ok(x) < k：

计算中间值mid
如果保留x个元素不够k个，说明x太小，调整左边界，记录当前x
否则x太大，调整右边界
 *
*对每个元素，移除min(a[i], x)个
更新剩余需要移除的元素数k
 *
*继续移除剩余的k个元素，采用循环策略：

从位置1开始遍历
如果元素还有剩余，则移除1个
记录最后移除元素的位置pos
直到k为0或遍历完所有元素
 *
*从pos+1位置开始，输出剩余元素的位置：

遍历从pos+1到n的所有位置
如果该位置还有元素，则输出位置并移除一个元素
 *
*继续从位置1到pos输出剩余元素的位置：

循环处理位置1到pos
如果该位置还有元素，则输出位置并移除一个元素

先从 pos+1 到 n 的位置开始移除
再从 1 到 pos 的位置继续移除
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(i=1;i<=n;++i)
using namespace std;

typedef long long ll;
const ll N = 1e5+7, inf = 1e9;
ll n, k, i, a[N], sum;

ll ok(ll x) {
    ll res(0);
    rep(i,n) res += min(a[i], x);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> k;
    rep(i,n) { cin >> a[i]; sum += a[i]; }
    if (sum < k) cout << -1 << "\n";
    else {
        ll l(0), r(inf), x(0);
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (ok(mid) < k) { l = mid + 1; x = mid; }
            else r = mid - 1;
        }
        rep(i,n) {
            ll val = min(a[i], x);
            a[i] -= val;
            k -= val;
        }
        ll pos(0);
        for (ll i = 1; i <= n && k; ++i) {
            if (a[i] > 0) {
                a[i]--;
                k--;
                pos = i;
            }
        }
        for (ll i = pos + 1; i <= n; ++i) {
            if (a[i]) {
                cout << i << ' ';
                a[i]--;
                k--;
            }
        }
        rep(i,pos) if (a[i]) {
            cout << i << ' ';
            a[i]--;
            k--;
        }
    }
    return 0;
}