//
// Created by Psy.C on 2026/10/14.
//
/**
把两个长度为 5 的数组 a[]、b[] 编码成一个唯一的 ull 哈希。
逐元素 ans += rt * a[i]，每次 rt *= inf（inf=23333333333）当作不同位的"权重/基数"，相当于五进制/混合进制编码，避免碰撞。
前 5 位编码 a，后 5 位编码 b
f[i]：状态 i 的博弈结论（-1 未定，0 必败，1 必胜）。
d[i]：状态 i 在反向游戏图中的"出度倒数"（用于拓扑推理）。
g[i]：反向边，g[t].push_back(x) 表示从状态 x 可一步到状态 t（建边方向与转移方向相反）
枚举所有可能的两数组状态 a[0]、a[1]（每个是和为 8 的 5 元素拆分，dfs 用"组合拆分"生成所有和等于 8 的分法），把每种组合通过 get 注册进表中。
这说明游戏里两个玩家的计数数组各为 5 个桶、总和为 8（类似"取物分类"的棋盘/石子博弈）
复制数组到结构体 c[l]，初始化 f[l] = -1（未定），并把哈希映射到编号 l
判断终止态：
若 a[0]==8（先手把全部 8 个都放进第 0 桶，达成目标）且 b[0]<8，先手胜 f[x]=1；
反之 b[0]==8 且 a[0]<8，先手必败 f[x]=0。
都入队 q 作为 BFS 起点。
枚举一步转移：挑 a 的第 i 个桶、b 的第 j 个桶都有存量，把 a 的一个从 i 移到 (i+j)%5（模拟合并/移动的分堆操作），得到新状态 b→a（注意交换次序 ha(b,a)，说明轮到另一方），查找编号 t，建反向边 g[t].push_back(x)，并 d[x]++（记录进入转移的数量）
标准的反向拓扑博弈推理：

从已知胜/败的终止态出发，沿反向边向上推。
若当前节点 x 是必败态（f[x]==0），则它的所有"前驱"（能走到它的状态）都是必胜态，f[v]=1 并入队。
若当前节点 x 是必胜态，则它不能直接判定前驱；只有当某前驱 v 的所有后继都已判为必胜（d[v] 减到 0）时，v 才是必败态。
最终 f 仍为 -1 的节点表示该状态无法被判定（可能平局/和局或未遍历到）
dfs 生成全部状态，build 建图并标记终止态，solve 反推胜负。
读入 T 组查询，每组先给 flg（当前轮到谁/当前玩家标记），再读 8 个数，用桶计数填进 a[0]/a[1]。
查表 mp[ha(...)] 得到状态编号，取 f[t]。
输出：-1 输出 Deal（平局）；否则比较 flg 与 t，相等 Bob 胜，不等 Alice 胜


正在填充第几个数组（0 或 1，对应 a[0] 和 a[1]）
y	当前数组里正在填第几个桶（0-4，共 5 个桶）
z	当前桶之前剩余还能分配的总数（初始为 8）
分支一：if (x == 2) —— 两个数组都填完了
当 x 计数到 2，说明 a[0] 和 a[1] 两个数组都已填充完毕。
此时把这一组完整方案 (a[0], a[1]) 交给 get() 注册进状态表（哈希 + 编号 + 存结构体）。
return 结束这条递归链
分支二：if (y == 4) —— 当前数组填到最后一个桶
如果当前数组已经填到第 4 个桶（最后一个），剩余总数 z 必须全部放进这个桶（因为要凑足总和 8），即 a[x][y] = z。
然后数组 x 填完了，转到下一个数组：x+1，桶下标重置为 0，剩余总数重置为 8（dfs(x+1, 0, 8)）。
return 结束当前递归
分支三：普通情况 —— 尝试当前桶分多少
当前桶 y 可以放 0 - z 里的任意数量 i。
枚举从大到小 i = z ... 0。
把 i 放进当前桶 a[x][y] = i。
递归填下一个桶：y+1，剩余可分配数减为 z-i
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
#define ll long long
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 3e5;
constexpr ll inf = 23333333333ll;

inline ull ha(const int a[5], const int b[5]) {
    ull rt = 1, ans = 0;
    rep(i,5) ans += rt*a[i], rt*=inf;
    rep(i,5) ans += rt*b[i], rt*=inf;
    return ans;
}

int f[N], d[N];
queue<int> q;//BFS 队列
map<ull, int> mp;//哈希 -> 状态编号(状态压缩查表)
vector<int> g[N];//反向图：g[from] 里的邻居可由 from 转移到
inline void build(int x, int a[5], int b[5]) {
    if (a[0] == 8 && b[0] < 8) f[x] = 1, q.push(x);
    else if (b[0] == 8 && a[0] < 8) f[x] = 0, q.push(x);
    for (int i = 1; i < 5; ++i) if (a[i])
        for (int j = 1; j < 5; ++j) if (b[j]) {
            a[i]--; a[(i+j)%5]++;
            int t = mp[ha(b, a)];
            g[t].push_back(x); d[x]++;
            a[i]++; a[(i+j)%5]--;
        }
}

struct node { int a[5], b[5]; } c[N];

int l;
inline void get(int a[5], int b[5]) {
    node t{};
    memcpy(t.a, a, sizeof(*a)); memcpy(t.b, b, sizeof(*b));
    rep(i,5) t.a[i] = a[i], t.b[i] = b[i];
    c[++l] = t; f[l] = -1; mp[ha(a, b)] = l;
}

int a[2][5];
void dfs(int x, int y, int z) {
    if (x == 2) { get(a[0], a[1]); return; }
    if (y == 4) { a[x][y] = z; dfs(x+1, 0, 8); return; }
    for (int i = z; i >= 0; --i)
        a[x][y] = i, dfs(x, y+1, z-i);
}

inline void solve() {
    while (!q.empty()) {
        int x = q.front(); q.pop();
        rep(i,g[x].size()) {
            int v = g[x][i];
            if (f[v] == 1) continue;
            if (!f[x]) f[v] = 1, q.push(v);
            else if (!--d[v]) f[v] = 0, q.push(v);
        }
    }
}

int x;
int main() {
    fast;
    dfs(0, 0, 8);//枚举所有状态
    for (int i = 1; i <= l; ++i) build(i, c[i].a, c[i].b);//建图+标记终止态
    solve();//反向BFS推胜负
    int T; cin >> T;
    while (T--) {
        int flg; cin >> flg; memset(a, 0, sizeof(a));
        rep(j,2) rep(i,8) cin >> x, a[j][x]++;//读入 8 个数做桶计数
        int t = f[mp[ha(a[flg], a[flg^1])]];
        if (t == -1) cout << "Deal\n";
        else if (flg^t) cout << "Alice\n";
        else cout << "Bob\n";
    }
    return 0;
}