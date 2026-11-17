//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
d[i] 表示每个位置，都先 *2（把"单位"翻倍，可能是为了处理"半单位"）。
三种字符对应三种资源：
W：产生资源1（写入 cnt[1]），每单位保底收益 2
G：可把资源1换成资源2（cnt[2] += w*2），并产生资源0
L：消耗资源，按优先级用三种库存补，收益递增
全程贪心：优先用"便宜的"库存补，累计 ans，最后输出 ans/2

d[i]	每段长度（输入后 ×2）
cnt[0]	第 0 类库存量（来源：G 段产生的）
cnt[1]	第 1 类库存量（来源：W 段产生的）
cnt[2]	第 2 类库存量（来源：G 段把1换成的）
tg	标志位，是否出现过 W 段
ans	累加收益
s	路段字符序列（下标1起）
每读一段，按字符类型处理。由于输入 d[i]*=2，处处的 d[i]/2 用来恢复"原始单位"
L 段 = 消耗区：需要消耗的能量，优先用代价最低的库存补（贪心），顺序 cnt[1] → cnt[2] → cnt[0]。

每次补 w 单位时，ans += w*2 + w*k：其中 2 是固定部分（可能代表"行走"），k（2 或 4）是各库存的"兑换成本"，w*2 因为 d 翻了倍所以补 w 需耗 2w。
补的顺序体现贪心：先花最少的（cnt[1] 成本2），再贵的。
如果三种库存都不够，且出现过 W（tg=1），则用"W 透支"手段（每单位 +4）一次性补齐。
最后 ans += 6*d[i]：完全"现金购买"的兜底成本
如果有 cnt[1] 库存，用它"换"——把资源1 变成资源2（cnt[1] -= w，cnt[2] += 2w），成本 2+2。
剩余的 G 长度按 *3 计入 ans，并让 cnt[0] += d[i]/2 积累第 0 类库存
置 tg=1（以后 L 段就能用"透支W"的手段）。
收益 +d*2，并积累 cnt[1] += d/2 资源1。
因为前面把所有 d 都 ×2，导致所有收益也都隐含 ×2，所以最后 ans/2 还原真实值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e7+5;

int n, d[N], cnt[3], ans, tg;
string s;
signed main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> d[i]; d[i] *= 2; }
    cin >> s; s = ' ' + s;
    rep(i,n) {
        int w;
        if (s[i] == 'L') {
            if (cnt[1]) {//第1轮：用 cnt[1]（来自 W，便宜）补
                w = min(d[i]/2, cnt[1]);
                ans += w*2 + w*2; d[i] -= w*2; cnt[1] -= w;
            }
            if (cnt[2]) {//第2轮：用 cnt[2]（来自 G 换的）补
                w = min(d[i]/2, cnt[2]);
                ans += w*2 + w*4; d[i] -= w*2; cnt[2] -= w;
            }
            if (cnt[0]) {//第3轮：用 cnt[0] 补
                w = min(d[i]/2, cnt[0]);
                ans += w*2 + w*4; d[i] -= w*2; cnt[0] -= w;
            }
            if (tg) { ans += 4*d[i]; d[i] = 0; }//若还有 W 出现过（tg=1），用"透支W"的手段补
            ans += 6*d[i];//剩余部分按 6/单位 硬扛（买）
        } else if (s[i] == 'G') {
            if (cnt[1]) {
                w = min(d[i]/2, cnt[1]);
                ans += w*2 + w*2; d[i] -= w*2; cnt[1] -= w; cnt[2] += w*2;
            }
            ans += d[i]*3; cnt[0] += d[i]/2;
        } else if (s[i] == 'W') {
            tg = 1; ans += d[i]*2; cnt[1] += d[i]/2;
        }
    }
    cout << ans/2;
    return 0;
}