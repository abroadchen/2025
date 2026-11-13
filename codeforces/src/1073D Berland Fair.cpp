//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
n, tot     // n 种物品，预算 tot
a[i]       // 第 i 个物品的单价
ans        // 累计能买的总件数
sum, cnt   // 每轮累加和、本轮的件数
按顺序扫描所有物品，在不超过预算 tot 的前提下，能放就放，得到：

sum：这一轮能塞进的总价格；
cnt：这一轮塞进的数量
sum 是"买满一轮"的总价。
因为每一轮摆放是固定的（顺序、集合都一致），只要预算还够塞满一整轮（即 tot >= sum），就可以同一轮重复 tot/sum 次，一次性累加 (tot/sum)*cnt 件，然后把预算 tot 取模 sum 缩小。
由此大幅加速——不必一点一点减，而是按"整轮"批量减
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

int n;
ll tot, a[N], ans, sum, cnt;
int main() {
    fast;
    cin >> n >> tot;
    rep(i,n) cin >> a[i];
    while (1) {
        sum = 0, cnt = 0;
        rep(i,n) if (sum+a[i] <= tot) sum += a[i], cnt++;
        if (cnt == 0) break;//一个都塞不进去 → 结束
        ans += tot/sum*cnt; tot%=sum;//预算缩减为余数
    }
    cout << ans << '\n';
    return 0;
}