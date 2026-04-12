//
// Created by Psy.C on 2026/4/12.
//
/**
k: 初始拥有的资源总数
n: 项目数量
nd[N]: 每个项目需要的资源量
had[N]: 每个项目已有的资源量

res = k: 初始化可用的额外资源
遍历每个项目：
如果 nd[i]*x > had[i]: 该项目x次操作需要的资源比已有的多
检查是否 nd[i]*x > had[i] + res: 是否即使加上额外资源也不够
如果是，返回false
否则，从额外资源中扣除所需数量：res -= nd[i]*x - had[i]
返回true表示x次操作可以完成

时间复杂度：O(n log(max_value))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

ll k, n, nd[N], had[N];
bool check(ll x) {
    ll res = k;
    for (int i = 1; i <= n; ++i)
        if (nd[i]*x > had[i]) {
            if (nd[i]*x > had[i] + res) return false;
            res -= nd[i]*x - had[i];
        }
    return true;
}

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> nd[i];
    ll l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> had[i];
        r = max(r, (had[i] + k)/nd[i]);//每个项目的理论最大执行次数
    }
    ll mid;
    while (r >= l) {
        mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;//可能还能执行更多
        else r = mid - 1;
    }
    cout << r << '\n';//最大可执行次数
    return 0;
}