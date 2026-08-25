//
// Created by Psy.C on 2026/8/25.
//
/**
- ios_base::sync_with_stdio(0) ：关闭C++流与C标准流（ scanf/printf ）的同步，减少跨语言流的额外开销。
- cin.tie(0) ：解除 cin 与 cout 的默认绑定（默认 cin 读取前会强制刷新 cout ），避免不必要的刷新。
- cout.tie(0) ：同理解除 cout 与 cin 的绑定。
主函数中调用 fast 即可全局启用加速

- n ：节点编号（唯一标识节点，从1开始）。
- t ：节点的 冷却时间戳 （表示节点何时能再次被使用，初始为0即可用）。
- bool operator<(const node &o) const ：重载 < 运算符，用于 优先队列的排序规则 （C++的 priority_queue 默认是 最大堆 ，堆顶优先级最高的元素）：
- 当 t 不同时： t 越大的节点优先级越高（堆顶优先），这样可以优先取出 冷却时间最晚的节点 （即 t 最大的节点，因为堆是最大堆，堆顶是 t 最大的，方便批量取出 t ≤当前时间的所有可用节点）。
- 当 t 相同时： n 越大的节点优先级越高

- n ：节点总数（需要调度的资源节点数量）。
- m ：操作次数（需要处理的资源申请次数）

循环初始化 [ o bj ec tO bj ec t ] n 个节点并加入优先队列：
- int i = 1; i <= n; ++i ：遍历从1到 [ o bj ec tO bj ec t ] n 的节点编号。
- node x{} ：C++ 聚合初始化 ，将 x 的成员 n 和 t 初始化为0。
- x.n = i; x.t = 0 ：赋值节点编号为 i ，冷却时间戳 t=0 （表示初始状态下所有节点均可用）。
- q.push(x) ：将节点加入优先队列，队列会自动按重载的 < 规则排序（按 t 降序， t 越大的在堆顶）。

循环处理 [ o bj ec tO bj ec t ] m 次操作，每次操作的输入格式为三个整数：
- a[0] ： 当前时间戳 （只有 t ≤ a[0] 的节点才可用，即冷却完成的节点）。
- a[1] ： 需要的节点数量 （本次申请需要取出的节点数）。
- a[2] ： 操作后的冷却时间增量 （节点被使用后，冷却时间戳更新为 a[0] + a[2] ，表示需要等待 a[2] 的时间才能再次可用）。
- vector<node> v ：定义可用节点列表，存储从队列中取出的所有冷却完成的节点。

从优先队列中批量提取 所有冷却完成的节点 （ t ≤ 当前时间戳a[0] ）：
- !q.empty() ：循环条件，队列非空时继续提取。
- q.top().t <= a[0] ：判断堆顶节点的冷却时间戳是否≤当前时间（即是否可用）。
- v.push_back(q.top()) ：将可用节点加入可用列表 v 。
- q.pop() ：将已提取的节点从队列中移除。
- else break ：若堆顶节点的 t > a[0] ，说明堆中所有节点的 t 均大于 a[0] （因为堆是最大堆，堆顶是 t 最大的节点），无更多可用节点，停止提取

判断可用节点数量是否满足申请要求：
- v.size() >= a[1] ：可用节点数≥需要的数量，满足要求。
- int sum = 0 ：定义 sum 存储 选中节点的编号之和 （题目要求的输出结果）。
- ranges::sort(v, cmp) ：使用**C++20的 ranges::sort **对可用列表 v 按 cmp 排序（即按节点编号 n 升序排序， n 小的排前面），方便后续选编号最小的 [ o bj ec tO bj ec t ] a [ 1 ] 个节点

选中前 [ o bj ec tO bj ec t ] a [ 1 ] 个编号最小的节点，更新其冷却状态并输出结果：
- for (int j = 0; j < a[1]; ++j) ：遍历排序后的前 [ o bj ec tO bj ec t ] a [ 1 ] 个节点（编号最小的）。
- sum += v[j].n ：累加选中节点的编号到 sum 。
- v[j].t = a[0] + a[2] ：将选中节点的冷却时间戳更新为 当前时间 + 冷却增量 ，表示这些节点需要等待 a[2] 的时间才能再次可用。
- for (auto j : v) q.push(j) ： 将所有可用节点（包括选中的和未选中的）重新放回优先队列 ：
  - 未选中的节点： t 未修改，会回到队列原有位置。
  - 选中的节点： t 已更新，会根据新的 t 重新排序。
- cout << sum << '\n' ：输出选中节点的编号之和

若可用节点数量不足（ v.size() < a[1] ），执行以下操作：
- cout << "-1" << '\n' ：输出 -1 表示本次申请失败。
- for (auto j : v) q.push(j) ： 将所有已提取的可用节点重新放回优先队列 （因为这些节点未被使用，保持原状态）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node {
    int n, t;
    bool operator<(const node &o) const {
        if (t == o.t) return n > o.n;
        return t > o.t;
    }
};
priority_queue<node> q;
//对可用节点列表按 节点编号 n 升序排序
int cmp(node a, node b) { return a.n < b.n; }

int main() {
    fast;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        node x{}; x.n = i; x.t = 0;
        q.push(x);
    }
    for (int i = 0; i < m; ++i) {
        int a[3];
        cin >> a[0] >> a[1] >> a[2];
        vector<node> v;
        while (!q.empty()) {
            if (q.top().t <= a[0]) {
                v.push_back(q.top());
                q.pop();
            } else break;
        }
        if (v.size() >= a[1]) {
            int sum = 0;
            ranges::sort(v, cmp);
            for (int j = 0; j < a[1]; ++j) {
                sum += v[j].n;
                v[j].t = a[0] + a[2];
            }
            for (auto j : v) q.push(j);
            cout << sum << '\n';
        } else {
            cout << "-1" << '\n';
            for (auto j : v) q.push(j);
        }
    }
    return 0;
}