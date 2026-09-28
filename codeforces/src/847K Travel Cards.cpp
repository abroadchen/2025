//
// Created by Psy.C on 2026/9/28.
//
/**
inf = 0x3f3f3f3f：一个很大的"无穷大"（约 10.7 亿），可做占位/默认值。
N = 1e5+5：结果数组大小上限。
vis：把"城市名（字符串）"映射成整数编号。因为后面要用城市编号做 pair，而城市是字符串，不方便直接进 pair，所以先给每个字符串城市一个从 1 开始的编号 num。
q：键是 pair<int,int>（一对城市，min,max 保证顺序），值是"这条航线到目前为止累计的差价值"。用于统计每一条航线可以省多少钱。
res[N]：把 q 里的所有"差值"提出来存进这个数组，方便排序。
cmp：从大到小比较器，用于 sort 时把差值降序排
读 n（航班段数）、a（普通价）、b（相邻两段连买折扣价）、k（最多可用的套餐数量）、f（每个套餐的固定价格）。
t1, t2：本段航班的出发、目的城市字符串。
num：已分配的城市编号计数器。
sum：不买任何套餐时的总花费（逐步累加）。
t = inf：上一段的"终点城市编号"，初值设为无穷大，保证第一段不可能命中"相邻"判断
读入第 i 段的 t1（出发）、t2（到达）。
给新出现的城市分配编号：若 vis[t1]==0（还没编号），分配 ++num；t2 同理。
注意这里用了 map 的 operator[]，若键不存在会创建并初始化为 0，所以 ==0 判断"是否首次出现"是成立的
if (vis[t1] == t)
判断本段的出发城市 vis[t1] 是否等于上一段的终点城市 t。如果是，说明这两天航班"首尾相连"（连续两天在同一城市换乘），可以享受相邻连买折扣价 b。
else：否则说明这两天不连续，只能用普通价 a。
无论命中哪种，都要累加到 q 里对应的航线键：
键：{ min(vis[t1], vis[t2]), max(vis[t1], vis[t2]) } —— 把这条航线的两端按小到大排好。这样 a→b 和 b→a 会被算作同一条航线（同一键）。这正是题目"同一条航线最多用一个套餐"的要求——往返回头飞也共用同一个套餐配额。
值：q[键] += (a 或 b)，即这条航线的累计花费累加。因为"一条航线买套餐"是把这条航线的所有相关花费都按套餐算，所以需要先统计"这条航线若全部按普通价算，共花了多少钱"，这就是能省的钱。
sum += (a 或 b)：同时把本次的花费计入总花费 sum。
t = vis[t2];：更新"上一段终点"为当前段的终点，供下一段判断"是否相邻"。
把 q 里每一条航线的累计花费（即每条航线若按普通/折扣累加后的总花费）取出来，存进 res[1..ans]（res[0] 不用）。
这里 q | views::values 是 C++20 的 ranges 写法，等价于遍历每个 map 元素并只取 .second（value）。注意：若编译器不支持 C++20 ranges，应改写为 for (auto &it : q) res[++ans] = it.second;。
这一步的意义：q 里每个 value 代表"第 j 条航线总共花了多少"，这些值就是"如果给这条航线买一个套餐 f，最多能省 value - f（前提是 value > f）"
把 res[1..ans] 按从大到小排序（用 cmp）。
排完序后，排在前面的是累计花费最高的航线，也就是"买套餐最划算"的航线（省得最多）
最多买 k 个套餐，逐个看前 k 条最贵的航线：
若 res[i] < f：这条航线的花费还没套餐价 f 高，买了反而亏，直接 break（后面更矮，更不划算）。
否则：买这个套餐，总花费 sum 减去 (res[i] - f)，即"这条航线原来花了 res[i]，现在花 f，省了 res[i]-f"。
输出最终最小总花费
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int inf = 0x3f3f3f3f, N = 1e5+5;
map<string, int> vis;
map<ii, int> q;
int res[N];
bool cmp(int t1, int t2) { return t1 > t2; }
int main() {
    fast;
    int n, a, b, k, f;
    cin >> n >> a >> b >> k >> f;
    string t1, t2;
    int num = 0, sum = 0, t = inf;
    for (int i = 1; i <= n; ++i) {
        cin >> t1 >> t2;
        if (vis[t1] == 0) vis[t1] = ++num;
        if (vis[t2] == 0) vis[t2] = ++num;
        if (vis[t1] == t) q[{min(vis[t1], vis[t2]), max(vis[t1], vis[t2])}] += b, sum += b;
        else q[{min(vis[t1], vis[t2]), max(vis[t1], vis[t2])}] += a, sum += a;
        t = vis[t2];
    }
    int ans = 0;
    for (auto &val: q | views::values) res[++ans] = val;
    sort(res+1, res+1+ans, cmp);
    for (int i = 1; i <= k; ++i) {
        if (res[i] < f) break;
        sum -= res[i] - f;
    }
    cout << sum << '\n';
    return 0;
}