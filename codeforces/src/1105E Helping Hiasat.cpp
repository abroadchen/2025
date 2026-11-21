//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
1<<20 ≈ 100万，DP 数组大小
操作数、顶点数(不同字符串数上限)、当前顶点计数、答案
b 每个顶点的"冲突邻居集合"bitmask
f g pre 前半/后半/合并用的 DP 数组
a1 a2 前半/后半的"可达(合法)状态"标记
读 n、m。逐条读操作：op=1 只读一个数；op=2 再读一个字符串，存到 qry[i]。（结构化绑定 auto &[op,s] 直接拿到 pair 的两个成员引用。）
while (j<=n && qry[j].first==2) j++; 把 j 推过这一段连续的 op==2。注意 j<=n 允许读到 qry[n]（越界读，读到默认的 first=0 就停，通常无害）。之后 j-- 回到段内最后一个串。
s：用 bitmask 表示"本组里有哪些串"。组里每个串：
第一次见到就通过 mp 分配新编号 tot++（编号就是它在 bitmask 里的位置）；
s |= 1ull<<编号 把该位标记为"本组成员"。
最后对组内每个串执行 b[编号] |= s：让它的冲突集合 = 整个组的成员。
i = j：跳到段尾，for 循环的 i++ 会继续下一段
异或掉自己的那一 bit。此时 b[i] = 顶点 i 的（真）冲突邻居集合，不含自己
f1 前半顶点数，f2 后半顶点数。a1[0]=1 表示空集状态是合法的起点。
这是标准的"状态机"式独立集 DP：状态 s 是一个合法独立集（内部无冲突）。
对每个状态，尝试加一个新顶点 i：仅当 s 和 i 的邻居集合 b[i] 没有交集（!(s&b[i])）时，才允许加入，形成新状态 s|(1<<i)，大小 f[s]+1。
a1[] 保证只有可达状态被扩展，避免浪费。
全程用 ll s 循环避免 1<<f1=1<<17 相关的位移溢出（前半 f1≤17 其实 int 也行，但统一成 ll 更稳）。
f[s] = 状态 s（作为独立集）的顶点数
后半的编号偏移到 f1+i。检测冲突：
(s<<f1) 把后半局部掩码 s 左移 f1 位，变成全局位域，再与 b[i+f1]（i 的全局冲突集）做 &，为空表示无冲突才加入
pre[s] = 在 s 的所有子集里，g 的最大值（SOS DP / 子集 DP）。
用途：合并时想快速问"后半能挑出不冲突且尽可能大的独立集是多少"
t：前半集合 s 里所有顶点的冲突邻居的并集 = 任何与前半冲突的顶点。
t ^= (1ull<<m)-1：全 m 位取反，得到"不与前半冲突"的顶点（含前半自己、含后半）。
t >>= f1：去掉前半位，只留下后半里可安全选择的顶点集合。
pre[t]：从这些可选后半顶点（及其子集）中取最大独立集大小。
答案 = 前半大小 + 后半最大 = f[s] + pre[t]。
合并能保证：前半内部已独立、后半内部由 pre 保证独立、两半之间由 t（已排除冲突）保证不冲突 → 整体合法。
输出最大独立集大小 = 最多能同时出现、又不冲突的字符串个数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<(n); i++)
#define ll long long
using namespace std;

template<class T, class U>
void chkmax(T &a, const U &b) { if (a < b) a = b; }

constexpr int N = 1<<20;
int n, m, tot, ans;
pair<int,string> qry[N];//存每条操作: {op, 字符串}
unordered_map<string,int> mp;//字符串 -> 顶点编号
ll b[40], f[N], g[N], pre[N];
bool a1[N], a2[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) {
        auto &[op, s] = qry[i];
        cin >> op;
        if (op == 2) cin >> s;
    }
    rep(i,n) if (qry[i].first == 2) {
        int j = i;
        while (j <= n && qry[j].first == 2) j++;
        j--;
        ll s = 0;
        for (int k = i; k <= j; k++) {
            if (!mp.contains(qry[k].second)) mp[qry[k].second] = tot++;
            s |= 1ull<<mp[qry[k].second];
        }
        for (int k = i; k <= j; k++) b[mp[qry[k].second]] |= s;
        i = j;
    }
    rep(i,m) b[i] ^= 1ull<<i;
    int f1 = m/2, f2 = m - f1; a1[0] = 1;
    for (ll s = 0; s < 1<<f1; s++) {
        if (!a1[s]) continue;
        chkmax(ans, f[s]);
        rep(i,f1) {
            if (s&(1<<i)) continue;
            if (!(s&b[i])) f[s|(1<<i)] = f[s]+1, a1[s|(1<<i)] = 1;
        }
    }
    a2[0] = 1;
    for (ll s = 0; s < 1<<f2; s++) {
        if (!a2[s]) continue;
        chkmax(ans, g[s]);
        rep(i,f2) {
            if (s&(1<<i)) continue;
            if (!((s<<f1)&b[i+f1])) g[s|(1<<i)] = g[s]+1, a2[s|(1<<i)] = 1;
        }
    }
    rep(s,1<<f2) {
        pre[s] = g[s];
        rep(i,f2) if (s&(1<<i)) chkmax(pre[s], pre[s^(1<<i)]);
    }
    for (ll s = 0; s < 1<<f1; s++) {
        ll t = 0;
        rep(i,f1) if (s&(1<<i)) t |= b[i];
        t ^= (1ull<<m)-1; t >>= f1;
        chkmax(ans, f[s]+pre[t]);
    }
    cout << ans << '\n';
    return 0;
}