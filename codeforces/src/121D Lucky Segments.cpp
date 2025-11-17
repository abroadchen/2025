//
// Created by Psy.C on 2025/11/17.
//
/*
 *n（区间数量）和k（目标值）
*创建左右端点向量
读取每个区间的左右端点
记录最小区间长度到inf
*获取所有幸运数字
如果没有幸运数字，输出0并退出
 *复制左右端点向量并排序
*使用128位整数避免溢出
计算前缀和数组pl（左端点）和pr（右端点）
tot存储所有左端点之和
 *对于给定值a，所有大于a的左端点与a的差值之和
 *对于给定值b，b与所有小于b的右端点的差值之和
 *
*初始化双指针j0和j
对每个幸运数字x[i]，找到在[x[i], x[i]+inf]范围内的最大索引j0
 *调整j指针，找到满足条件的最大j值
 *更新最大区间长度j-i
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define N 2000000000000000000ll
using namespace std;

typedef long long ll;
ll inf = 2e18;

vector<ll> get() {
    vector<ll> res;
    queue<ll> q; q.push(4); q.push(7);
    while(!q.empty()) {
        ll t = q.front(); q.pop();
        if (t > N) continue;
        res.push_back(t);
        ll nxt1 = t * 10 + 4, nxt2 = t * 10 + 7;
        if (nxt1 <= N) q.push(nxt1);
        if (nxt2 <= N) q.push(nxt2);
    }
    sort(res.begin(), res.end());
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, k; cin>>n>>k;
    vector<ll> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin>>l[i]>>r[i];
        ll len = r[i] - l[i];
        if (len < inf) inf = len;
    }
    vector<ll> x = get();
    int m = x.size();
    if (m == 0) { cout << 0 << '\n'; return 0; }
    vector<ll> ls = l, rs = r;
    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    using int128 = __int128;
    vector<int128> pl(n + 1, 0), pr(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pl[i + 1] = pl[i] + (int128)ls[i];
        pr[i + 1] = pr[i] + (int128)rs[i];
    }
    int128 tot = pl[n];

    auto f = [&](ll a) -> int128 {
        auto it = upper_bound(ls.begin(), ls.end(), a);
        int pos = it - ls.begin();
        ll cnt = n - pos;
        if (cnt == 0) return 0;
        int128 suml = tot - pl[pos];
        return suml - (int128)a * cnt;
    };
    auto g = [&](ll b) -> int128 {
        auto it = lower_bound(rs.begin(), rs.end(), b);
        int pos = it - rs.begin();
        ll cnt = pos;
        if (cnt == 0) return 0;
        return (int128)b * cnt - pr[pos];
    };
    int j0(0), j(0);
    ll ans(0);
    for (int i = 0; i < m; ++i) {
        while (j0 < m && x[j0] <= x[i] + inf) j0++;
        int128 v = f(x[i]), w = (int128)k - v;
        if (j < i) j = i;
        while (j < j0) {
            int128 v2 = g(x[j]);
            if (v2 <= w) j++;
            else break;
        }
        if (j - i > ans) ans = j - i;
    }
    cout << ans << '\n';
    return 0;
}