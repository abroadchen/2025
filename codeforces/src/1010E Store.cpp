//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
node：三元坐标点。
a[x]：临时数组，build 排序时用。
v[x]：KD-tree 节点 x 存储的实际点坐标
opt：当前分割的维度（0/1/2 对应 x/y/z）。
cmp：按第 opt 维坐标比较两点，供 nth_element 用
mn[x][i] / mx[x][i]：以节点 x 为根的子树中，所有点在 i 维的最小/最大值（该子树覆盖的包围盒）。
ls[x] / rs[x]：节点 x 的左右子节点
先把 mn/mx 都初始化为当前节点自身坐标
分别与左、右子树的 mn/mx 取 min/max，从而节点 x 覆盖的包围盒 = 自身 + 左子树 + 右子树中所有点的最小最大范围。这是 KD-tree 剪枝的关键
cnt：节点编号计数器。
build 递归构建，x 通过引用赋值为新节点编号。
mid = (l+r)>>1 取中点。
opt = wd 指定当前分割维度。
nth_element：把 a[l..r] 重新排列，使 a[mid] 是第 (mid-l) 小的那个点（按 opt 维），且左边的都比它小、右边的都比它大（但不保证完整有序）。这是 O(区域大小)，比 sort 快
把中位点 a[mid] 存入 v[x] 作为当前节点。
递归建左子树 [l, mid-1]、右子树 [mid+1, r]，分割维度交替：(wd+1)%3 → 0→1→2→0… 保证三维都分割，使树均衡。
up(x)：构建完子树后更新该节点覆盖的包围盒
判断一个点（X1=X2=X，单点）是否完全落在大盒 [x1..x2]×[y1..y2]×[z1..z2] 内。返回 1 表示命中
判断两个盒子（查询盒 vs 某子树包围盒）‍在任意一维没有重叠即整体不相交。返回 1 表示可剪枝（该子树不会有点在查询盒内）
KD-tree 查询：

节点为空 → 没有点。
当前节点自身点已在查询盒内 → 找到答案，返回 1。
整个子树包围盒与查询盒不相交 → 这个子树里绝不可能有点在盒内，直接剪掉。
都不满足 → 递归左右子树找。
剪枝靠的是节点维护的子树包围盒 mn/mx。查询盒通常就是"询问点与原长方体构成的一个大盒"，只要有任何外点落进这个大盒，就说明询问点被某个外点挡着 → CLOSED
读入前 3 个数作为包围盒起点的角点 (x1,y1,z1)，接着读 n（盒内点数）、m（盒外点数）、k（询问次数）
读入 n 个"盒内点"，并用它们扩展包围盒 [x1..x2]×[y1..y2]×[z1..z2]（对每个维取 min/max）。得到的这个包围盒，是所有内点必然在其中、且真长方体在其中
读入 m 个"外点"。若某外点落在 n 个内点构成的包围盒内，说明两边信息矛盾（外点被迫也在盒内）→ 输入非法，输出 INCORRECT 结束。
否则把它存入 a[i] 作为 KD-tree 待建点集
没有矛盾，输出 CORRECT，用 m 个外点构建 KD-tree（根节点 rt，初始分割维度 0)
每次询问读入一个点。若询问点已在包围盒内 → 输出 OPEN（直接在里面，无需查 KD-tree）
以"询问点"和"长方体/包围盒"为两个对角构建一个大查询盒 [a, b]：
a 的每个维 = min(询问点坐标, 盒下界)
b 的每个维 = max(询问点坐标, 盒上界)
这个盒子即为"询问点与原有盒之间的连线范围"。
用 ask 在 KD-tree（m 个外点）里查是否存在外点落进这个大盒：
若有 → 询问点被外点隔开，不可直达 → CLOSED
若无 → 询问点在盒外且无外点阻挡 → UNKNOWN
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 2e5+5;

struct node { int x[3]; } a[N], v[N];

int opt;
inline int cmp(node x, node y) { return x.x[opt] < y.x[opt]; }

int mn[N][3], mx[N][3], ls[N], rs[N];
void up(int x) {
    rep(i,3) mn[x][i] = mx[x][i] = v[x].x[i];
    if (ls[x]) {
        rep(i,3) {
            mx[x][i] = max(mx[x][i], mx[ls[x]][i]);
            mn[x][i] = min(mn[x][i], mn[ls[x]][i]);
        }
    }
    if (rs[x]) {
        rep(i,3) {
            mx[x][i] = max(mx[x][i], mx[rs[x]][i]);
            mn[x][i] = min(mn[x][i], mn[rs[x]][i]);
        }
    }
}

int cnt;
void build(int &x, int l, int r, int wd) {
    if (l > r) return;
    x = ++cnt;
    int mid = (l+r)>>1; opt = wd;
    nth_element(a+l, a+mid, a+r+1, cmp);
    v[x] = a[mid];
    build(ls[x], l, mid-1, (wd+1)%3);
    build(rs[x], mid+1, r, (wd+1)%3);
    up(x);
}

int in(int x1, int x2, int y1, int y2, int z1, int z2, int X1, int X2, int Y1, int Y2, int Z1, int Z2) {
    return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2 && z1 <= Z1 && Z2 <= z2;
}
int out(int x1, int x2, int y1, int y2, int z1, int z2, int X1, int X2, int Y1, int Y2, int Z1, int Z2) {
    return x1 > X2 || X1 > x2 || y1 > Y2 || Y1 > y2 || z1 > Z2 || Z1 > z2;
}
int ask(int x, node a, node b) {
    if (!x) return 0;
    if (in(a.x[0],b.x[0],a.x[1],b.x[1],a.x[2],b.x[2],v[x].x[0],v[x].x[0],v[x].x[1],
        v[x].x[1],v[x].x[2],v[x].x[2])) return 1;
    if (out(a.x[0],b.x[0],a.x[1],b.x[1],a.x[2],b.x[2],mn[x][0],mx[x][0],mn[x][1],
        mx[x][1],mn[x][2],mx[x][2])) return 0;
    if (ask(ls[x], a, b)) return 1;
    return ask(rs[x], a, b);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int x1 = rd(), y1 = rd(), z1 = rd(), n = rd(), m = rd(), k = rd(), x2=0, y2=0, z2=0, rt=0;
    for (int i = 1; i <= n; i++) {
        int x = rd(), y = rd(), z = rd();
        x1 = min(x1, x), y1 = min(y1, y), z1 = min(z1, z);
        x2 = max(x2, x), y2 = max(y2, y), z2 = max(z2, z);
    }
    for (int i = 1; i <= m; i++) {
        int x = rd(), y = rd(), z = rd();
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && z1 <= z && z <= z2) {
            cout << "INCORRECT\n"; return 0;
        }
        a[i].x[0] = x; a[i].x[1] = y; a[i].x[2] = z;
    }
    cout << "CORRECT\n";
    build(rt, 1, m, 0);
    while (k--) {
        int x = rd(), y = rd(), z = rd();
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && z1 <= z && z <= z2) {
            cout << "OPEN\n"; continue;
        }
        node a = {min(x,x1), min(y,y1), min(z,z1)},
        b = {max(x,x2), max(y,y2), max(z,z2)};
        if (ask(rt, a, b)) cout << "CLOSED\n"; else cout << "UNKNOWN\n";
    }
    return 0;
}