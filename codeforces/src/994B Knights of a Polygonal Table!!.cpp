//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
node：一项记录，含能力 pw、原始下标 id、成本 c。
cmp：按 pw 升序排序
n, m：人数 / "取前 m 个"参数。
lim：临时计数，控制取几个。
q：大根堆（默认 priority_queue 就是大根堆，堆顶最大）。
t[]：临时缓冲，存"从堆里弹出来的值"，用于之后放回。
ans[]：每个人最终累加的答案
读入每个人的 pw 并记录原始 id。
读入每个人的成本 c。
按 pw 升序排序。
注意：排序后 k[i].id 记录了原始位置，ans[k[i].id] 用来把结果放回原始顺序输出
处理第 i 个人时，把已处理过（能力更弱）的前一个 k[i-1].c 加入大根堆。
这样堆里始终放着"曾经处理过的、比他能力弱的所有人的成本"。
只要堆不空且还没取满 m 个，就把当前堆顶（最大的成本）‍弹出来：
记录到 t[lim]（待会儿放回）；
累加到当前人的 ans。
循环结束条件：堆空 或 已取满 m 个。
这一段的意图：把"能力弱于当前人的、成本最大的至多 m 个"加给当前人
把自己的成本也累加进答案
把刚才从堆里弹出去、暂存在 t[] 里的值全部原样推回堆。
作用：保证堆里始终保持"到当前 i 为止所有已出现过的成本"，不影响后续处理。
重要细节：这里放回后，堆的内容和弹之前一样（不消耗）。也就是说 ans 累加时"用的"这些成本并没有真正被移除，下一次外层循环还会基于同样的堆再加。
所以这个循环实际上反复利用同一批"前面人的成本"，给每个人累加"他之前所有人的前 m 大成本 + 自己成本"
按原始输入顺序（通过 k[id] 索引）输出每个 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

struct node {
    int pw, id;
    ll c;
} k[N];
inline bool cmp(node k1, node k2) { return k1.pw < k2.pw; }

int n, m, i, lim;
priority_queue<ll> q;
ll t[N], ans[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) { cin >> k[i].pw; k[i].id = i; }
    rep(i,n) cin >> k[i].c;
    sort(k+1, k+1+n, cmp);
    rep(i,n) {
        if (i > 1) q.push(k[i-1].c);
        while (!q.empty() && lim < m) {
            lim++;
            t[lim] = q.top();
            ans[k[i].id] += q.top(); q.pop();
        }
        ans[k[i].id] += k[i].c;
        while (lim) { q.push(t[lim]); lim--; }
    }
    rep(i,n) cout << ans[i] << ' ';
    return 0;
}