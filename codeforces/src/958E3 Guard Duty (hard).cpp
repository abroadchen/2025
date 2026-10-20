//
// Created by Psy.C on 2026/10/20.
//
/**
x, y：坐标
id：编号（一类点 1..n，二类点 1..n）
type：false=一类，true=二类
以基准点 t 为原点，按斜率（极角）升序排列其余点。这是从 t 出发看所有点的角度排序（注意分母可能为负/零，代码用浮点近似处理）
取当前区间最左下的点作为「基准 t」，它必然位于某个配对线段的一端。把其余点按绕 t 的极角排序后，寻找一个"类型平衡"的切分点，让 t 与某个点配对，并把问题分成左右两个子区间递归
从极角最大处往前扫描，统计与 t 同类的数量 s1 和异类的数量 s2。循环条件：t.type == a[k].type || s1 != s2，停止条件是找到了一个异类的点，并且前面 s1==s2（类型平衡）‍。

含义：找一个分界点 k，使得 [l+1, k] 这个"扇区"内与 t 同类和异类的点数目相等（平衡），并且 k 点本身与 t 异类。这样 t 与 a[k] 配对后，左右子区间内两类点仍是平衡的（可递归配对）
若 a[k] 是二类（true），则基准 t（一类）配给 a[k]：ans[t.id] = a[k].id；反之 ans[a[k].id] = t.id。把配对结果存入 ans。
基准 t 与 a[k] 之间的点和 a[k] 之后的点分别递归处理
前 n 个点为一类（type=false，id=1..n）
后 n 个点为二类（type=true，id 重新设为 1..n）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 2e4+10;

struct node { int x, y, id; bool type; } a[N], t;
bool cmp(const node& a, const node& b) {//用于找"最左下"的点（x 最小、其次 y 最小）
    return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cmp2(const node& a, const node& b) {
    return 1.0*(a.y-t.y)/(a.x-t.x) < 1.0*(b.y-t.y)/(b.x-t.x);
}

int ans[N];
void dfs(int l, int r) {
    if (l > r) return;
    int c = min_element(a+l, a+r+1, cmp) - a;
    swap(a[c], a[l]), t = a[l];
    sort(a+l+1, a+r+1, cmp2);
    int k = r, s1 = 0, s2 = 0;
    for (; t.type == a[k].type || s1 != s2; --k)
        if (a[k].type == t.type) s1++; else s2++;
    a[k].type ? ans[t.id] = a[k].id : ans[a[k].id] = t.id;
    dfs(l+1, k-1), dfs(k+1, r);
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int main() {
    fast;
    int n; read(n);
    rep(i,1,2*n) read(a[i].x), read(a[i].y), a[i].type = (a[i].id=i) > n;//前 n 个 type=false，后 n 个 type=true
    rep(i,n+1,2*n) a[i].id -= n;//二类点 id 归一为 1..n
    dfs(1, 2*n);
    rep(i,1,n) cout << ans[i] << '\n';
    return 0;
}