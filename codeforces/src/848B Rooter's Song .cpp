//
// Created by Psy.C on 2026/9/29.
//
/**
N：数组容量上界（200005）。
inf = 1e5（100000）：用作下标偏移基准（后面 p-t+inf 防负数）。
node {x, y, id}：一个三元组：
x、y：坐标（水平/垂直方向的位置）。
id：原始编号（哪个人/任务）。
ans[N]：存放每个人的最终答案坐标
自定义排序规则（用于 std::sort）：
先按 y 降序（> 大在前）；
y 相同则按 x 升序（< 小在前）
d[k]：按"键 k = p - t + inf"分桶的数组。每个桶内存放属于同一"key"的若干 node（带 id）。
pn：临时桶，存放重排后的坐标点（id 置 0）。
mp：unordered_map，记录某个 key 是否已出现过（去重）。
v：所有出现过的 key 的列表（用于遍历）
读入 n（人数）、x、y（两个方向的固定位移量）。
对每个人 i，读入 tp（类型）、p（位置）、t（时间）：
计算桶 key = p - t + inf。
若 tp == 1：人沿 X 方向，坐标设为 {p, 0}（x=p, y=0）。
若 tp == 2（else）：人沿 Y 方向，坐标设为 {0, p}（x=0, y=p）。
push 进 d[key]，带 id=i。
用 mp + v 记录第一次出现的 key，保证 v 里每个 key 只有一次。
语义：p - t 这个量（"出发时刻域"）相同的人会"互相追上/交换"——这是算法分桶的依据
对每个出现过的人桶 k：
清空 pn。
遍历桶里每个人 i：
若 i.y == 0（即原本是 X 方向的人，坐标 {p,0}）：生成一个"目标点" {x = i.x, y = y}（把 x 保留、y 换成 y 固定值）。
否则（Y 方向的人，坐标 {0,p}）：生成 {x = x, y = i.y}（x 换成 x，y 保留）。
即：把每个人的坐标"交叉映射"——X 方向的人得到 y 方向的位移，Y 方向的人得到 x 方向的位移。
这些目标点放进 pn，id=0
对原桶 d[k] 和 目标点桶 pn 都用同一个比较函数排序。
排序后，d[k] 的第 i 个（按自定义规则排好序）对应 pn 的第 i 个点。
把排序后第 i 个目标点 pn[i] 赋给"原桶排序后第 i 个人的 id"：ans[ d[k][i].id ] = pn[i]。
即：同一桶内按同一规则排序后，一一对应地重排目标坐标。这就是"同 key 的人互相交换/继承坐标"逻辑
按原始编号 1..n 输出每个人的最终坐标 x y，每行一个
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5, inf = 1e5;
struct node { int x, y, id; } ans[N];

static bool operator<(const node& a, const node& b) {
    if (a.y != b.y) return a.y > b.y;
    return a.x < b.x;
}

static int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

vector<node> d[N], pn;
unordered_map<int, int> mp;
vector<int> v;
int main() {
    fast;
    int n = rd(), x = rd(), y = rd();
    for (int i = 1; i <= n; ++i) {
        int tp = rd(), p = rd(), t = rd();
        if (tp == 1) d[p-t+inf].push_back({.x = p, .y = 0, .id = i});
        else d[p-t+inf].push_back({.x = 0, .y = p, .id = i});
        if (!mp[p-t+inf]) {
            v.push_back(p-t+inf);
            mp[p-t+inf] = 1;
        }
    }
    for (const auto k : v) {
        pn.clear();
        for (const auto i : d[k]) {
            if (!i.y) pn.push_back({.x = i.x, .y = y, .id = 0});
            else pn.push_back({.x = x, .y = i.y, .id = 0});
        }
        sort(d[k].begin(), d[k].end());
        sort(pn.begin(), pn.end());
        for (int i = 0; i < d[k].size(); ++i)
            ans[d[k][i].id] = pn[i];
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i].x << ' ' << ans[i].y << '\n';
    return 0;
}