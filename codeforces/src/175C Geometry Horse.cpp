//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 物品数量
m: 需求点数量
p[N]: 需求点数组
ans: 最终答案（总成本）
 *
*k: 数量
c: 单价
*op: 已经购买的数量累计
f: 当前处理的需求点索引
 *
*a[i].k - j + 1: 当前物品剩余数量
p[f] - op: 到达下一个需求点还需要的数量
取两者较小值
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 105;
int n, m, p[N], ans;
struct node { int k, c; } a[N];
inline bool cmp(const node& x, const node& y) { return x.c < y.c; }

signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i].k >> a[i].c;
    sort(a + 1, a + n + 1, cmp);
    cin >> m;
    rep(i,m) cin >> p[i];
    p[m+1] = 0x7fffffffffff;
    int op=0, f=1;
    rep(i,n) {//遍历每个物品（按单价从低到高）
        for (int j = 1; j <= a[i].k;) {//处理第i个物品的k个单位
            const int x = min(a[i].k - j + 1, p[f] - op);
            ans += f * a[i].c * x;//累加成本：需求点编号 × 单价 × 购买数量
            op += x;//更新已购买总量
            while (op >= p[f] && f <= m) f++;//如果已购买量达到或超过当前需求点，推进到下一个需求点
            j += x;//更新当前物品已处理的数量
        }
    }
    cout << ans << '\n';
    return 0;
}