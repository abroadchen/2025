//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
返回从 x 顺时针（沿编号增大方向）走到 y 的距离：

若 y >= x，距离 y - x；
否则要绕一环走回去，距离 y - x + n。
即"环上单向顺时针弧长"
cnt[x]：起点为 x 的信的数量。（同一起点可能有多个信）
mn[x]：以 x 为起点出发的所有信中，目的地距离 x 最短的那一段弧长 dis(x,y)
对每一个起始点 i：
遍历所有起点位置 j（j 是该信发起的起点）：
dis(i,j)：先从 i 顺时针走到起点 j 那里。
n*(cnt[j]-1)：从 j 出发要送 cnt[j] 封信——第 1 封在抵达时顺带处理，剩下 cnt[j]-1 封每封都至少要绕一整环 n 才能回到 j 再取下一封（因为每次回到同一起点取信要绕一圈）。
mn[j]：在 j 那里，最后一次"送出这封信到最近目的地"所需的剩余弧长。
三者相加 = "从 i 出发，处理完 j 起点所有信所需的时间"。
对所有 j 取 max：因为不同的 j 起点的信是并行的，但最终要等都处理完，所以取最耗时的那个起点 j 作为总时间 ans。

对每个 i 输出它的总时间
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 5010;

int n;
int dis(int x, int y) {
    if (y >= x) return y - x;
    return y + n - x;
}

int m, cnt[N], mn[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) {
        int x, y; cin >> x >> y; cnt[x]++;
        if (mn[x] == 0) mn[x] = dis(x,y);
        else mn[x] = min(mn[x], dis(x,y));
    }
    rep(i,n) {
        int ans = 0;
        rep(j,n) ans = max(ans, dis(i,j)+n*(cnt[j]-1)+mn[j]);
        cout << ans << ' ';
    }
    return 0;
}