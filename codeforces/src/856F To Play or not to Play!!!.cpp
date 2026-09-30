//
// Created by Psy.C on 2026/9/30.
//
/**
每个节点代表包络上的一个转折点 (x, y)（平面坐标），以及懒标记 (lx, ly)，key 是 Treap 的随机优先级，ch[0]/ch[1] 左右孩子
对整棵子树做整体平移：所有点的 x 都加 vx、y 都加 vy。
tag(k, vx, vy) 更新当前节点坐标，并累加到懒标记 lx/ly 上。
push_down 把懒标记下推到左右子树（孩子可能没建则跳过），然后清零。
这相当于"包络整体平移"，用于扫描线推进时的坐标变换
标准的无旋 Treap：merge 合并、split 按自定义谓词 cmp 分裂（把满足条件的放左树，否则右树）。cmp 是 lambda，可灵活按 x、y 或组合条件切分
find_mn(k)：返回以 k 为根的树中最左（中序遍历最小）节点。
find_mx(k)：返回最右（最大）节点。
由于包络点是按"某个序"存储在树里的，最小/最大对应包络的左端/右端转折点
把所有端点坐标排序后，相邻两点之间是一个区间，扫描时用「差分翻转」得到当前区间的覆盖状态 cur：

cur 是整数，初始 0，每遇到一个 v 点就 cur ^= v（即翻转该组在该段的覆盖）。
cur 的低 2 位表示组1、组2 是否覆盖当前区间。
于是当前区间 [vec[i], vec[i+1]) 长 len，根据覆盖状态做整体平移：

cur==1：只有组1覆盖 → 包络此时只由组1决定，沿 x 方向整体平移 len（tag(rt, len, 0)）。
cur==2：只有组2覆盖 → 沿 y 方向平移 len（tag(rt, 0, len)）。
cur==3：两组同时覆盖 → 需要做公共包络的交并处理（下面详述），整体沿两个方向同时平移 len。
cur==0 或 len==0：无人覆盖/零长度，跳过。
最终答案 = 扫描结束后树中 x 最大的点（也就是包络最右端点的 x 坐标，即题要求的最大值）。
这一步把包络按"角度带 ±C"分成三类：

k1：点在直线 x = y-C 左侧（x < y-C）。
k2：夹在 y-C <= x <= y+C 之间（斜率为负 ±C 的带状区域）。
k3：在 x > y+C 右侧。
这个分裂本质是按 x-y 与 ±C 的关系切分，C 是公共覆盖时线段的"斜率约束"
目的是把公共覆盖段补齐为一条完整的连续包络链，在空缺处补上新的转折点 (xl,yl)、(xr,yr)
公共段平移后，取出其最左点的 y（mxy）和最右点的 x（mxx）。
把左部 k1 中所有 y > mxy 的点拆出去丢掉（k4）；把右部 k3 中所有 x <= mxx 的点拆出去丢掉（k5）——保证整条包络在公共段过渡处单调衔接、无重叠。
拼回 k1 + k2 + k3，再整体平移 len。
这样，公共覆盖段处把两组包络的正确"包络线"保留下来（取重叠部分的合适极值）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6;

struct node { ll x, y, lx, ly; int key, ch[2]; } s[N+5];

void tag(int k, ll vx, ll vy) {
    s[k].x += vx; s[k].lx += vx;
    s[k].y += vy; s[k].ly += vy;
}
void push_down(int k) {
    if (!s[k].lx && !s[k].ly) return;
    if (s[k].ch[0]) tag(s[k].ch[0], s[k].lx, s[k].ly);
    if (s[k].ch[1]) tag(s[k].ch[1], s[k].lx, s[k].ly);
    s[k].lx = s[k].ly = 0;
}

int cnt;
mt19937 rng(time(0));
int init(ll x, ll y) {
    s[++cnt].x = x; s[cnt].y = y; s[cnt].key = rng();
    return cnt;
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    push_down(x); push_down(y);
    if (s[x].key < s[y].key) return s[x].ch[1] = merge(s[x].ch[1], y), x;
    return s[y].ch[0] = merge(x, s[y].ch[0]), y;
}

void split(int k, int& x, int& y, auto cmp) {
    if (!k) return x = y = 0, void(); push_down(k);
    if (cmp(s[k])) x = k, split(s[k].ch[1], s[k].ch[1], y, cmp);
    else y = k, split(s[k].ch[0], x, s[k].ch[0], cmp);
}

int find_mn(int k) {
    if (!s[k].ch[0]) return k; push_down(k);
    return find_mn(s[k].ch[0]);
}
int find_mx(int k) {
    if (!s[k].ch[1]) return k; push_down(k);
    return find_mx(s[k].ch[1]);
}

int n1, n2;
ll C;
vector<pair<ll, int>> vec;
int main() {
    fast;
    cin >> n1 >> n2 >> C;
    for (int i = 1; i <= n1*2; ++i) {
        ll x; cin >> x; vec.emplace_back(x, 1);
    }
    for (int i = 1; i <= n2*2; ++i) {
        ll x; cin >> x; vec.emplace_back(x, 2);
    }
    ranges::sort(vec);
    int cur = 0, rt = init(0, 0);
    for (int i = 0; i+1 < vec.size(); ++i) {
        cur ^= vec[i].second;
        ll len = vec[i+1].first - vec[i].first;
        if (!cur || !len) continue;
        if (cur == 1) { tag(rt, len, 0); continue; }
        if (cur == 2) { tag(rt, 0, len); continue; }
        int k1, k2, k3, k4, k5;
        split(rt, k1, k2, [&](const node &x) {
            return x.x < x.y - C;
        });
        split(k2, k2, k3, [&](const node &x) {
            return x.x <= x.y + C;
        });
        ll xl = -C, yl = 0, xr = 0, yr = -C;
        if (k1) xl = s[find_mx(k1)].x, yl = xl + C;//从左边接续
        if (k3) yr = s[find_mn(k3)].y, xr = yr + C;//从右边接续
        //构造公共段的新端点
        if (xl > xr || yl > yr) {//左端、右端算出的边界矛盾
            if (!k2) k2 = init(xl, yl);//无中间带 → 直接新建一个点
            else if (yl > s[find_mn(k2)].y) k2 = merge(init(xl, yl), k2);//插到 k2 左侧
        }
        if (!k2) k2 = init(xr, yr);//无中间带→建右点
        else if (xr > s[find_mx(k2)].x) k2 = merge(k2, init(xr, yr));//插到 k2 右侧
        tag(k2, len, len);//公共段整体沿 x,y 各平移 len（两点之间都覆盖）
        ll mxy = s[find_mn(k2)].y, mxx = s[find_mx(k2)].x;//k2 的最小y / 最大x
        //剪掉 k1 中 y 过大（高于 k2 下界）的部分，剪掉 k3 中 x 太小的部分
        split(k1, k1, k4, [&](const node &x) {//k4 被丢弃
            return x.y > mxy;
        });
        split(k3, k5, k3, [&](const node &x) {//k5 被丢弃
            return x.x <= mxx;
        });
        rt = merge(merge(k1, k2), k3);//重新拼回
        tag(rt, len, len);
    }
    cout << s[find_mx(rt)].x << '\n';
    return 0;
}