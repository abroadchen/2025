//
// Created by Psy.C on 2026/10/7.
//
/**
car：一辆车，属性 p（当前停靠位置）、t（空闲时间/上次结束时间）、id（编号）。自定义 <：按 p、t、id 字典序。
s1：multiset<car>，空闲可用车辆集合。
qrq[]：m 个订单，t（下单时间）、a（起点）、b（终点），按 t 排序。
run：一个"途中/预约"运行，t（车辆到达起点的时间）、p（载客起点位置）、id。按 t 排序。
s2：multiset<run>，已预约但还没出发的运行任务。
s：multiset<int>，所有需要处理的时间点（事件队列）
（题面通常 n=m，且每辆刚完成的车会重新触发时间事件，这里把订单时间与运行完成时间都塞进事件队列 s。
事件循环按时间从小到大推进。
时刻 t：先把到点空闲的预约车放回空闲池 s1，再为这段时间内到达的订单派车。
派车策略：从 s1 中找距离订单起点 a 最近的空闲车（lower_bound 找不小于 a 的，再和它前一辆比较远近；距离相等时优先 t 更小、再 id 更小者——即选"更早空闲 / 编号小"的车）。
派出后计算完成时刻 t1 = 现在时刻 + 空车跑向起点 + 载客送到终点，输出车辆 id 和乘客等待时间 t + |p-a| - q[x].t（乘客下单到车到达起点的时间差）。
车辆进入"预约"状态 s2，并在 t1 时刻触发事件继续
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define sz(a) ((int)(a).size())
using namespace std;

struct car {
    int p, t, id;
    friend bool operator<(const car& a, const car& b) {
        if (a.p == b.p) {
            if (a.t == b.t) return a.id < b.id;
            return a.t < b.t;
        }
        return a.p < b.p;
    }
};
multiset<car> s1;

constexpr int N = 2e5+5;
struct qry {
    int t, a, b;
    friend bool operator<(const qry& x, const qry& y) {
        return x.t < y.t;
    }
} q[N];
struct run {
    int t, p, id;
    friend bool operator<(const run& a, const run& b) {
        return a.t < b.t;
    }
};
multiset<run> s2;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

multiset<int> s;
void solve() {
    int n = rd(), k = rd(), m = rd();//n个位置, k辆车, m个订单
    for (int i = 1; i <= k; ++i) {
        int x = rd();
        s1.insert({.p = x, .t = 0, .id = i});//初始时所有车在位置x、时间0
    }
    for (int i = 1; i <= m; ++i) {
        int t = rd(), a = rd(), b = rd();
        q[i] = {.t = t, .a = a, .b = b}; s.insert(t);//记录新订单时间
    }
    int x = 0;
    while (!s.empty()) {
        int t = *s.begin(); s.erase(s.begin());//取最早事件时间
        //① 把所有此时刻"到达起点"的预约车放入空闲池
        while (sz(s2) && s2.begin()->t == t) {
            run i = *s2.begin();
            int p = i.p, id = i.id;
            s1.insert({.p = p, .t = t, .id = id});//车到起点，车停在 p、空闲时间为 t
            s2.erase(s2.begin());
        }
        //② 处理所有在 t 时刻(及之前)到达且有空闲车的订单
        while (x+1 <= m && q[x+1].t <= t && sz(s1)) {
            ++x;
            int p = q[x].a;
            //找到离起点 p 最近的空闲车（邻居查找）
            auto it = s1.lower_bound({.p = p, .t = 0, .id = 0});
            if (it == s1.end()) {//p 比所有车都大
                --it; p = it->p;
                it = s1.lower_bound({.p = p, .t = 0, .id = 0});
            }
            else if (it == s1.begin()) {}
            else {//比较前后两辆，选更近的；距离相同再比 t、id
                auto it1 = prev(it);
                int o = it1->p;
                it1 = s1.lower_bound({.p = o, .t = 0, .id = 0});
                if (p-it1->p > it->p-p) {}
                else if (p-it1->p < it->p-p) it = it1;
                else {
                    if (it1->t > it->t) {}
                    else if (it1->t < it->t) it = it1;
                    else {
                        if (it1->id < it->id) it = it1;
                    }
                }
            }
            p = it->p;// 派出这辆车接单
            int id = it->id;
            int t1 = t + abs(p-q[x].a) + abs(q[x].a-q[x].b);//到达+接客+送客总耗时
            cout << id << ' ' << t+abs(p-q[x].a)-q[x].t << '\n';//派哪辆车 + 等待时间
            s.insert(t1);//该车 t1 时刻完成，加入事件
            s2.insert({.t = t1, .p = q[x].b, .id = id});//预约: t1 时到达 q[x].b
            s1.erase(it);//车不再空闲
        }
    }
}

signed main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}