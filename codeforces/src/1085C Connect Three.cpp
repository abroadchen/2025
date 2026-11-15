//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
排序后：p[0].y <= p[1].y <= p[2].y（升序）。关键：中间那个点（按 y 排序后）是 p[1]
第一步：水平线（y = 中间点的 y）‍
沿 y = p[1].y（中间点的 y），从最左 x 到最右 x 铺一整行水平线。这条水平线一定经过 p[1]（因为它的 x 在 [l,r] 区间内）
第二步：左边竖线（若需要）‍
从 p[0].y 到 p[1].y-1，沿 x = p[0].x 垂直铺列，覆盖最低点 y 到水平线之间。这样 p[0] 就被连上水平线了
第三步：右边竖线（若需要）‍
从 p[1].y+1 到 p[2].y，沿 x = p[2].x 垂直铺列，覆盖水平线到最高点 y 之间。这样 p[2] 也被连上

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
using namespace std;

struct node {
    int x, y;
    bool operator<(const node &o) const {
        return y < o.y;
    }
} p[3];

vector<node> ans;
int main() {
    fast;
    cin >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> p[2].x >> p[2].y;
    int l = min(p[0].x, min(p[1].x,p[2].x));//最左 x
    int r = max(p[0].x, max(p[1].x,p[2].x));//最右 x
    sort(p, p+3);
    rep(i,l,r) ans.push_back({i,p[1].y});
    rep(i,p[0].y,p[1].y-1) ans.push_back({p[0].x,i});
    rep(i,p[1].y+1,p[2].y) ans.push_back({p[2].x,i});
    cout << ans.size() << '\n';
    rep(i,0,ans.size()-1) cout << ans[i].x << ' ' << ans[i].y << '\n';
    return 0;
}