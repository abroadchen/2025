//
// Created by Psy.C on 2026/10/15.
//
/**
N=1e5+5：数组规模上限。
inf=2e9：无穷大初值（用来初始化答案并作为哨兵边界 d[m+1]=L[n+1]=inf）。
d[N]：某类坐标数组（后文看是某种"传送带/竖线"的 x 坐标），m 是其数量。
L[N]：另一类坐标数组，n 是其数量
两个函数结构相同，都是在递增数组里二分定位"x 落在哪个区间 [d[mid], d[mid+1})"，返回左端点下标 mid。
数组下标从 1 开始存数据，d[0]=L[0]=0（默认全局 0），末尾是哨兵 d[m+1]=L[n+1]=inf。
find(x) 返回 x 左侧最近的 d 坐标位置；get(x) 同理针对 L。
二者都假定数组已递增排序
读入：

R, C：网格行列（行数/列数）。
n：L 数组长度（某种"行/竖线"坐标数）。
m：d 数组长度（另一种坐标数）。
V：某个速度/步长参数（后文用于"传送"代价）。
预处理：

d[m+1] = L[n+1] = inf：设置数组末尾哨兵。
读入 L[1..n] 和 d[1..m]，分别排序（保证二分可用）。
每个询问 (sy,sx) -> (ty,tx)：

sy, sx：起点(row?, col?)，ty, tx：终点。
先二分 j = find(sx)（d 组中 sx 的左侧邻居），k = get(sx)（L 组中 sx 的左侧邻居）。
情况 1：同行直达
若起点终点同一行，直接水平移动，代价为 |sx - tx|。
情况 2：不同行，找最短路径
用四条候选路径取最小：

sx -> d[j] -> 沿 d 列传输 -> d[j] -> tx（j 存在时）
同上但用右侧邻居 d[j+1]（j < m 时）。

sx -> L[k] -> 沿 L 传输 -> L[k] -> tx（k 存在时）
同上但用右侧邻居 L[k+1]（k < n 时）
代价分解：

sgn(sx-d[j])：从起点水平走到竖线 d[j] 的横向代价。
(sgn(ty-sy)-1)/V + 1：沿竖线从 sy 到 ty 的纵向代价——|ty-sy| 长度，按步长 V 走，(|Δ|-1)/V + 1 相当于向上取整 ceil((|Δ|-1+1)/V)，即向上取整的步数（/V 整除 +1 处理余数）。
sgn(d[j]-tx)：从竖线 d[j] 水平走到终点 tx 的代价。
对 L 的情况，纵向代价是 sgn(ty-sy)（无 V 分母，说明 L 类型的传输按 1 格/单位代价，不除以 V）。
输出：打表所有候选最短代价 ans，无同行时结果来自四种候选最小值
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5, inf = 2e9;

int d[N], m;
int find(int x) {
    int l = 0, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (d[mid] <= x && x < d[mid+1]) return mid;
        if (d[mid] <= x) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}

int L[N], n;
int get(int x) {
    int l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (L[mid] <= x && x < L[mid+1]) return mid;
        if (L[mid] <= x) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int sgn(int x) { return x < 0 ? -x : x; }

int R, C, V, Q, ans;
int main() {
    cin >> R >> C >> n >> m >> V;
    d[m+1] = L[n+1] = inf;
    rep(i,1,n) L[i] = rd();
    rep(i,1,m) d[i] = rd();
    sort(d+1, d+1+m); sort(L+1, L+1+n);
    Q = rd();
    rep(i,1,Q) {
        ans = inf;
        int sy = rd(), sx = rd(), ty = rd(), tx = rd();
        int j = find(sx), k = get(sx);
        if (sy == ty) ans = sgn(sx - tx);
        else {
            if (j) ans = min(ans, sgn(sx-d[j])+(sgn(ty-sy)-1)/V+1+sgn(d[j]-tx));
            if (j < m) ans = min(ans, sgn(sx-d[j+1])+(sgn(ty-sy)-1)/V+1+sgn(d[j+1]-tx));
            if (k) ans = min(ans, sgn(sx-L[k])+sgn(ty-sy)+sgn(L[k]-tx));
            if (k < n) ans = min(ans, sgn(sx-L[k+1])+sgn(ty-sy)+sgn(L[k+1]-tx));
        }
        cout << ans << '\n';
    }
    return 0;
}