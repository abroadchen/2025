//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
a：原始数据元素（结构体）
.a：值（题目给的值，参与排序）
.b：原始下标
.ans：答案（最终输出给每个元素的分组/天数编号
t[]：工作数组（存放"桶"的状态）
.a：每个桶当前容纳的某个"代表值"
.b：每个桶的编号（用于回填到 ans）
n：元素个数，m：可能是某种上限（本题代码里未实际使用？见下文分析），d：关键差值参数
对第 i 个元素：读值到 a[i].a，a[i].b = i 记录下标。
t[i].a = -inf：将所有 t 桶的"代表值"初始化为无穷小。
t[1].b = 1：给第 1 个桶编号 1。
把元素按 .a（值）‍升序排序。
s、e：双指针，指向 t 中一段活跃的"桶"区间 [s, e]。
z：新桶编号计数器（从 2 开始）。
对每个已排序元素 a[i]（值从小到大）：

分支 1：a[i].a - d > t[s].a（可以复用旧桶）
条件：当前值与 t[s] 的差值严格大于 d（即 a[i].a > t[s].a + d），说明它和旧桶的代表值相距较远，可以放进同一个"已有桶"里而不违反某个间隔约束。
操作：把 t[s] 的 .a 更新为 a[i].a，同时把桶号 t[e] 复制为 t[s]（t[e] = t[s]）作为一份副本，然后 s++、e++ 各向后移一格——相当于把前一个桶滚动着继续使用，并把当前元素归到该桶号。
a[i].ans = t[e].b：该元素的答案 = 该桶的编号 b。
直观理解：这是一个"环形/复用桶"的贪心，s 指向当前可继续追加的最小桶，e 往前进；当元素能塞进 t[s]（值间隔 > d 时），就沿用它的桶号并前移。
分支 2：否则（间隔不够，需要新桶）
条件：a[i].a - d <= t[s].a，即当前值离 t[s] 太近了，不能共用旧桶，必须新开一个桶。
操作：在 t[e]（新位置）写入 a[i].a 和新的桶号 z，元素答案 = z，z++（新桶号递增）
用 cmp2（按 .b，即原始下标）把数组恢复原顺序。
输出 e-s+1：用到的桶（天数/组别）总数。
依次输出每个元素被分配到的桶号 a[i].ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5, M = 4e5+5, inf = 2e9+9;

struct node { int a, b, ans; } a[N];
bool cmp(node l, node r) { return l.a < r.a; }
bool cmp2(node l, node r) { return l.b < r.b; }

struct node2 { int a, b; } t[M];

int n, m, d;
int main() {
    fast;
    cin >> n >> m >> d;
    rep(i,n) {
        cin >> a[i].a; a[i].b = i;
        t[i].a = -inf;
    }
    t[1].b = 1;
    sort(a+1, a+n+1, cmp);
    int s = 1, e = 1, z = 2;
    rep(i,n) {
        if (a[i].a - d > t[s].a) {
            t[s].a = a[i].a; e++;
            t[e] = t[s]; s++;
            a[i].ans = t[e].b;
        } else {
            e++; t[e].a = a[i].a; t[e].b = z;
            a[i].ans = z; z++;
        }
    }
    sort(a+1, a+n+1, cmp2);
    cout << e-s+1 << '\n';
    rep(i,n) cout << a[i].ans << ' ';
    return 0;
}