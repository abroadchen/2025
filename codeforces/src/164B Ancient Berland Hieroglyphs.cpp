//
// Created by Psy.C on 2025/11/27.
//
/*
 *在数组c中建立映射：c[b[i]] = i，表示元素b[i]在数组b中的位置是i
 *i%n：确保索引在0到n-1范围内，实现循环访问数组a
 *
*如果元素a[i%n]不在数组b中（p==-1）：
清空队列q，因为连续性被中断
 *lst：获取队列最后一个元素在模m意义下的位置
*如果当前元素位置小于等于队尾元素位置：
说明发生了循环，需要调整p值
加上适当的m的倍数使p大于队尾元素
*否则（p > lst）：
计算基准值x
调整p为正确的相对位置
如果调整后仍不大于队尾，则再加上m
 *将调整后的p值加入队列尾部
*维护窗口大小不超过m：
移除队首那些与当前元素位置差超过m的元素
 */
#include <iostream>
#include <queue>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 1e6*2+5;
int n, m,
a[N], b[N], c[N];

int main() {
    fast;
    for (auto& x : c) x = -1;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) { cin >> b[i]; c[b[i]] = i; }
    int ans = 0; queue<ll> q;
    rep(i,2*n) {
        ll p = c[a[i%n]];
        if (p == -1) while (!q.empty()) q.pop();
        else {
            if (!q.empty()) {
                const ll lst = q.back() % m;
                if (p <= lst) p += ((q.back() - p) / m + 1) * m;
                else {
                    const ll x = (q.back() / m) * m;
                    p = x + p;
                    if (p <= q.back()) p += m;
                }
            }
            q.push(p);
            while (!q.empty() && q.front() <= p - m) q.pop();
        }
        ans = max(ans, static_cast<int>(q.size()));
    }
    cout << ans << '\n';
    return 0;
}