//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
M = 3e5：把点分成两类，x 一侧、y 一侧，各最多 M 个。
N = 6e5+10：总点数上限（x+y 两侧共 6e5 个），并多留 10 余量。
本质上这是一个二分图：左部点编号 1-M，右部点编号 M+1-2M
vector<ii> T[N<<2]	线段树的存储：每节点存在此节点时间区间内"全程有效"的边
ins(i, l, r, L, R, t)	把边 t ≤存在于时间区间 [l,r]≥ 插入线段树；[L,R] 是当前节点管辖的时间范围
if (l==L && R==r)	若要插入的区间正好覆盖整个节点管辖区间，则直接存进该节点并返回
mid = (L+R)>>1	计算中点
mid >= r	目标区间完全落在左半 → 下放左子节点
mid < l	目标区间完全落在右半 → 下放右子节点
else 分支	目标区间横跨中点 → 拆成两半，分别下放左右子节点
⚠️ 注意：这里 find 没有路径压缩！这是可撤销并查集的关键——因为要能回溯合并，不能用会改变树结构的路径压缩，只能用"不压缩"的递归找根
sz[i]	连通块大小（用于按秩/按大小合并）
cx[i]	该连通块内 x 侧节点数
cy[i]	该连通块内 y 侧节点数
res	全局答案 = Σ（每个连通块 cx*cy）
merge(x,y,st)	把 x、y 所在的连通块合并；st 记录合并操作以便撤销
x=find(x); y=find(y)	找两者所在集合根
if (x!=y)	原本不相连才操作
if (sz[x]<sz[y]) swap	按大小合并：让较大的当根，控制树高度
st.emplace(x,y)	记录本次合并的 (大根x, 被合并的y)
res -= cx[x]*cy[x] 等	先把两个集合的贡献从 res 里减掉
sz[x]+=sz[y]; f[y]=x	合并父指针和大小
cx[x]+=cx[y]; cy[x]+=cy[y]	合并两侧计数
res += cx[x]*cy[x]	再把合并后的新集合贡献加回 res
while(!st.empty())	从这个栈里逐个撤销之前做的合并
x, y	还原 (父, 子)，即反向操作 merge 里的 (x,y)
res -= cx[x]*cy[x]	先把合并后的集合贡献减掉
f[y]=y	还原父指针
sz[x]-=sz[y]; cx[x]-=cx[y]; cy[x]-=cy[y]	把 y 的计数从 x 里减回来
res += cx[x]*cy[x] + cx[y]*cy[y]	恢复回两个独立集合的贡献
ans[N]	保存每个时刻的答案
dfs(i,l,r)	深度优先遍历线段树节点 i，该节点管辖时间 [l,r]
stack<ii> st	本节点局部合并栈（用于回溯）
for(...: T[i]) merge(...)	把此节点覆盖到全程的边全部合并
if (l==r) ans[l]=res	到达叶子（即某一时刻）→ 记录当前 res
else 递归左右孩子	中间节点：往下层继续处理更细时间段
del(st)	离开节点时撤销本节点加的所有边，恢复状态
map<ii,int> mp	记录"当前还处于活跃/未闭合的边"，键=边(x,y+M)，值=它第一次出现的时刻
tmp={x,y+M}	把右部点 y 编号偏移到 M 之后，构造边
if (!mp[tmp])	若是第一次遇到此边（还没被匹配）→ 记录其开始时刻 i
else 分支	再次遇到同一条边 → 说明该边存在区间是 [mp[tmp], i-1]，插入线段树，并从活跃表删除
for(mp) 段	最后仍在活跃表中的边：从未闭合，存在区间延伸到末尾 [snd, n]，补插
第一个 for（i=1..M）	左部点初始化：自成一个集合，cx=1, cy=0, sz=1
第二个 for（i=M+1..N-10）	右部点初始化：自成一个集合，cy=1, cx=0, sz=1
dfs(1,1,n)	从根节点（时间 1..n）做分治遍历，填充 ans
输出循环	依次输出每个时刻的答案，" \n"[i==n] 控制空格/换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
#define ll long long
using namespace std;

constexpr int N = 6e5+10, M = 3e5;

vector<ii> T[N<<2];
void ins(int i, int l, int r, int L, int R, ii t) {
    if (l == L && R == r) { T[i].push_back(t); return; }
    int mid = (L+R)>>1;
    if (mid >= r) ins(i<<1,l,r,L,mid,t);
    else if (mid < l) ins(i<<1|1,l,r,mid+1,R,t);
    else {
        ins(i<<1,l,mid,L,mid,t);
        ins(i<<1|1,mid+1,r,mid+1,R,t);
    }
}
int f[N];
inline int find(int x) { return x == f[x] ? x : find(f[x]); }

int sz[N], cx[N], cy[N];
ll res;
inline void merge(int x, int y, stack<ii> &st) {
    x = find(x); y = find(y);
    if (x != y) {
        if (sz[x] < sz[y]) swap(x,y);
        st.emplace(x,y);
        res -= (ll)cx[x]*cy[x]; res -= (ll)cx[y]*cy[y];
        sz[x] += sz[y]; f[y] = x;
        cx[x] += cx[y]; cy[x] += cy[y];
        res += (ll)cx[x]*cy[x];
    }
}
inline void del(stack<ii> &st) {
    while (!st.empty()) {
        int x = st.top().first, y = st.top().second;
        res -= (ll)cx[x]*cy[x];
        f[y] = y; st.pop();
        sz[x] -= sz[y]; cx[x] -= cx[y]; cy[x] -= cy[y];
        res += (ll)cx[x]*cy[x]; res += (ll)cx[y]*cy[y];
    }
}

ll ans[N];
void dfs(int i, int l, int r) {
    stack<ii> st;
    for (auto &[fst, snd] : T[i]) merge(fst,snd,st);
    if (l == r) ans[l] = res;
    else {
        int mid = (l+r)>>1;
        dfs(i<<1,l,mid); dfs(i<<1|1,mid+1,r);
    }
    del(st);
}

int n;
map<ii,int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        ii tmp = {x,y+M};
        if (!mp[tmp]) mp[tmp] = i;
        else {
            ins(1,mp[tmp],i-1,1,n,tmp);
            mp.erase(tmp);
        }
    }
    for (auto [fst, snd] : mp) ins(1,snd,n,1,n,fst);
    for (int i = 1; i <= M; i++) f[i] = i, cx[i] = sz[i] = 1;
    for (int i = M+1; i <= N-10; i++) f[i] = i, cy[i] = sz[i] = 1;
    dfs(1,1,n);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i==n];
    return 0;
}