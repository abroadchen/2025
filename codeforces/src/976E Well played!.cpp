//
// Created by Psy.C on 2026/10/22.
//
/***
node：每个怪物含 hp、dmg。
cmp：按 hp - dmg（血量高于伤害的差值）从大到小排序；差值相等时按 hp 从大到小。
也就是：hp 相对 dmg 越"富余"的怪物排越前面
读入 n、a、b（a 是翻倍次数，b 是可用技能次数）。
读入每个怪物的 hp、dmg。
排序。
res：所有 dmg 之和（基线总伤害）。
d[i] 记录每个怪物的原始 dmg（后面再改用）
b 为 0 → 没有任何特权技能 → 总伤害就是所有 dmg 之和 res，直接输出结束
遍历每个怪物：若对其用 a 次翻倍技能，其伤害从 dmg 提升到 hp * 2^a，增量 = 2^a * hp - dmg。
取所有怪物中增量最大的 mx（贪心：翻倍技能只对单个怪物用最有收益的那个）。
res += mx：把最优增量加进去
遍历（已按 hp−dmg 降序排列）‍前 r 个怪物：只要 hp > dmg 且还有 b 次，就免费把 dmg 提升到 hp，消耗一次 b，计数 r。
中途若发现当前怪 hp <= dmg（无提升空间）或 b 用完，就 break。
用提升后的 dmg 重新累加 ans（此时把部分怪物的 dmg 顶到了 hp）
r 是已经被免费提升的怪物个数。
在已提升的 r 个怪物中找最大 hp mxt。
初始 xx = (2^a - 1) * mxt：把翻倍技能用在已被提升、hp 最大的怪物上，额外增量 = 2^a·hp − hp（因为其 dmg 已被提升到 hp，增量是从 hp 到 2^a·hp）。
mt = s[r].dmg、mn = r 记录边界信息
若 b 还有剩余（提升技能没全用完）：翻倍技能的增量可能放在未被提升的怪物上收益更大——对 i = r+1..n（未提升的怪物）计算 2^a·hp − dmg，取最大更新 xx。
若 b 用完了：对未提升怪物计算时需考虑边界调整 now - mt + d[mn]（因为某个已被提升的怪物 cf. 逻辑，可能要用 dmg 原始值补偿），同样取最大。
now 本质与第 4 步相同的增量公式，区别在于处理「提升技能是否耗尽」时的边界修正
ans 是第二步"免费提升 dmg→hp"后的总伤害，xx 是翻倍技能带来的增量。
若 xx + ans 大于基准 res，输出 xx+ans，否则输出 res。即 max(res, ans+xx)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

struct node { int hp, dmg; } s[N];
inline bool cmp(const node &a, const node &b) {
    if (a.hp - a.dmg == b.hp - b.dmg) return a.hp > b.hp;
    return a.hp - a.dmg > b.hp - b.dmg;
}

int n, a, b, i, d[N];
signed main() {
    fast;
    cin >> n >> a >> b;
    rep(i,n) cin >> s[i].hp >> s[i].dmg;
    sort(s+1, s+1+n, cmp);
    int r = 0, mx = -1, res = 0;
    rep(i,n) res += s[i].dmg, d[i] = s[i].dmg;
    if (b == 0) { cout << res; return 0; }
    if (b) {
        rep(i,n) {
            int x = s[i].dmg, now = (1ll<<a)*s[i].hp-x;
            mx = max(mx, now);
        }
        res = res + mx;
    }
    rep(i,n) {
        if (s[i].hp <= s[i].dmg || !b) break;
        s[i].dmg = s[i].hp; --b; ++r;
    }
    int ans = 0;
    rep(i,n) ans += s[i].dmg;
    int mxt = -1, mt = s[r].dmg, mn = r;
    rep(i,r) if (s[i].hp > mxt) mxt = s[i].hp;
    int xx = ((1ll<<a)-1)*mxt;
    if (b > 0) {
        for (i = r+1; i <= n; ++i) {
            int x = s[i].dmg, now = (1ll<<a)*s[i].hp-x;
            xx = max(xx, now);
        }
    } else {
        for (i = r+1; i <= n; ++i) {
            int x = s[i].dmg, now = (1ll<<a)*s[i].hp-x;
            xx = max(xx, now-mt+d[mn]);
        }
    }
    cout << (xx+ans > res ? xx+ans : res);
    return 0;
}