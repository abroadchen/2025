//
// Created by Psy.C on 2026/10/7.
//
/**
n、a、d 是参数，m 是事件个数，t[i] 是事件发生的时间点
在末尾追加 n*a（一个"终点事件"），然后通过相邻交换做冒泡排序，使 t[1..m] 递增
now：当前最后一次触发覆盖到的时间；
ans：触发总次数（答案）；
cur：下一个还"没被覆盖"的格点编号，满足 cur*a 是下一个待覆盖的格点时刻（因为 a 是间距，所以时间都用 某格点编号 × a 表示）
前提判断 cur <= n && cur*a < t[i]：只有当"待覆盖的指针还没超过总格点数 n"、且"指针时刻还没到这个事件"时，才可能用批量覆盖来快速扫过中间的连续格点。

now = cur*a：从指针所在格点开始触发。
r = d/a+1：一次触发能向前覆盖几个格点。因为每次触发覆盖区间长度 d，格点间距 a，所以完整覆盖 d/a 个完整间隔，再加起点本身，共 d/a+1 个格点。
tot = (t[i]-now)/a+1：从 now 到这个事件之间一共有多少个待覆盖格点。
q = tot/r：能用完整批量触发恰好覆盖多少整段；ans += q 累加次数，然后把 now 推到 q 次触发后的位置，cur 同步前移，剩余 tot 若还有零头就再来一次触发。
若 tot 还有剩余（tot>0），多触发一次，更新指针。
if (now >= t[i]) continue：批量推进已经把这个事件盖住了，跳过不处理。

否则：该事件还没被覆盖，就专门为它触发一次：now=t[i]+d（覆盖该点及往后 d），cur=now/a+1 更新指针，ans++。

循环结束后输出总触发次数 ans。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10;
ll n, m, a, d, t[N];
int main() {
    fast;
    cin >> n >> m >> a >> d;
    for (int i = 1; i <= m; ++i) cin >> t[i];
    ll now = 0, ans = 0, cur = 1;
    t[++m] = n*a;
    for (ll i = m; i >= 2; --i)
        if (t[i] < t[i-1]) swap(t[i], t[i-1]);
    for (int i = 1; i <= m; ++i) {
        if (cur <= n && cur*a < t[i]) {
            now = cur*a;//从当前指针处开始批量触发
            //一次触发能覆盖的格点数 到本事件需要覆盖的格点数 完整批量触发的次数
            ll r = d/a+1, tot = (t[i]-now)/a+1, q = tot/r;
            if (q) {
                ans += q;
                now += (q-1)*r*a+d;//推进 q 次后的最终时间
                tot -= q*r;//剩余未覆盖格点
                cur = now/a+1;//更新指针
            }
            if (tot) {//还有零头 → 再触发一次
                ++ans;
                now = cur*a+d;
                cur = now/a+1;
            }
        }
        if (now >= t[i]) continue;//该事件已被覆盖，跳过
        now = t[i]+d;//单独为它触发一次
        cur = now/a+1;
        ++ans;
    }
    cout << ans << '\n';
    return 0;
}