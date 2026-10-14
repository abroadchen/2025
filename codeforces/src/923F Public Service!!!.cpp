//
// Created by Psy.C on 2026/10/14.
//
/**
set<ii> e[2];        // 两图的边集合（去重）
int deg[2][N+5];     // 每个节点度数
int fa[2][N+5];      // 父（上一层）指针
deque<int> ch[2][N+5]; // 节点在"缩链"过程中的子队列
vector<int> adj[2][N+5]; // 邻接表
int rf[N+5];         // 图0节点 i -> 图1节点的映射 rf[i]
set<ii> md[2];       // (度数, 节点) 的集合，用于快速取最大度数点
bool rsv[N+5];       // 图1节点是否已被占用
set<int> lb[2];      // "叶子候选"集合

rf[i]：核心映射数组——图 0 的节点 i 对应图 1 的哪个节点。
rsv[j]：图 1 的节点 j 是否已被使用（前向占用）。
e[t]：用 (min,max) 有序对存边，exist(t,u,v) 快速查边
把边标准化为 (小,大) 后查 set<ii>，O(log n) 判断两点是否相连。u ^= v ^= u ^= v 是经典的异或交换
DFS 建树（以 1 为根），把叶子节点（度数==1）‍按父节点挂到 ch[t][parent] 队列里。
这一步为后续"每次处理一个叶子对"的反复删边做准备。
ch 用 deque：既有 push_back 添加叶子，后续又有 push_front（更新时把新叶子插到队首）、pop_back 删除
判断：图 0 的节点 u 与它所有已映射邻居 v，它们的映射 rf[v] 在图 1 里必须也相邻（exist(1, rf[u], rf[v])）。
若存在某个邻居映射后不相邻，则 check 返回 false → 该映射不合法。
这是同构约束的核心检查：边必须在两图中同时保留
res 表示当前尚未映射的节点数。整体是一个回溯搜索，分几种情况：

（a）小规模暴力（res ≤ 5）
剩余节点少时，直接暴力枚举所有映射排列并逐点 check，这也是最终返回 "Yes" 前的兜底
（b）两树度都 < res-2（都非"星形"）
当两图都不是"近似星形"时，每次剥掉两组叶子（图0两个、图1两个），递归减小规模 res-2。
剥叶子后判断映射是否合法，若不合法则交换配对再试。
（c,d）某一侧接近"星形"（度为 res-2）
当一侧最大度点已经是 res-2（即它几乎连接所有剩余节点，是星形中心），进入确定性构造分支：不再搜索，而是贪心/直接指定某个节点作为中心，然后其余未映射节点按 rsv/rf 顺序填补剩余映射。
这三个分支对应一个常见的同构算法思想——反复减少"分枝数"最多的叶-链结构，把问题规模逐步缩小到能暴力求解的小情况

当某个叶子被删掉时，更新度数集合 md、叶子候选 lb、子队列 ch 以及父指针。
若某节点因此变成叶子（度==1），则把它挂到其唯一邻居下，并更新"叶子代表"
读入用 u -= t*n,v -= t*n 把两个图的节点编号统一到 1..n（图1原始编号为 n+1..2n）。
输出时 rf[i]+n 还原为图1真实编号。
预剪枝：若某树存在度==n-1（星形中心，其它点都连它）则直接判 "No"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define ii pair<int,int>
using namespace std;

constexpr int N = 1e4;

set<ii> e[2];
inline bool exist(const int t, int u, int v) {
    if (u > v) u ^= v ^= u ^= v;
    return e[t].contains({u, v});
}

int deg[2][N+5], fa[2][N+5];
deque<int> ch[2][N+5];
vector<int> adj[2][N+5];
inline void init(const int t, const int u, const int lst) {
    if (lst && deg[t][u] == 1) ch[t][fa[t][u]=lst].push_back(u);
    for (int v : adj[t][u]) if (v != lst) {
        if (!lst && deg[t][u] == 1) ch[t][fa[t][u]=v].push_back(u);
        init(t, v, u);
    }
}

int rf[N+5];
inline bool check(const int u) {
    return ranges::all_of(adj[0][u], [&](int v) {
        return !(rf[v] > 0 && exist(1, rf[u], rf[v]));
    });
}

set<ii> md[2];
int n;
bool rsv[N+5];
set<int> lb[2];
inline void solve(const int res) {
    int rt = md[0].rbegin()->second, rt1 = md[1].rbegin()->second;
    if (res <= 5) {
        int p[6]{}, q[6]{};
        rep(i,1,n) {
            if (!rf[i]) p[++p[0]] = i;//未映射的图0节点
            if (!rsv[i]) rsv[q[++q[0]]=i] = true;//占用的图1节点
        }
        do {//枚举图1节点的一个排列，尝试映射
            bool flg = true;
            rep(i,1,p[0]) rf[p[i]] = 0;
            rep(i,1,p[0]) {
                rf[p[i]] = q[i];
                if (!((flg=check(p[i])))) break;
            }
            if (flg) return;//找到可行解
        } while (next_permutation(q+1, q+q[0]+1));
        assert(false);//若到这里说明无解
    }
    if (deg[0][rt] < res-2 && deg[1][rt1] < res-2) {
        assert(lb[0].size() >= 2 && lb[1].size() >= 2);
        //取各自"最大度点"的两个叶子 u0,v0 / u1,v1
        int u0(*lb[0].begin()), v0(*++lb[0].begin());
        int u1(*lb[1].begin()), v1(*++lb[1].begin());
        if (deg[0][rt] == res-3 && fa[0][u0] != rt)
            v0 = ch[0][rt].back();
        if (deg[1][rt1] == res-3 && fa[1][u1] != rt1)
            v1 = ch[1][rt1].back();
        auto update = [](const int t, const int u) -> void {
            assert(u);
            lb[t].erase(ch[t][u].back());//删除当前"叶子代表"
            md[t].erase({deg[t][ch[t][u].back()]--, ch[t][u].back()});//度数-1
            md[t].erase({deg[t][u]--, u});
            md[t].insert({deg[t][u], u});
            ch[t][u].pop_back();
            if (!ch[t][u].empty()) lb[t].insert(ch[t][u].back());
            if (deg[t][u] == 1) {//若 u 变为叶子
                for (int v : adj[t][u]) if (deg[t][v]) { fa[t][u] = v; break; }
                assert(fa[t][u]);
                ch[t][fa[t][u]].push_front(u);
                if (ch[t][fa[t][u]].size() == 1) lb[t].insert(u);
            }
        };
        update(0, fa[0][u0]), update(0, fa[0][v0]);
        update(1, fa[1][u1]), update(1, fa[1][v1]);
        rf[u0] = rf[v0] = -1, rsv[u1] = rsv[v1] = true;
        solve(res-2);//递归：删掉这两组叶子
        rf[u0] = u1, rf[v0] = v1;//尝试匹配
        if (!check(u0) || !check(v0)) rf[u0] = v1, rf[v0] = u1;//交换再试
    } else if (deg[0][rt] == res-2) {
        int x = *lb[0].begin(), y = *lb[1].begin();
        if (fa[0][x] == rt) x = *lb[0].rbegin();
        rsv[rf[rt]=y] = rsv[rf[x]=fa[1][y]] = true;
        int s = fa[0][x];
        rep(i,1,n) if (!rsv[i]) {
            rsv[rf[s]=i] = true;
            if (check(s)) break;
            rf[s] = rsv[i] = false;
        }
        assert(rf[s]);
        for (int i = 1, j = 1; i <= n; ++i) if (!rf[i]) {
            while (rsv[j]) ++j;
            rsv[rf[i]=j++] = true;
        }
    } else {
        int x = *lb[1].begin(), y = *lb[0].begin();
        if (fa[1][x] == rt1) x = *lb[1].rbegin();
        rsv[rf[y]=rt1] = rsv[rf[fa[0][y]]=x] = true;
        int s = fa[1][x];
        rep(i,1,n) if (!rf[i]) {
            rsv[rf[i]=s] = true;
            if (check(i)) break;
            rf[i] = rsv[s] = false;
        }
        assert(rsv[s]);
        for (int i = 1, j = 1; i <= n; ++i) if (!rsv[i]) {
            while (rf[j]) ++j;
            rsv[rf[j++]=i] = true;
        }
    }
}



int main() {
    fast;
    cin >> n;
    //读入两棵树的边：图0节点编号1..n，图1节点编号 n+1..2n（t=1 减掉 t*n 归一化）
    rep(t,0,1) rep(i,2,n) {
        int u, v; cin >> u >> v;
        if (u > v) u ^= v ^= u ^= v;
        u -= t*n, v -= t*n, ++deg[t][u], ++deg[t][v];
        e[t].insert({u, v});
        adj[t][u].push_back(v), adj[t][v].push_back(u);
    }
    rep(i,1,n) {
        md[0].insert({deg[0][i], i});
        md[1].insert({deg[1][i], i});
        if (deg[0][i] == n-1 || deg[1][i] == n-1)//任一节点度==n-1（孤立星中心）→ No
            return cout << "No\n", 0;
    }
    init(0, 1, 0), init(1, 1, 0);//初始化 md、lb
    rep(t,0,1) rep(i,1,n) {//初始化 lb（每棵树的"叶子代表"）
        if (!ch[t][i].empty()) lb[t].insert(ch[t][i].back());
    }
    //全量递归
    solve(n); cout << "Yes\n";
    rep(i,1,n) cout << rf[i]+n << (i<n?' ':'\n');
    return 0;
}