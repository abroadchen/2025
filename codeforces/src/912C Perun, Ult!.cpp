//
// Created by Psy.C on 2026/10/12.
//
/**
有 n 只生物/建筑，初始生命 h[i]、初始攻击/当前值 st[i]，每秒恢复 re[i]。
有 m 个事件：在时刻 x，第 y 只生物的参数变为 z。
我们要找到一个时刻 t，统计"在时刻 t，有多少生物满足某个条件（其当前值 ≤ 阈值 d）"，设这个数量为 cnt，则收益 = cnt × (b + t×ic)，求最大收益。
对每只生物，它能"满足条件"的时间段是一个连续区间（因为值是随时间线性变化的），把这些区间加入扫描线，用差分 + 坐标离散化求每个时间点上的最大覆盖数 × 收益，取最大值
o：坐标离散化数组（存储所有区间的关键时间点）。
get(x)：在 o 中二分查找 x 的下标，用于下标的差分
v[i]：第 i 只生物的"参数变化事件"序列，每个元素是 (时刻, 新值)。
add：每个生物满足条件的时间区间列表 (起, 止)。
cnt：差分数组
对每只生物读入初始生命 h、初始当前值 st、恢复速度 re，并把 (时刻0, st[i]) 作为它的初始状态压入 v[i]。
对每个事件读入 x(时刻)、y(哪只)、z(新值)，压入 v[y]
若某生物的生命上限 h[i] <= d 且 ic（随时间能继续增加收益的系数）非零，则说明该生物当前值永远能 ≤ d（因为上限都没超过 d），能被无限利用 → 收益无限大，输出 -1。
换句话说：如果一个生物永远满足条件，而 ic>0 使得越晚收益越高，那么没有最优解（可达无穷大）
把每只生物的参数变化事件按时间排序
遍历第 i 只生物的每段"状态维持期"：
up = 这段状态的结束时刻：若非最后一段，则是下一事件时刻 - 1；若是最后一段，则无上限 inf。
若这段的当前值 v[i][j].second > d，则这段时间内该生物不满足条件，跳过。
如果恢复速度 re[i] != 0（当前值随时间增长）：
ret = (d - 当前值)/re[i]：从当前值增长到刚好 ≤ d 所需的时间。
满足条件的时间段 = [本段开始时刻, min(up, 开始+ret)]，因为超过这个点值就超过 d 了。
把区间加入 add，并把起/止端点加入离散化 o。
如果 re[i] == 0（当前值不随时间变）：
若 up 无上限（永远这段）且 ic 非零 → 该生物能永远满足且越晚收益越高 → 无解，输出 -1。
否则区间 = [开始, up]，加入 add 和 o
对 o 去重排序，得到所有关键时间点。
cnt 是差分数组（长度 = 去重后的点数）。
对每个区间 (fst, snd)：
在左端点 get(fst) 处 +1，在右端点之后 get(snd+1) 处 -1（区间覆盖的差分技巧）。
前缀和扫描：
cnt[i] += cnt[i-1]：累加前缀和，cnt[i] 即为在时间点 o[i] 时同时满足条件的生物数量（即点权，区间覆盖层数）。
收益 = cnt[i] × (b + (o[i+1]-1)*ic)：b + (该时刻)*ic 是"每单位 cnt 的收益"，随 t 线性增长。
ans 取所有时刻的最大收益。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define For(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
#define pll pair<ll, ll>
#define sz(a) ((int)(a).size())
using namespace std;

constexpr int N = 1e5+7;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fLL;

vector<ll> o;
int get(ll x) { return lower_bound(o.begin(), o.end(), x) - o.begin(); }

int n, m;
ll b, ic, d, h[N], st[N], re[N], x, y, z;
vector<pll> v[N], add;
vector<ll> cnt;
int main() {
    fast;
    cin >> n >> m >> b >> ic >> d;
    rep(i,1,n) { cin >> h[i] >> st[i] >> re[i]; v[i].emplace_back(0, st[i]); }
    rep(i,1,m) { cin >> x >> y >> z; v[y].emplace_back(x, z); }
    rep(i,1,n) if (h[i] <= d && ic) { cout << "-1\n"; return 0; }
    rep(i,1,n) ranges::sort(v[i]);
    rep(i,1,n) For(j,sz(v[i])) {
        ll up = j < sz(v[i])-1 ? v[i][j+1].first-1 : inf;
        if (v[i][j].second > d) continue;
        if (re[i]) {
            ll ret = (d - v[i][j].second)/re[i];
            add.emplace_back(v[i][j].first, min(up, v[i][j].first+ret));
            o.push_back(v[i][j].first);
            o.push_back(min(up, v[i][j].first+ret)+1);
        } else {
            if (up == inf && ic) { cout << "-1\n"; return 0; }
            add.emplace_back(v[i][j].first, up);
            o.push_back(v[i][j].first);
            o.push_back(up+1);
        }
    }
    ll ans = 0;
    ranges::sort(o);
    o.erase(ranges::unique(o).begin(), o.end());
    cnt.resize(sz(o));
    for (auto&[fst, snd] : add) {
        cnt[get(fst)]++; cnt[get(snd+1)]--;
    }
    For(i,sz(cnt)) {
        if (i) cnt[i] += cnt[i-1];
        ans = max(ans, 1ll*cnt[i]*(b+(o[i+1]-1)*ic));
    }
    cout << ans << '\n';
    return 0;
}