//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
ODT（Old Driver Tree / 珂朵莉树）维护区间覆盖 + 扫描线 + 二分答案
树上维护一段段"值相同的连续区间"
每个节点表示一个连续区间 [l, r]，其值是 id。
按左端点 l 排序放在 set 中
初始整段 [1, inf] 都是 id=0（"空/未被覆盖"）
lower_bound({x,0,0}) 找到第一个 l >= x 的区间。
若它左端点正好是 x，直接返回。
否则把包含 x 的那段 [l,r] 拆成 [l,x-1] 和 [x,r] 两段，返回第二段的迭代器
split(r+1)、split(l) 把区间拆齐，itl 与 itr 之间就是要被覆盖覆盖到的那几段。
对原 [l,r] 内每一段旧区间（原覆盖者 id 是 ti）：
若 ti == 0（原本是空的），跳过。
否则记录"从旧覆盖者 ti 手中收回了长度为 tr-tl+1 的区间"，写入 v[id]：
(1, -(tr-tl+1))：在"时间 1"开始减少这么多长度（因为新覆盖从 id 这一刻开始接管）。
(ti+1, +(tr-tl+1))：在"时间 ti+1"开始增加这么多长度（旧覆盖者在 ti 之后结束，这里回收回来）。
然后清掉被覆盖区间，插入新区间 [l,r] 值为 id。
v[id] 记录新覆盖的区间长度：
(1, r-l+1)：时间 1 开始加入 r-l+1。
(id+1, -(r-l+1))：时间 id+1 开始减掉这段（该覆盖到 id 结束）。
总结：v[id] 是"差分时间轴"——记录每个 id 覆盖的长度，在哪个时间点产生 / 消失。这样就能推演出"任一时刻，有多少长度被覆盖、被哪些 id 覆盖"
这是一个双指针（滑动窗口）扫描判定函数：

w[i] 是"数组差分"，l、r 是双指针下界/上界，sum 是当前 [l, r] 窗口内覆盖长度之和。
遍历右端点 r，更新窗口内的覆盖长度；若左端可继续推进且长度仍 ≥ x，则移动左指针。
ans 统计满足 sum >= x 的位置个数，若 ans >= k 返回 true，说明"存在至少 k 个位置覆盖长度 ≥ x"。
这本质是判断能否找到 ≥k 个位置，当前覆盖之和 ≥ x，属于二分答案的 check 函数（求满足条件的最大值）

读入 n、k。每个区间 [l[i], r[i]]（注意 r[i]--，即右端点减一，把闭区间处理成开区间）。
用 ODT 依次把区间 i 覆盖到 ids=i，同时构建差分差分数组 v。
assign 传的 id 是 i
二分出满足条件的最大的 x（答案）
最后用同样的双指针扫描，但这次是用已经二分出的最优答案 ans 来精确累加结果 res，并把边界位置的多余部分单独处理（res += (k-cnt)*ans），最后输出

l = 当前有效区间的左端点
r = 当前扫描的右端点
sum = 当前 [l, r] 内覆盖总长度
res = 最终答案累加
ret = 右端点推进过程中，随左端点变动而贡献的那部分累计
cnt = 统计"覆盖长度 > ans"的完整左端点个数
右端点推进到 r 时，应用属于 r 的所有差分事件。

若事件起点 fst <= l（已经在左端点左边或就在左端点），说明这条增减从位置 fst 一路横跨到当前左端点 l 都有效，所以：

sum += snd：它覆盖了后续所有位置，直接进 sum。
ret += snd*(l-fst+1)：还要补上 fst 到 l 这一段（之前没被计进 ret 的）对贡献的增量。因为 ret 是"左端点固定时，累积的有效长度贡献"，这里把这一段补齐。
若 fst > l（事件起点还在右边），暂时存进 w[fst]，等 l 推进过去再处理
如果当前覆盖总长度不超过最优答案 ans，这个右端点没有贡献，直接 continue
左端点在 l 时，若把左端点推到 l+1 后，总长度 sum + w[l+1] 仍然大于 ans，就继续左移。

l++：左端点向右移
sum += w[l]：把 l 位置上暂存的差分事件生效（因为 l 已经越过它）
ret += sum：每次左移，把当前新的 sum 累加进 ret（这段在统计时被计入贡献）
一句话：在保持 sum > ans 的前提下，尽量把左端点 l 往右推，使区间尽量短、贡献尽量精准
res += ret：把当前右端点下能贡献的总量累加进答案。
若当前 sum > ans（而不是仅仅等于），说明左端点 l 对应的位置也满足严格大于，记为 cnt += l
最后一步：因为结果要的是"第 k 大意义下的答案"，未被严格计入的 (k - cnt) 个位置，每个按最优值 ans 补齐

在时刻 fst 起，覆盖总长度会变化 snd。
snd > 0：此刻起长度增加
snd < 0：此刻起长度减少
由于有些事件起点 fst 还在右边（尚未轮到），就先暂存到 w[fst]，等左端点推进到 fst 时才正式生效。这是标准的差分 + 双指针技巧
*/
#include <bits/stdc++.h>
#define ii pair<int,int>
#define int long long
using namespace std;

constexpr int N = 3e5+5, inf = 1e9;

vector<ii> v[N];
namespace ODT {
    struct node {
        int l, r, id;
        bool operator<(const node &o) const { return l < o.l; }
    };
    set<node> s;
    void init() { s.insert({1,inf, 0}); }
    auto split(int x) {
        auto it = s.lower_bound({x,0,0});
        if (it->l == x) return it; --it;
        int l = it->l, r = it->r, id = it->id; s.erase(it);
        s.insert({l,x-1,id});
        return s.insert({x,r,id}).first;
    }
    void assign(int l, int r, int id) {
        auto itr = split(r+1), itl = split(l);
        for (auto it = itl; it != itr; ++it) {
            int tl = it->l, tr = it->r, ti = it->id;
            if (ti == 0) continue;
            v[id].emplace_back(1,-(tr-tl+1));
            v[id].emplace_back(ti+1,tr-tl+1);
        }
        s.erase(itl, itr); s.insert({l,r,id});
        v[id].emplace_back(1,r-l+1);
        v[id].emplace_back(id+1,-(r-l+1));
    }
}

int n, w[N], k;
int check(int x) {
    for (int i = 0; i <= n; i++) w[i] = 0;
    int l = 1, r = 1, sum = 0, ans = 0;
    for (; r <= n; r++) {
        for (auto [fst, snd] : v[r]) {
            if (fst <= l) sum += snd;
            else w[fst] += snd;
        }
        while (sum + w[l+1] >= x && l < r) l++, sum += w[l];
        if (sum >= x) ans += l;
    }
    return ans >= k;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int l[N], r[N];
signed main() {
    read(n), read(k);
    for (int i = 1; i <= n; i++) read(l[i]), read(r[i]), r[i]--;
    ODT::init();
    for (int i = 1; i <= n; i++) ODT::assign(l[i],r[i],i);
    int l = 0, r = inf, ans = 0;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) ans = mid, l = mid+1; else r = mid-1;
    }
    for (int i = 0; i <= n; i++) w[i] = 0;
    l = 1, r = 1;
    int sum = 0, res = 0, ret = 0, cnt = 0;
    for (; r <= n; r++) {
        for (auto [fst, snd] : v[r]) {
            if (fst <= l) sum += snd, ret += snd*(l-fst+1);
            else w[fst] += snd;
        }
        if (sum <= ans) continue;
        while (sum + w[l+1] > ans && l < r) l++, sum += w[l], ret += sum;
        res += ret;
        if (sum > ans) cnt += l;
    }
    res += (k-cnt)*ans;
    write(res);
    return 0;
}