//
// Created by Psy.C on 2026/10/4.
//
/**
先判断是否有"无法跨越"的间隔，若某段最大间距大于油箱容量 b，直接不可能：

普通内部路段，加油站把每段 a 分成两段：f 和 a-f。跨越一个加油站补满油后要再走到下一个加油站，连续两段间距的最大值可能是 2*f 或 2*(a-f)（往返时方向相反，间距更大）。若任一大于 b 则 -1。
k==1：只走一段，只需保证 f ≤ b 且 a-f ≤ b。
k==2：特殊处理第一段只需单程 f，后续段需要 2*(a-f)。
k>2：需要中间段能连续扛住 2f 或 2(a-f)
把整段折叠考虑。由于路线是折返（0 → a → 2a → ... 往返），把加油站按"实际到达的绝对坐标"排出来。

对每"对"折返路段（长度为 2a 的闭合往返），有两个加油站：去程段内的 cur+f 和回程段内的 cur+2a-f。
k 为奇数时，末尾还剩一个孤立的到 cur+a 的去程段，其加油站在 cur+f。
这样 dis[1..cnt] 是按到达顺序排列的所有加油站绝对坐标
cur 最终应为 k*a（总终点）。dis[cnt+1] 放一个大数作为循环终止的边界
维护当前能到达的最远位置 now（起点为满油 b）。扫描排好序的加油站，当"当前够得着加油站 i（dis[i] ≤ now）但够不着下一个加油站 i+1（dis[i+1] > now）"时，就必须在加油站 i 加油，加满后 now = dis[i] + b 更新为新的最远可到位置，计数 +1。直到 now 足够到达终点（now >= cur）。

这是典型的"每次在能到达的最后一个加油站加油"的最优贪心，保证加油次数最少
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
constexpr ll inf = 1e10;

ll cur, dis[N], cnt;
int main() {
    fast;
    ll a, b, f, k; cin >> a >> b >> f >> k;
    if (k > 2) {
        if (b < 2*f || b < 2*(a-f)) { cout << "-1\n"; return 0; }
    } else if (k == 2) {
        if (b < f || b < 2*(a-f)) { cout << "-1\n"; return 0; }
    } else {
        if (b < f || b < a - f) { cout << "-1\n"; return 0; }
    }
    if (k&1) {
        int len = k/2; cur = 0;
        for (int i = 1; i <= len; ++i) {
            dis[++cnt] = cur + f; dis[++cnt] = cur + 2*a - f;
            cur += 2*a;
        }
        dis[++cnt] = cur + f;
        cur += a;
    } else {
        int len = k/2; cur = 0;
        for (int i = 1; i <= len; ++i) {
            dis[++cnt] = cur + f; dis[++cnt] = cur + 2*a - f;
            cur += 2*a;
        }
    }
    dis[cnt+1] = 2*a + inf;
    ll now = b, tot = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (now >= cur) break;
        if (dis[i] <= now && dis[i+1] > now) {
            now = dis[i] + b;
            tot++;
        }
    }
    cout << tot << '\n';
    return 0;
}