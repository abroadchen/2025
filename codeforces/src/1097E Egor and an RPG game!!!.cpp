//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
type：0 表示当前要找递增链，1 表示要找递减链。
cnt：当前记录到的最长链长度。
mn[j]：贪心 LIS 中"长度为 j 的递增子序列，其最小末尾元素的下标"。
fr[i]：在构造的这条链里，下标 i 元素的前驱下标（用于最后回溯整条链）
cnt=0：重置计数。
a[0] = type ? inf : -inf：设定哨兵。type=0（递增）用 -inf 作为最小下界，这样第一个元素一定可比；type=1（递减）用 inf。
mn[1]=0：初始化，让"长度为1的子序列末尾"潜在地可以是下标 0（哨兵），方便 lower_bound 从位置 1 起工作。
rep(i,n)：遍历每个下标 i（1..n 对应 a[1..n]）。
lower_bound(mn+1, mn+1+cnt, i, lambda)：
在 mn[1..cnt] 这些下标里找第一个 "满足阈值关系" 的位置 pos。
lambda 把下标 x、y 转成比较值：type ? a[x] : -a[x]——也就是当要找递增时用 -a[x]（求最长下降的对称技巧），找递减时用 a[x]。这实质是用 LIS 算法处理"递减子序列"的通用写法。
mn[pos]=i：把长度为 pos 的最小末尾下标更新为 i（贪心替换）。
fr[i] = mn[pos-1]：记录长度为 pos-1 的末尾下标作为 i 的前驱 → 这样走 fr 链就能还原出一条子序列。
if (pos == cnt+1) cnt++：如果 i 能作为新的最长金字塔顶端，cnt 增一。
作用：get() 跑完，mn[cnt] 指向整条最长链的末尾元素，fr 链表可以还原出这条链全体。
tot++：答案链计数器 +1，把这条链作为一个新的组。
memset(v,0,...) + vec[tot].clear()：清空标记数组和该组容器。
int u = mn[cnt]：从最长链的末尾元素下标出发。
while(u){ v[u]=1; u=fr[u]; }：沿着 fr 前驱回溯，把所有属于这条链的下标标记为 v=1。
rep(i,n) if (v[i]) vec[tot].push_back(a[i])：把这条链上所有元素取出，存进第 tot 组。
vt.clear()：准备存放删除后剩下的元素。
rep(i,n) if (!v[i]) vt.push_back(a[i])：把不在链上的元素（v=0）放进去 → 这就是删掉这条链后的剩余序列。
n = vt.size()：更新剩余元素个数。
rep(i,n) a[i]=vt[i-1]：重排 a，使其覆盖剩余元素。
作用：把 get() 找到的一条链取出来固定为一组，然后把原序列缩成删掉这条链后的剩余部分，返回主循环继续下一次 get()。
st 是一个按第一关键字排序的 set<pair<int,int>>（值, 链编号）。
st.clear()：清空。
rep(i,lim) st.insert({0,++tot}), vec[tot].clear()：开 lim 条新链，每条链用 {0, tot} 初始化（末尾值设为 0，因为默认最小；tot 递增得到新链编号），并清空对应 vec。
rep(i,n)：对剩余每个元素值 a[i]：
auto now = *--st.lower_bound({a[i],0})：在 set 里找到最后一个末尾值 < a[i] 的那条链（lower_bound({a[i],0}) 返回第一个 ≥ a[i] 的迭代器，-- 得到它前面那个，即末尾 < a[i] 的最大者）。
st.erase(now)：把它从 set 暂移出（因为其末尾值要更新）。
vec[now.second].push_back(a[i])：把 a[i] 追加到这条链末尾（链内保持递增）。
st.insert({a[i], now.second})：把这条链以新末尾 a[i] 重新插回 set。
循环结束后，每条链就是一条单调递增链。
作用：这是贪心的"开心牌排序/最小链划分"：始终把当前元素放到"能放下且末尾值最大的那条链"上，使得链数尽量少且每条内部递增。lim 是可用链数上限
int T; cin>>T：题目多组测试数据。
tot=0：清空链总数。
cin>>n：序列长度。
k = 最小满足 k(k+1)/2 ≥ n 的整数：这里的 k*(k+1)/2 是三角数。这个 k 很关键——它决定了整个算法最终要划分成的链数目标（即"划分成 k 条链，使得某种代价不超过 k"）。它是这道题的核心定界：当把序列尽量分成 k 条链时，某组链数正好是 k。
type=0：先做递增链分解。
while(n)：循环直到序列被处理完（n 变为 0）：
get()：求一条当前最长链。
if (cnt < k && !type) { solve(cnt); break; }：如果当前的最长链长度已有趋势 cnt < 目标 k 且还在递增模式，则改用批量贪心分链解决剩余，结束循环。
init(), k--：否则取走这条链，k 减 1（目标剩余链数下降），继续下一轮。
cout<<tot：输出总链数。
输出每一条链的长度和内容
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5, inf = 0x3f3f3f3f;

int cnt, a[N], mn[N], n, fr[N];
bool type;
void get() {
    cnt = 0; a[0] = type ? inf : -inf; mn[1] = 0;
    rep(i,n) {
        int pos = lower_bound(mn+1,mn+1+cnt,i,[](int x, int y) {
            return (type?a[x]:-a[x]) < (type?a[y]:-a[y]);
        }) - mn;
        mn[pos] = i; fr[i] = mn[pos-1];
        if (pos == cnt+1) cnt++;
    }
}

int tot;
bool v[N];
vector<int> vec[N], vt;
void init() {
    tot++; memset(v,0,sizeof(v)); vec[tot].clear();
    int u = mn[cnt];
    while (u) { v[u] = 1; u = fr[u]; }
    rep(i,n) if (v[i]) vec[tot].push_back(a[i]);
    vt.clear();
    rep(i,n) if (!v[i]) vt.push_back(a[i]);
    n = vt.size();
    rep(i,n) a[i] = vt[i-1];
}

set<ii> st;
void solve(int lim) {
    st.clear();
    rep(i,lim) st.insert({0,++tot}), vec[tot].clear();
    rep(i,n) {
        auto now = *--st.lower_bound({a[i],0});
        st.erase(now);
        vec[now.second].push_back(a[i]);
        st.insert({a[i],now.second});
    }
}

int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        tot = 0; cin >> n;
        int k = 0;
        while (k*(k+1)/2 < n) k++;
        rep(i,n) cin >> a[i];
        type = 0;
        while (n) {
            get();
            if (cnt < k && !type) { solve(cnt); break; }
            init(), k--;
        }
        cout << tot << '\n';
        rep(i,tot) {
            cout << vec[i].size() << ' ';
            for (int &it : vec[i]) cout << it << ' ';
            cout << '\n';
        }
    }
    return 0;
}