//
// Created by Psy.C on 2026/9/6.
//
/**
ii：简写 pair<int, int>，用于存储 (value, index) 对
N：数组最大规模（10^5）。
M：块的大小，这里固定为 320（接近
10
5
≈
316
10
5

​
 ≈316）。
inf：无穷大，用于初始化。
bel(x)：计算下标 x 属于第几块（1-indexed）
chkmin：如果 b 小于当前值 a，则更新 a 为 b

a[N]：原始数组。
blocks：总块数。
L[i] / R[i]：第 i 块的左端点和右端点（下标）。
f[N][M]：辅助数组，f[i][j] 表示位置 i 到第 j 块最近的元素差值。
s[M][M]：块与块之间的预处理结果，s[i][j] 存储第 i 块到第 j 块之间（完全包含）的最小差值。
b[N]：存放 (value, index) 对，用于块内排序。
m：查询次数

读取数据：将原始数组读入 a，并构建 (value, index) 对数组 b。
确定块数：根据 n 计算总块数。
划分块边界：设定每块的左右端点。注意最后一块可能不足 M，因此手动修正右端点为 n

对于块 i 中的每个元素 b[k]，使用双指针在块 j 中找到最接近的元素（由于块内排序，时间复杂度
O
(
n
)
O(n)）。
将结果存入 f[原始下标][目标块号]


完整块部分：如果查询跨越了多个完整块（即 bL+1 <= bR-1），则直接取预处理好的 s[bL+1][bR-1] 作为候选答案。
边界块处理：
还需要考虑左端块 bL 和右端块 bR 的影响，因为它们只被部分覆盖。
使用 f[r][bL+1] 和 f[l][bR-1] 计算左端块与紧邻块、右端块与紧邻块之间的最小距离。
收集实际数值：
遍历左端块 bL 中位于 [l, r] 范围内的元素，将其值加入 vl。
同理，遍历右端块 bR 中位于 [l, r] 范围内的元素，将其值加入 vr。
注意这里使用的是全局数组 b（已经排序），但筛选条件基于原始下标 (b[i].second)。
调用 merge()：计算左块与右块

pre 记录上一个元素的值。
对于每个满足下标范围的元素，计算当前值与 pre 的差值，更新 ans。
因为块内已排序，这样就能得到该块内的最小差。


阶段一（跨块最近值）‍：对每一对块 (i, j)，对第 i 块内的每个元素 k（实际遍历原始下标），用双指针在第 j 块的排序数组里找到值最接近 a[k] 的元素，把这个最小绝对差存入 f[原始下标k][j]。即"元素 k 与第 j 块内最接近元素的距离"。这通过单调双指针 l 完成。

阶段二（stretch 扩展）‍：f[k][j] 原本只对"直接相邻的块"有效，这里通过在块内按 j 单调方向用 f[k][j±1] 更新自己，让每个元素 k 的 f[k][j] 表示"元素 k 到任何第 j 块的最短距离"（本质是 DP 传递 min，因为 abs 差满足单调传播）。

阶段三（块内前缀/后缀最小化）‍：对于固定块 j，块 i 内元素 k 的 f[k][j] 再沿 k 方向（块内下标单调）求前缀/后缀最小值，从而 u 表述"以元素为下标的查询需要的最小值"。这为查询阶段用 f[r][...]、f[l][...] 直接 O(1) 取用做准备。

阶段四（自块最小差）‍：s[i][i] 保存第 i 块内相邻排序元素间的最小差值（即"整块内部的最小距离"，因为块内已按值排序，最近的两个相邻即可）。int &S 是引用别名，直接修改 s[i][i]

s[i][j-1]：去掉第 j 块的区间最小值；
s[j][j]：第 j 块内部的最小差；
f[R[j]][i]：第 j 块末尾元素 R[j] 与第 i 块的最短交叉距离（边界处的跨块贡献）

情况一（跨块，bL < bR）‍：
若存在完整中间块区间 [bL+1, bR-1]，直接用预处理的 s[bL+1][bR-1] 作为基础答案 ans。
再用 f[r][bL+1]（右端点 r 与下一块 bL+1 的最小差）和 f[l][bR-1]（左端点 l 与上一块 bR-1 的最小差）更新。
剩下左右两个残缺块（bL 中下标 ≥ l 的元素、bR 中下标 ≤ r 的元素）收集到 vl、vr，调用 merge() 归并求最小差。
三者取最小即答案。注意：残缺块与中间完整块、残缺块彼此之间的贡献，通过 merge() 内部的每个排序数组找最近邻 + 双指针部分覆盖。
情况二（同块，bL == bR）‍：整个区间都在一块内。因为该块已按值排序，遍历块内、筛出下标在 [l,r] 内的元素，相邻两个的差取最小即可（用 pre 记录上一个选中元素的值）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, M = 320, inf = 0x3f3f3f3f;
#define bel(x) ((x-1)/M+1)

inline void chkmin(int &a, int b) { a = b > a ? a : b; }

vector<int> vl, vr;
inline int merge() {
    int l1 = 0, l2 = 0, ans = inf;
    //左块内部相邻元素的最小差值
    for (int i = 0; i < vl.size()-1; ++i) chkmin(ans, vl[i+1]-vl[i]);
    //右块内部相邻元素的最小差值
    for (int i = 0; i < vr.size()-1; ++i) chkmin(ans, vr[i+1]-vr[i]);
    //双指针遍历两块，找跨块的最小差值
    while (l1 < vl.size() && l2 < vr.size()) {
        chkmin(ans, abs(vl[l1]-vr[l2]));
        if (vl[l1] < vr[l2]) ++l1; else ++l2;
    }
    return ans;
}

int a[N], blocks, L[M], R[M], f[N][M], s[M][M], m;
ii b[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = {a[i], i};
    blocks = bel(n);//总块数 = 最后一块编号
    for (int i = 1; i <= blocks; ++i) L[i] = R[i-1]+1, R[i] = i*M;
    R[blocks] = n;
    for (int i = 1; i <= blocks; ++i) sort(b+L[i], b+R[i]+1);
    for (int i = 1; i <= blocks; ++i) {
        for (int j = 1; j <= blocks; ++j) if (i != j) {
            for (int k = L[i], l = L[j]; k <= R[i]; ++k) {
                while (l < R[j] && b[l+1].first < b[k].first) ++l;
                f[b[k].second][j] = abs(b[k].first - b[l].first);
                if (l < R[j]) chkmin(f[b[k].second][j], abs(b[l+1].first - b[k].first));
            }
        }
        for (int k = L[i]; k <= R[i]; ++k) {
            for (int j = i-2; j >= 0; --j) chkmin(f[k][j], f[k][j+1]);
            for (int j = i+2; j <= blocks; ++j) chkmin(f[k][j], f[k][j-1]);
        }
        for (int j = 1; j < i; ++j)
            for (int k = L[i]+1; k <= R[i]; ++k) chkmin(f[k][j], f[k-1][j]);
        for (int j = i+1; j <= blocks; ++j)
            for (int k = R[i]-1; k >= L[i]; --k) chkmin(f[k][j], f[k+1][j]);
        int &S = s[i][i]; S = inf;
        for (int j = L[i]; j < R[i]; ++j) chkmin(S, b[j+1].first-b[j].first);
    }
    for (int i = 1; i <= blocks; ++i)
        for (int j = i+1; j <= blocks; ++j) s[i][j] = min(min(s[i][j-1], f[R[j]][i]), s[j][j]);
    for (cin >> m; m--; ) {
        int l, r; cin >> l >> r;
        const int bL = bel(l), bR = bel(r);//左右端点的块编号
        int ans = inf;
        if (bL < bR) {
            if (bL + 1 <= bR - 1)
                ans = s[bL+1][bR-1], chkmin(ans, min(f[r][bL+1], f[l][bR-1]));
            vl.clear(), vr.clear();
            for (int i = L[bL]; i <= R[bL]; ++i)
                if (b[i].second >= l) vl.push_back(b[i].first);
            for (int i = L[bR]; i <= R[bR]; ++i)
                if (b[i].second <= r) vr.push_back(b[i].first);
            chkmin(ans, merge());
        } else {
            int pre = -inf;
            for (int i = L[bL]; i <= R[bL]; ++i)
                if (l <= b[i].second && b[i].second <= r)
                    chkmin(ans, b[i].first - pre), pre = b[i].first;
        }
        cout << ans << '\n';
    }
    return 0;
}