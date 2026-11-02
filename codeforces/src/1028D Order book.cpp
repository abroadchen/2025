//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
mx 初始为极小值、mn 初始为极大值，表示一开始没有限制
在集合中插入两个哨兵 -inf 和 inf，方便后续用 lower_bound 找前驱后继而不越界
D（插入）‍：若 x 目前处在可行区间 [mx, mn] 内，说明它可以是候选，sum++（表示这段"自由区段"内有 sum 个可选位置）；然后插入集合。
I（查询）‍：这是一个核心操作——它相当于"确认当前位置取值为 x"。逻辑如下：
若 x 超出当前边界 [mx, mn]，则无解，输出 0。
若 x 是边界内部的点（x != mx && x != mn），则此前那段 区间内可选方案数翻倍（ans *= 2），因为 x 可以从区间内自由取值。
然后以 x 为基准，把边界收紧：mn 更新为集合中 x 的后继，mx 更新为集合中 x 的前驱，最后把 x 从集合中删除
最后答案 = ans * (sum + 1) % mod。sum+1 是最后一小段尚未确定的可选位置数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr ll inf = 0x3f3f3f3f3f3f3f3f, mod = 1e9+7;

set<ll> s;
ll n, x, mx(-inf), mn(inf), sum, ans(1);
char op[10];
int main() {
    fast;
    s.insert(inf); s.insert(-inf);
    auto it = s.begin();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op >> x;
        if (op[1] == 'D') {
            if (x >= mx && x <= mn) sum++;
            s.insert(x);
        } else {
            sum = 0;
            if (x > mn || x < mx) { cout << "0\n"; return 0; }
            if (x != mx && x != mn) ans = ans*2%mod;
            it = s.lower_bound(x); ++it;
            mn = *it; --it; --it;
            mx = *it; ++it;
            s.erase(it);
        }
    }
    cout << ans*(sum+1)%mod << '\n';
    return 0;
}