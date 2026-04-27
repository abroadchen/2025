//
// Created by Psy.C on 2026/4/26.
//
/**
值x和索引i
type数组标记每个元素的状态
pq结构体封装了带过滤功能的优先队列
up()方法清除队列顶部已标记的元素

选择前A个最小值加入结果，并标记其状态为1
按索引重新排序a数组
q1存储a数组值
q2存储b数组值
q3存储b[i]-a[i]差值
进行B次操作，每次选择收益最大的方案:
方案1(op=1): 直接选择b[i]，收益为b[i]
方案2(op=2): 选择b[i]并替换掉a[j]，收益为(b[i]-a[j])+a[j]=b[i]
更新相应元素的类型标记

op = -1: 操作类型标识，初始为-1表示无操作
x: 临时存储队列顶部的值
i = 0, j = 0: 存储选中的元素索引
mx = -inf: 最大收益，初始化为负无穷
方案1：直接选择b[i]
条件: q2队列非空，且队列顶部元素的值大于当前最大收益
操作:
将x赋值为q2顶部元素的值（即b[i]）
更新mx为这个值
设置op=1表示方案1
记录索引i
含义: 选择b[i]而不影响其他元素，收益为b[i]
方案2：替换操作
条件: q3和q1队列都非空，且两队列顶部元素值之和大于当前最大收益
操作:
q3.top().x 是 b[i]-a[i] 的值
q1.top().x 是 a[j] 的值
x = (b[i]-a[i]) + a[j] = b[i] + (a[j]-a[i])
实际上这里应该是 x = q3.top().x + q1.top().x = (b[i]-a[i]) + a[j]
更新mx，设置op=2，记录索引i和j
含义:
移除原来的a[i]（已经计入结果）
添加新的a[j]（收益为a[j]）
添加b[i]（收益为b[i]）
净收益变化：b[i] - a[i] + a[j]

操作1 (op == 1)
res += mx: 将最优收益加入总结果
type[i] = 2: 将元素i标记为类型2（表示选择了b[i]）
操作2 (op == 2)
res += mx: 加入组合操作的最大收益
type[i] = 2: 将i标记为类型2（选择b[i]）
type[j] = 1: 将j标记为类型1（保留或重新选择a[j]）
q3.push({b[j].x-a[j].x, j}): 将更新后的差值重新加入q3队列

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+7, inf = 0x3f3f3f3f3f3f3f3f;
struct node { int x, i; } a[N], b[N];
bool operator<(const node& x, const node& y) { return x.x > y.x; }
bool operator>(const node& x, const node& y) { return x.x < y.x; }

int type[N];
struct pq {
    int op{};
    priority_queue<node, vector<node>, greater<>> q;
    void up() { while (!q.empty() && type[q.top().i] != op) q.pop(); }
    void push(const node& x) { q.push(x); }
    node top() { up(); return q.top(); }
    bool empty() { up(); return q.empty(); }
    void clear() { op = 0; q = {}; }
} q1, q2, q3;

int n, A, B, res;
signed main() {
    fast;
    cin >> n >> A >> B; q1.op = 0, q2.op = 0, q3.op = 1;
    for (int i = 1; i <= n; ++i) cin >> a[i].x, a[i].i = i;
    for (int i = 1; i <= n; ++i) cin >> b[i].x, b[i].i = i;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= A; ++i) res += a[i].x, type[a[i].i] = 1;
    sort(a + 1, a + 1 + n, [](node x, node y) {
        return x.i < y.i;
    });
    for (int i = 1; i <= n; ++i) {
        q1.push({a[i].x, i}); q2.push({b[i].x, i});
        q3.push({b[i].x-a[i].x, i});
    }
    for (int t = 1; t <= B; ++t) {
        int op = -1, x, i = 0, j = 0, mx = -inf;
        if (!q2.empty() && (x=q2.top().x) > mx) {
            mx = x; op = 1; i = q2.top().i;
        }
        if (!q3.empty() && !q1.empty() && (x=q3.top().x+q1.top().x) > mx) {
            mx = x; op = 2; i = q3.top().i; j = q1.top().i;
        }
        res += mx;
        if (op == 1) type[i] = 2;
        else if (op == 2) {
            type[i] = 2; type[j] = 1; q3.push({b[j].x-a[j].x, j});
        }
    }
    cout << res << '\n';
    for (int i = 1; i <= n; ++i) {
        if (type[i] == 1) cout << i << ' ';
        cout << '\n';
    }
    for (int i = 1; i <= n; ++i) {
        if (type[i] == 2) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}