//
// Created by Psy.C on 2026/10/18.
//
/***
block：莫队的分块大小。这里用 pow(n, 2.0/3.0)（n^(2/3)），这是带修莫队的经典块大小（使总复杂度约为 O(n^(5/3))）。
struct qu：一次查询需要四个信息：
l, r：查询的区间左右端点
t：查询时已应用了几次修改（时间戳），即"这个询问要基于第几次修改之后的状态"
id：原始输出顺序（因为排完序后顺序乱了，需要靠它按原序输出）
operator<：排序规则（莫队排序）：
先按左端点所在块 a.l/block 排；
若左块相同，再按右端点所在块排；
若右块也相同，再按时间 t 排。
用三元运算符嵌套写等价于：
if (a.l/block != b.l/block) return a.l < b.l;
if (a.r/block != b.r/block) return a.r < b.r;
return a.t < b.t;
一条修改记录：pos（把 a[pos] 修改成的新值的坐标位置）+ val（修改成的新值）。
注意：c[i].val 在交换时会记录"被换掉的旧值"，用来回退（下面会看到 swap 技巧
这里用到了双层计数来快速算 mex：
cnt[pos]：当前区间内，值 pos 出现的次数（注意 pos 这里指"元素的值"作为下标，下标范围是离散化后 0-V）。
num[k]：当前出现次数恰好为 k 的不同值有多少个。
add(pos)：把一个元素（值为 pos）‍加入当前区间——
它原来出现 cnt[pos] 次，先让 num[cnt[pos]] 减一（该出现次数档位少了一个值）；
再把 cnt[pos] 加一（值为 pos 的出现次数 +1），让 num[新增档位] 加一。
del(pos)：把元素移出区间，逻辑完全相反（出现次数 -1，转移计数档位）。
通过 num[cnt] 只要维护"出现次数为某档位的值的个数"，就能在 O(1) 内"加点/删点"，并在最后求 mex。

输入：n（数组长度）、m（总操作数）。
block = n^(2/3) 为带修莫队块大小。
读入初始数组 a[1..n]，把值全部 push_back 进 v（v 用来做离散化）
依次读 m 个操作：
op 为奇数（op&1==1）⇒ 查询操作：读 l, r，记入查询 q[++cq]。
查询结构体的 t 被设为 cc，即"记录下当前已经进行了多少次修改"——这是带修莫队的关键：每个询问被打上它发生时的时间戳。
id = cq：当前查询的原始编号。
op 为偶数 ⇒ 修改操作：读 pos, val，记入修改 c[++cc]。
修改记录的 pos 是数组下标，val 是要改成的值。
同时把 val 也 push_back 进 v（因为修改后出现的新值也要参与离散化
先对查询 q 排序（莫队排序），确定处理顺序。
对 v 排序、去重（ranges::sort 和 ranges::unique 是 C++20 的写法）。
把所有数组初始值 a[i] 和所有修改之新值 c[i].val 替换成各自在 v 中的离散化下标（lower_bound(...) - v.begin()），把值域压缩到 0-V，这样 cnt[] 才能按"值"当下标用。
之所以要把初始值和所有修改值一起离散化，是因为 cnt 数组要能覆盖所有出现过（可能被改成）的值
三指针初始：区间左右 l=1, r=0（空区间），时间 t=0（未应用任何修改）。
逐个处理排好序的查询 q[i]，把当前目标区间记为 [L, R]、目标时间为 q[i].t
通过 add/del 把当前区间 [l,r] 逐步移动到目标 [L,R]：
左端点右移 → 左边的元素离开区间 → del
左端点左移 → 新元素进入区间左边 → add
右端点右移 → 新元素进入区间右边 → add
右端点左移 → 右边的元素离开区间 → del
结束后 [l,r] == [L,R]
应用修改（t 前进）‍：
t++ 进入第 t 次修改；
若该修改的坐标 c[t].pos 在当前查询区间 [L,R] 内，则它会影响区间内的数值 → 先把旧值 a[pos] 从计数中删掉，再把新值 c[t].val 加进来（del + add）；
swap(a[c[t].pos], c[t].val)：交换数组实际值和修改记录的 val。
应用后：a[pos] 变成新值 ✓，同时 c[t].val 里存下旧值（这样未来回退时才拿得到）。
回退修改（t 后退）‍：逻辑完全对称。
先把（当前已应用在区间内的该 pos 的值）a[pos] 删掉、把 c[t].val（即旧值）加进来；
再一次 swap，把 a[pos] 换回旧值，c[t].val 换回新值，然后 t--。
这个 swap 小技巧是带修莫队的经典写法：单条代码里同时完成"应用"和"记录旧值"，因此前进和回退可以共用几乎一样的代码
从 1 开始，往上看 num[ans]：num[k] 表示"当前区间内出现次数恰好为 k 的不同值个数"。
只要 num[ans] 非零，说明存在出现次数恰好为 ans 的值——也就是 0、1、2、…、ans−1 这些数都在区间里出现过（各自至少出现一次，其"出现次数为 k"的档位里这些值存在），所以 mex 至少是 ans+1，于是 ans++ 继续找。
循环到第一个 num[ans]==0（即没有值刚好出现 ans 次）时停下。实际上这保证 1..ans−1 都在区间中出现过，而 ans 这个值没出现过（那么它出现次数为 0，故 num[ans]==0），所以 ans 就是 mex。
结果存入 ans[q[i].id] —— 用原查询编号存，保证按输入顺序输出。
按查询输入顺序（1..cq）输出每个区间的 mex
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+5;

int block;
struct qu {
    int l, r, t, id;
    friend bool operator<(const qu& a, const qu& b) {
        return a.l/block^b.l/block ? a.l < b.l : a.r/block^b.r/block ? a.r < b.r : a.t < b.t;
    }
} q[N];
struct node { int pos, val; } c[N];

int num[N], cnt[N];
void add(int pos) { --num[cnt[pos]]; num[++cnt[pos]]++; }
void del(int pos) { --num[cnt[pos]]; num[--cnt[pos]]++; }


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], cq, cc, ans[N];
vector<int> v;
int main() {
    int n = rd(), m = rd(); block = pow(n, 2.0/3.0);
    for (int i = 1; i <= n; i++) {
        a[i] = rd(); v.push_back(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int op = rd();
        if (op&1) {
            q[++cq].l = rd(); q[cq].r = rd();
            q[cq].t = cc; q[cq].id = cq;
        } else {
            c[++cc].pos = rd(); c[cc].val = rd();
            v.push_back(c[cc].val);
        }
    }
    sort(q+1, q+cq+1); ranges::sort(v);
    v.erase(ranges::unique(v).begin(), v.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    for (int i = 1; i <= cc; i++)
        c[i].val = lower_bound(v.begin(), v.end(), c[i].val) - v.begin();
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= cq; i++) {
        int L = q[i].l, R = q[i].r;
        while (l < L) del(a[l++]);
        while (l > L) add(a[--l]);
        while (r < R) add(a[++r]);
        while (r > R) del(a[r--]);
        while (t < q[i].t) {
            t++;
            if (L <= c[t].pos && R >= c[t].pos) { del(a[c[t].pos]); add(c[t].val); }
            swap(a[c[t].pos], c[t].val);
        }
        while (t > q[i].t) {
            if (L <= c[t].pos && R >= c[t].pos) { del(a[c[t].pos]); add(c[t].val); }
            swap(a[c[t].pos], c[t].val);
            t--;
        }
        for (ans[q[i].id] = 1; num[ans[q[i].id]]; ans[q[i].id]++) {}
    }
    for (int i = 1; i <= cq; i++) printf("%d\n", ans[i]);
    return 0;
}