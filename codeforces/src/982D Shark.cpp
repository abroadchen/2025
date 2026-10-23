//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
并查集 fa，用于维护"当前已激活点的连通块"。
find 带路径压缩
b 存 (权值, 位置下)，按权值从小到大排序。
这样依次处理时，就是按权值从小到大"逐个激活"位置
sum[x]：以 x 为若干连通块根时，该连通块的大小（激活点数）。
cnt[s]：当前大小为 s 的连通块有多少个。
tot：当前被激活的点的总数（也是当前连通块的总点数
其实这里 tot 注释上说的是"激活点总数"，但 uni 里 tot-- 表示合并两个连通块后，连通块数量减 1（tot 记录的是连通块个数）。命名有点误导，但逻辑是：合并后连通块数减一。
cnt[sum] 维护"当前大小为 sum 的连通块个数"，便于快速判断"是否只剩一个大块"。
注意：tot 初始在激活单个点时 tot++（此时 +1 是连通块数 +1），在 uni 里 tot--（合并两块减一）。所以 tot 语义 = 当前连通块个数
按权值从小到大，逐个激活位置 x（即把 a[x] 视为"当前阈值下的最低激活值"）。
激活时：sum[x]=1（自身成一个点）、cnt[1]++（一个大小为 1 的块）、tot++（块数 +1）。
若相邻位置已被激活（即 a[相邻] < a[x]，因为更小的权值更先被激活）则合并：
x+1 被激活且 a[x+1] < a[x] → 右合并
x-1 被激活且 a[x-1] < a[x] → 左合并
判断条件 tot == cnt[sum[find(x)]]：
sum[find(x)] = 当前 x 所在连通块的大小。
cnt[sum[find(x)]] = 大小为该值的连通块个数。
tot（连通块总数）等于"大小为最大块的个数"，意味着当前所有激活点已经合并成恰好一个连通块（整块大小 = 当前激活总数）。
若满足，表示当前阈值下激活点构成一个完整连通块，记录答案 y+1（当前权值 y 对应的阈值，+1 是取"下一位"作为阈值上界）。
用 mx 记录能成立的最大 tot（即能构成完整连通块时激活点数最多、对应最大阈值），ans 对应最大阈值。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int sum[N], cnt[N], tot;
void uni(int x, int y) {
    x = find(x), y = find(y);
    cnt[sum[x]]--, cnt[sum[y]]--;
    sum[x] += sum[y]; fa[y] = x;
    cnt[sum[x]]++;
    tot--;
}

int n, a[N];
ii b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i].first = a[i]; b[i].second = i; fa[i] = i;
    }
    sort(b+1, b+n+1);
    int mx = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = b[i].second, y = b[i].first;
        sum[x] = 1; cnt[1]++; tot++;
        if (x != n && a[x+1] < a[x]) uni(x, x+1);
        if (x != 1 && a[x-1] < a[x]) uni(x-1, x);
        if (tot == cnt[sum[find(x)]]) if (tot > mx) { mx = tot; ans = y+1; }
    }
    cout << ans << '\n';
    return 0;
}