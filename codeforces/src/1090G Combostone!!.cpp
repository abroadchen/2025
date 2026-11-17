//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
N 数组容量：2e5+5e4+5，比上一版多开了 5e4（大概是给 op4 复制新增的对象预留空间）。
M = 5e4：剪枝用的魔法阈值
a=攻击力, h=阈值/血量 out=出局回合(-1存活), tim=已执行回合计数
f 全局计数：统计 op4(复制) 的次数
k = 对方攻击力 y.a − 己方累计回合 x.tim
剪枝：只有当 f（复制次数）超过 5 万、且 k 明显小于阈值 h-20 时才提前返回。你的小样例里 f 很小，这个分支永远不触发，不影响本次结果，但本身是个不严格的近似
先把 st 里匹配 k 的所有节点删光，然后 insert(k) 插回一个 k，所以 st 最终仍是单元素 {k}
把 k 插回集合，然后取集合最大值赋给 k。
若最大值 ≥ 阈值 h，判定该对象在 round 回合出局，并清空集合释放内存。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e5+5e4+5, M = 5e4;

struct node {
    set<int> st;//单对象维护的"当前攻击值集合"
    int a, h, out, tim;
} c[N];

int f;
void attack(node &x, node &y, int round) {
    int k = y.a - x.tim;
    if (f > M && k < x.h - 20) return;
    for (auto it = x.st.find(k); it != x.st.end() && *it == k; ++k)
        it = x.st.erase(it);
    x.st.insert(k); k = *x.st.rbegin();
    if (k >= x.h) {
        x.out = round;
        set<int>().swap(x.st);
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int op[N], u[N], v[N];
int main() {
    fast;
    int n = rd(), x = 0, k = 0, i, r, j;
    rep(i,n) {
        op[i] = rd();
        switch (op[i]) {
            case 1: ++x; break;//统计新建个数
            case 2:
            case 3: u[i] = rd(); break;//op2/3 只读一个参数
            case 4: u[i] = rd(); ++f; break;// op4 读参数并累加 f
            default: u[i] = rd(); v[i] = rd();//op5 读两个参数
        }
    }
    rep(r,n) {
        x = op[r];//把读取的 op 值赋给 x，覆盖了第一遍的计数
        if (x == 1) { c[++k].out = -1; c[k].a = c[k].h = 1; }//新建对象：存活(-1)，a=h=1
        else {
            i = u[r];
            switch (x) {
                case 2: if (c[i].out < 0) ++c[i].a; break;//未出局才 a+1
                case 3: if (c[i].out < 0) ++c[i].tim; break;//未出局才 tim+1
                case 4: if (c[i].out > 0) c[++k].out = r;//源已出局 → 新对象也在 r 出局
                        else c[++k] = c[i];//否则整体复制状态
                        break;
                default: j = v[r];
                         if (c[i].out > 0 || c[j].out > 0) break;//任一出局则不发生对战
                         attack(c[i], c[j], r);
                         attack(c[j], c[i], r);
            }
        }
    }
    cout << k << '\n';//输出对象总数 k，以及每个对象的出局回合（out）
    rep(i,k-1) cout << c[i].out << ' ';
    if (k) cout << c[k].out << '\n';
    return 0;
}