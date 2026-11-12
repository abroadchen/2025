//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
mx[i][0]、mx[i][1] 存第 i 层（桶）的两个代表端点。
cmp：按 x 从大到小，x 相同按 y 从小到大 排序。用来找每层的首尾端点
b 存所有 max(x,y)，排序去重 → 得到层的集合（值越大的层越"外圈"）。
a[i].num = 通过 lower_bound 得到该 max 对应的桶编号（1..m）。
id[k]：把所有 max(x,y) 相同的点归入同一桶 k。
这个分层的直觉：路径中 max 坐标只能单调不减，所以所有在"同一对角线/同一边界"上的点必须集中处理
每层排序后，取首尾作为该层的两个代表端点。
sum[i] = 这两个端点间的曼哈顿距离，即访问完该层所有点所必需的最小"层内移动代价"（因为这几个端点恰是层内极值，且在 L 形边界上，从一端口扫到另一端口可覆盖全层各类点）。
mx[0] 是原点 (0,0)，作为 DP 起点。
注：按 max 分层时，层是 L 形折线区域（直线 x=k 与 y=k 上的点）。首尾端点是该区域的"两个嘴"，所以层内代价定义为两端点间的曼哈顿距离，并从一层的一端进、另一层的一端出
dp[i][0]：访问完第 1..i 层后，最终停留在第 i 层的 mx[i][1] 端的最小代价。
dp[i][1]：访问完后停留在第 i 层的 mx[i][0] 端的最小代价。
注意代码写法上状态标注与到达端点呈现"镜像"（dp[i][0] 用 mx[i][1]，dp[i][1] 用 mx[i][0]），但数学上等价——因为两层端点之间会做 min 组合，最终答案取 min(dp[m][0], dp[m][1])。

转移含义：

访问第 i 层必须付出层内代价 sum[i]（从一种端口扫到另一端口）。
跨层：从上一层停留端 (mx[i-1][0] 或 mx[i-1][1]) 走到本层进入端，付出它们之间的曼哈顿距离。
两种"上一层停在哪个端 × 本层从哪个端进入"的组合都试遍，取最小。
边界：dp[0][0]=dp[0][1]=mx[0]=(0,0)，即从原点出发
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

struct node {
    ll x, y, num;
    bool operator < (const node &o) const {
        return max(x,y) < max(o.x,o.y);
    }
} a[N], mx[N][2];
bool cmp(node l, node r) {
    if (l.x != r.x) return l.x > r.x;
    return l.y < r.y;
}

ll n, b[N], sum[N], dp[N][2];
vector<ll> id[N];
vector<node> t;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i].x >> a[i].y, b[i] = max(a[i].x, a[i].y);//b[i] = 每个点的 max 坐标
    sort(b+1, b+n+1);
    ll m = unique(b+1,b+n+1) - b - 1;//去重后的不同 max 值个数
    rep(i,n) {
        a[i].num = lower_bound(b+1,b+m+1,max(a[i].x,a[i].y)) - b;//该点所属桶
        id[a[i].num].push_back(i);//桶里放入点下标
    }
    mx[0][0] = mx[0][1] = {0,0,0};//虚拟原点层（起始点）
    rep(i,m) {
        t.clear();
        for (auto j : id[i]) t.push_back(a[j]);
        ranges::sort(t, cmp);
        mx[i][0] = t[0], mx[i][1] = t[t.size()-1];//首端点 = x 最大的那个 末端点 = x 最小的那个
        sum[i] = abs(mx[i][0].x-mx[i][1].x)+abs(mx[i][0].y-mx[i][1].y);//层内曼哈顿跨度
    }
    rep(i,m) {
        dp[i][0] = min(dp[i-1][1]+sum[i]+abs(mx[i][1].x-mx[i-1][1].x)+abs(mx[i][1].y-mx[i-1][1].y),
            dp[i-1][0]+sum[i]+abs(mx[i][1].x-mx[i-1][0].x)+abs(mx[i][1].y-mx[i-1][0].y));
        dp[i][1] = min(dp[i-1][0]+sum[i]+abs(mx[i][0].x-mx[i-1][0].x)+abs(mx[i][0].y-mx[i-1][0].y),
            dp[i-1][1]+sum[i]+abs(mx[i][0].x-mx[i-1][1].x)+abs(mx[i][0].y-mx[i-1][1].y));
    }
    cout << min(dp[m][0],dp[m][1]);
    return 0;
}