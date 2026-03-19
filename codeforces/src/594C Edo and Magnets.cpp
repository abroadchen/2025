//
// Created by Psy.C on 2026/3/19.
//
/**
n：点的数量
K：最多可选择的点数
d1,d2,d3,d4：存储不同排序顺序下的前K+1个点ID
cnt：当前选中点的数量
v[N]：访问标记数组
d1[i] = a[i].id：存储x坐标最小的K+1个点ID
d2[i] = a[n-i+1].id：存储x坐标最大的K+1个点ID
d3[i] = a[i].id：存储y坐标最小的K+1个点ID
d4[i] = a[n-i+1].id：存储y坐标最大的K+1个点ID
按原始ID排序，恢复原始顺序
三层循环枚举三种类型点的数量
使用计数数组v标记已选择的点
!v[d1[z]]++：如果未访问过则计数加1并标记为已访问
用二分的方式确定第四种类型点的数量l
清空访问标记
如果选中的点数超过K，跳过当前组合
a[d2[j+1]].x - a[d1[i+1]].x：剩余点的x坐标范围
x1++, x1 >>= 1：计算 (x1+1)/2，相当于向上取整除以2
计算y方向范围并做同样处理
更新最小面积
时间复杂度通过枚举限制在O(K³logK)范围内
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;
constexpr int N = 1e5+5, M = 15;
constexpr ll inf = 1e18;
struct node { int x, y, id; } a[N];
int n, K, d1[M], d2[M], d3[M], d4[M], cnt, v[N];
int main() {
    fast;
    cin >> n >> K;
    for (int i = 1, c, d, e, f; i <= n; ++i) {
        cin >> c >> d >> e >> f;
        a[i] = {c+e, d+f, i};
    }
    sort(a + 1, a + n + 1, [](node x, node y) {
        return x.x < y.x;
    });
    rep(i,K+1) d1[i] = a[i].id, d2[i] = a[n-i+1].id;
    sort(a + 1, a + n + 1, [](node x, node y) {
        return x.y < y.y;
    });
    rep(i,K+1) d3[i] = a[i].id, d4[i] = a[n-i+1].id;
    sort(a + 1, a + n + 1, [](node x, node y) {
        return x.id < y.id;
    });
    ll ans = inf;
    for (int i = 0; i <= K; ++i)
        for (int j = 0; j <= K; ++j)
            for (int k = 0; k <= K; ++k) {
                rep(z,i) cnt += !v[d1[z]]++;//添加d1中的前i个点
                rep(z,j) cnt += !v[d2[z]]++;//添加d2中的前j个点
                rep(z,k) cnt += !v[d3[z]]++;//添加d3中的前k个点
                int l = 0;
                while (cnt <= K && l <= K) cnt += !v[d4[++l]]++;//添加d4中的点直到超过K个
                if (cnt > K && l) cnt -= !--v[d4[l--]];//回退最后一个
                rep(z,i) v[d1[z]] = 0;
                rep(z,j) v[d2[z]] = 0;
                rep(z,k) v[d3[z]] = 0;
                rep(z,l) v[d4[z]] = 0;
                if (cnt > K) { cnt = 0; continue; }
                cnt = 0;
                int x1 = max(a[d2[j+1]].x - a[d1[i+1]].x, 1);
                x1++, x1 >>= 1;
                int y1 = max(a[d4[l+1]].y - a[d3[k+1]].y, 1);
                y1++, y1 >>= 1;
                ans = min(ans, 1ll*x1*y1);
            }
    cout << ans << '\n';
    return 0;
}