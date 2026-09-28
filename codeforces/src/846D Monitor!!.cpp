//
// Created by Psy.C on 2026/9/28.
//
/**
用数组 dat 手写了一个单调队列（双端队列，用 head/tail 指针实现）。
q[N]：一组队列（每行一个），q3：单独的一个队列。
队列里存的是下标，通过 empty/front/back/push_back/pop_front/pop_back/clear 操作维护。
这套结构用于维护滑动窗口内的最大值（配合下面 get 里 <= 的 pop_back 比较，维护的是单调递减队列，队首即窗口最大值）
这是对第 i 行（q[i]）做滑动窗口：
先弹出移出窗口的下标：窗口左端为 x - S + 1，所以队头 < x - S + 1 的要从队首弹出。
再维护单调性：a[i][back] <= a[i][x] 时队尾弹出，保证队首是该窗口内 a[i] 值最大的位置（队首存最大值的下标）。
把 x 压入队尾。
若 x >= S（窗口已成形），返回队首下标（窗口最大值的下标）。
所以 get(i,x) 的作用是：维护第 i 行上以 x 为右端、长度 S 的滑动窗口中 a[i] 的最大值位置。窗口长度即 S。
注意 S 是全局变量（S = r），所以所有行的窗口宽度相同

输入 n × m 规模；全部初始化为 inf。
输入 r → 赋值给全局 S（滑动窗口长度）；输入 T，接下来 T 行把指定位置 (x,y) 赋为 t。其余位置保持 INF
遍历每一列 i（从 1 到 m）。注意这里 get(j, i) 的第一个参数 j 是行号（对应 q[j] 这一行队列），第二个参数 i 是列号（即当前处理的列位置 x）。
也就是说：对每一行 j，用 get 往前推进列位置 i，维护第 j 行上"以 i 为右端、长度 S"的列方向滑动窗口，返回窗口内最大值对应列下标 p。
若 p == -1 表示该行窗口未成形（i < S），则置 f[0] = 1 标记"这一列整列处理失败/信息不足"并 continue。
否则 f[j] = a[j][p]：f[j] 记录第 j 行在当前位置 i 的窗口最大值数值。
若 f[0] 被标记为 1，说明这一列有行还没凑满窗口，continue 跳过该列其余处理。
这一阶段本质：逐列地、对每一行做长度 S 的滑动窗口最大值，结果存入 f[j]
在每一列 i 内部，对刚才得到的 f[1..n]（每行的窗口最大值）再开一个单调队列 q3，做纵向长度为 r（=S）的滑动窗口最大值：
弹出窗口外元素、维护单调递减、压入 j。
当 j >= r（窗口成形）时，取队首 f[q3.front()]（该纵向窗口内的最大值），并用 mn = min(mn, ...) 更新全局最小值。
由于 a 中非 INF 位置很少、其余为大 INF，这里取"每列的两次窗口最大值的最小值"，本质是某种"求一个 r×r（横向 i 处理 + 纵向 r 窗口）区域相关的最小代价"。
第二阶段：对列维处理完的 f 序列，再做长度 r 的纵向滑动窗口最大值，求其全局最小值 mn
若 mn 仍为初始的 INF（无有效解），输出 -1；否则输出 mn
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e3+1;
constexpr ll inf = 1e9+7, INF = 1e18+7;

struct node {
    ll dat[N], head = 1, tail = 0;
    bool empty() const { return head > tail; }
    void push_back(ll x) { dat[++tail] = x; }
    void pop_front() { ++head; }
    void pop_back() { --tail; }
    void clear() { head = 1; tail = 0; dat[1] = dat[0] = 0; }
    ll front() const { return dat[head]; }
    ll back() const { return dat[tail]; }
} q[N], q3;

ll S, a[N][N];
ll get(ll i, ll x) {
    ll ret = -1;
    while (!q[i].empty() && q[i].front() < x - S + 1) q[i].pop_front();
    while (!q[i].empty() && a[i][q[i].back()] <= a[i][x]) q[i].pop_back();
    q[i].push_back(x);
    if (x >= S) ret = q[i].front();
    return ret;
}

ll f[N], mn(INF);
int main() {
    fast;
    ll n, m; cin >> n >> m;
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m; ++j) a[i][j] = inf;
    ll r, T; cin >> r; S = r; cin >> T;
    while (T--) {
        ll x, y, t; cin >> x >> y >> t; a[x][y] = t;
    }
    for (ll i = 1; i <= m; ++i) {
        q3.clear(); f[0] = 0;
        for (ll j = 1; j <= n; ++j) {
            ll p = get(j, i);
            if (p == -1) { f[0] = 1; continue; }
            f[j] = a[j][p];
        }
        if (f[0]) continue;
        for (ll j = 1; j <= n; ++j) {
            while (!q3.empty() && q3.front() < j-r+1) q3.pop_front();
            while (!q3.empty() && f[q3.back()] <= f[j]) q3.pop_back();
            q3.push_back(j);
            if (j < r) continue;
            mn = min(mn, f[q3.front()]);
        }
    }
    cout << (mn == inf ? -1 : mn);
    return 0;
}