//
// Created by Psy.C on 2026/10/6.
//
/**
g：某个权重/评分值。
w：原始位置（原始下标）。
a：最终要输出的答案标签（类别）。
代码读入 n 和每个元素的 g，按 g 从大到小排序。
用 g[i] - g[i+1] 来表示相邻排序后元素的差值（可以看作"断点权重"）。
然后套用 RMQ（ST 表）来快速查询区间内最大的 g[i]-g[i+1] 及其位置。
主流程用三层枚举尝试把数组切成三段，选出"字典序/数值上最优"的三个断点，分别标为类别 1、2、3，其余标为 -1
cmp：按 g 降序。
cmp2：按 w（原始下标）升序——用于最后恢复原顺序输出。
f[0][i] = a[i].g - a[i+1].g：长度为 1 的区间的值就是"第 i 与第 i+1 个元素的差值"。
pos[0][i] = i：记录这个值对应的位置 i。
计算 lg[]（log2 表）。
后续用倍增法构建 f[j][i]（区间 [i, i+2^j-1] 内最大的差值和它的位置），f 存最大值、pos 存最大值所在位置。
注意：a[i+1] 在 i == n 时会读到 a[n+1]（越界，默认 0），这是代码的潜在风险点
标准的 RMQ 查询：取区间长度对应的 lg，比较覆盖整个区间的两个重叠块 [l, l+2^x-1] 和 [r-2^x+1, r] 的最大值，返回较大者的位置。
注意这里 > 比较，平局时偏向取右块的位置（当二者相等时走 else 返回右块
外层枚举第一个断点 i。
l = ((i+1)>>1)+i，r = min((i<<1)+i, n) 限定第二个断点 j 的范围（这是由题目中"组大小"的约束推导出的，i 与 j-i 需满足某种比例关系）。
内层枚举 j。
由 x=i, y=j-i（两段长度）计算第三个断点 k 的允许区间 [mn, mx]。
用 ask(mn, mx) 在区间内查询差值最大的位置作为 k。
通过 a1, a2, a3（三段断点处的差值）做字典序比较——优先让第一段差值最大，然后第二段，再第三段，采用"如果更优则更新"的贪心策略。
l1, l2, l3 记录最终选定的三个断点位置
把排序后的数组按断点分成四段：前 l1 个标 1，接着 l2-l1 个标 2，再 l3-l2 个标 3，其余标 -1。
最后按 cmp2（原始下标）排序恢复顺序，输出每个元素对应的标签
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e3+5, M = 15;

struct node { int g, w, a; } a[N];
inline bool cmp(const node& x, const node& y) { return x.g > y.g; }
inline bool cmp2(const node& x, const node& y) { return x.w < y.w; }

int n, lg[N], f[M][N], pos[M][N];
void init() {
    for (int i = 0; 1<<i <= n; ++i) lg[1<<i] = i;
    for (int i = 1; i <= n; ++i) {
        f[0][i] = a[i].g - a[i+1].g;
        pos[0][i] = i;
        if (lg[i]) continue;
        lg[i] = lg[i-1];
    }
    for (int j = 1; j <= lg[n]; ++j) {
        int lim = n - (1<<j) + 1;
        for (int i = 1; i <= lim; ++i) {
            if (f[j-1][i] > f[j-1][i+(1<<(j-1))]) {
                f[j][i] = f[j-1][i];
                pos[j][i] = pos[j-1][i];
            } else {
                f[j][i] = f[j-1][i+(1<<(j-1))];
                pos[j][i] = pos[j-1][i+(1<<(j-1))];
            }
        }
    }
}

int ask(const int& l, const int& r) {
    int x = lg[r-l+1];
    if (f[x][l] > f[x][r-(1<<x)+1]) return pos[x][l];
    return pos[x][r-(1<<x)+1];
}

int a1, a2, a3, l1, l2, l3, l, r, x, y, mx, mn;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].g; a[i].w = i;
    }
    sort(a+1, a+n+1, cmp); init();
    for (int i = 1; i <= n; ++i) {
        if (a1 > a[i].g - a[i+1].g) continue;
        l = ((i+1)>>1) + i; r = min((i<<1)+i, n);
        for (int j = l; j <= r; ++j) {
            if (a1 == a[i].g - a[i+1].g && a2 > a[j].g - a[j+1].g) continue;
            x = i; y = j - i; mx = max((x+1)>>1, (y+1)>>1) + j;
            mn = min(min(x<<1, y<<1)+j, n);
            if (mx > mn) continue;
            int k = ask(mx, mn);
            if (a1 == a[i].g - a[i+1].g && a2 == a[j].g - a[j+1].g &&
                a3 > a[k].g - a[k+1].g) continue;
            a1 = a[i].g - a[i+1].g; a2 = a[j].g - a[j+1].g; a3 = a[k].g - a[k+1].g;
            l1 = i; l2 = j; l3 = k;
        }
    }
    for (int i = 1; i <= l1; ++i) a[i].a = 1;
    for (int i = l1+1; i <= l2; ++i) a[i].a = 2;
    for (int i = l2+1; i <= l3; ++i) a[i].a = 3;
    for (int i = l3+1; i <= n; ++i) a[i].a = -1;
    sort(a+1, a+n+1, cmp2);
    for (int i = 1; i <= n; ++i) cout << a[i].a << ' ';
    return 0;
}