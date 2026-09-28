//
// Created by Psy.C on 2026/9/28.
//
/**
ok(x, y, ...) 返回 true 表示「候选人 x 排在候选人 y 前面」。

tc[] 是当前票数数组（temporary count），tl[] 是当前最后一次投票时刻数组（temporary last）。
排序规则：票数多者排前面；票数相同时，最后一次投票时刻早者排前面（先达标者优先，这是题目的 tie-break 规则）。
参数带 const 表示只读、不改动传入的数组
n（人数）、k（当选名额）设为全局变量，in 函数里可以直接用。
第一行：如果候选人 idx 得票为 0，直接返回 false（0 票的人不可能进入委员会/当选）。
然后遍历所有人，统计有多少人排在 idx 前面（ok(j, idx, ...) 为真），计数到 f。
若排在前面的人数 f < k，说明 idx 排进了前 k，返回 true；否则 false。
注意：这里 in 判断依据的是传入的临时数组 tc/tl，而不是全局的 cnt/lst，这样才能模拟"某分配方案下"的最终排名

m：总票数（全程要投出的票）；a：目前已投出的票数。
cnt[i]：候选人 i 当前的得票数；lst[i]：候选人 i 最后一次收到票的时刻。
初始化：所有人 0 票；lst 设为 INT_MAX（表示"从未投过票"——因为 tie-break 是越早越好，所以没票的人放在最后）
读入这 a 张票：第 t 张投给了 g（输入是 1 基，g-- 转成 0 基下标）。
给该候选票数 +1，并把 lst 更新为当前时刻 t
r = 总票数 − 已投票数 = 还剩多少张票没投，将在后续模拟中自由分配
复制一份当前票况到 tc/tl（临时数组），后面在副本上模拟，不影响全局。
rem = 剩余票数 r，在下面贪心分配。
思路：判定"必定当选"要看最坏情况——即我（候选人 c）一张剩余票都不拿，剩余 r 张票全部被用来"制造新对手"，尽量让更多候选人排到我前面。若这种最坏情况下我仍在前 k，则我必定当选
while (rem > 0)：只要还有剩余票就继续制造威胁。
bj = 本次选中要"扶持"的候选择对象（best job），bn = 让其反超 c 所需的最少票数。INT8_MAX 只是一个大数（用 8 位 max 当作无穷大，够用即可，因为票数最多 100）。
遍历每个 j：
跳过 j == c（不能扶持 c 自己）。
ok(j, c, tc, tl) 为真说明 j 已经排在 c 前面了，无需扶持，continue 跳过。
否则 j 目前排在 c 后面，尝试给它加票让它反超：
nd = 需要多少票，done 标记是否已找到。
内层 for (x = 1; x <= rem && !done; x++)：从小到大试加 x 张票。
试加时把 tc[j] += x; tl[j] = m（假想剩余票都在最后时刻 m 投出——最不利于 c 的 tie-break），然后检验 ok(j, c, ...) 是否让 j 反超 c。
反超成功就用 nd = x 记录并 done = true 退出内层；无论如何要还原 tc[j] = oc; tl[j] = ol（因为只是试探）。
如果这个 j 所需的票数 nd 比当前记录的 bn 更少，就更新 bj = j, bn = nd（贪心：每次找性价比最高、即最少票就能新增一个对手的候选）。
内层全部遍历完：
如果 bj == -1：说明没有任何候选能在剩余票数内反超 c（都抬不动了），无法再制造威胁，break 终止。
否则正式把 bn 张票给 bj，tc[bj] += bn; tl[bj] = m，并从 rem 里扣掉 bn。
循环结束后，tc/tl 代表"最坏情形"下的最终票况——c 没拿票，且对手被尽量抬起来了。
cnt[c] > 0：c 至少要有票（0 票不可能当选）。
in(c, tc, tl)：在最坏情形下 c 是否仍在前 k。若在，gd = true，即必定当选 → ans = 1。
has 初始为 false，下面用来判"是否有希望（2）"
复制当前票况到 bc/bl。
方案 A（最有利于 c）‍：把全部剩余 r 张票都给 c 自己，并把 c 的最后时刻设为 m——此时 c 得票最大化。
in(c, bc, bl)：若这样 c 能进前 k，说明 c 有希望（ans = 2）‍，has = true
如果方案 A 都不行，再试方案 B：给 c 0 张票（保留 c 原有的较早 / 正常 lst），把剩余 r 张票全给"当前名次最靠后的那个候选"t。
t 的选择：遍历所有 j != c，用 ok(t, j, ...) 保持 t 一直是最靠后的那一个（ok(t,j) 为真表示 t 排在 j 前、j 更靠后，就把 t 换成 j）。
把 r 票全砸给 t（最弱的人），这样不会新增能反超 c 的强对手，是"对 c 尽可能无害"的分配。
再 in(c, bc, bl) 判断，若 c 进前 k，has = true。
方案 A 和 B 覆盖了"c 拿不拿票"两种对 c 最有利的极端，取其一可行即视为"有希望"。
为什么方案 A 用"全给 c"而方案 B 用"给 0 票 + 票给最弱者"？因为 c 拿满票通常排名最高；但若 c 和某人同票，需要靠较早的 last 才能赢，此时多拿票把 last 推到 m 反而让 c 变不利，所以也要考虑"c 不拿票保留早 last"的方案 B。两个都试，谁能让 c 进前 k 都算"有希望"。
gd（必定当选）→ 1；否则 has（有希望）→ 2；否则 → 3。
输出时用空格分隔各候选人答案，最后一个（c+1 == n）换行。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;

bool ok(int x, int y, const int tc[], const int tl[]) {
    if (tc[x] != tc[y]) return tc[x] > tc[y];
    return tl[x] < tl[y];
}

int n, k;
bool in(int idx, int tc[], int tl[]) {
    if (tc[idx] == 0) return false;
    int f = 0;
    for (int j = 0; j < n; j++)
        if (j != idx && ok(j, idx, tc, tl)) f++;
    return f < k;
}

int m, a, cnt[N], lst[N];
int main() {
    fast;
    cin >> n >> k >> m >> a;
    for (int i = 0; i < n; i++) {
        cnt[i] = 0; lst[i] = INT_MAX;
    }
    for (int t = 1; t <= a; t++) {
        int g; cin >> g; g--;
        cnt[g]++; lst[g] = t;
    }
    int r = m - a;
    for (int c = 0; c < n; c++) {
        int tc[N], tl[N];
        for (int j = 0; j < n; j++) { tc[j] = cnt[j]; tl[j] = lst[j]; }
        int rem = r;
        while (rem > 0) {
            int bj = -1, bn = INT8_MAX;
            for (int j = 0; j < n; j++) {
                if (j == c || ok(j, c, tc, tl)) continue;
                int nd = INT8_MAX, done = false;
                for (int x = 1; x <= rem && !done; x++) {
                    int oc = tc[j], ol = tl[j];
                    tc[j] += x; tl[j] = m;
                    if (ok(j, c, tc, tl)) { nd = x; done = true; }
                    tc[j] = oc; tl[j] = ol;
                }
                if (nd < bn) { bn = nd; bj = j; }
            }
            if (bj == -1) break;
            tc[bj] += bn; tl[bj] = m;
            rem -= bn;
        }
        bool gd = cnt[c] > 0 && in(c, tc, tl), has = false;
        int bc[N], bl[N];
        for (int j = 0; j < n; j++) { bc[j] = cnt[j]; bl[j] = lst[j]; }
        bc[c] += r; bl[c] = m;
        if (in(c, bc, bl)) has = true;
        if (!has) {
            for (int j = 0; j < n; j++) { bc[j] = cnt[j]; bl[j] = lst[j]; }
            int t = -1;
            for (int j = 0; j < n; j++) {
                if (j == c) continue;
                if (t == -1 || ok(t, j, bc, bl)) t = j;
            }
            if (t >= 0) { bc[t] += r; bl[t] = m; }
            if (in(c, bc, bl)) has = true;
        }
        int ans;
        if (gd) ans = 1;
        else if (has) ans = 2;
        else ans = 3;
        cout << ans << (c+1 == n ? '\n' : ' ');
    }
    return 0;
}