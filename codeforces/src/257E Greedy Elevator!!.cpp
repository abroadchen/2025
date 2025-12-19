//
// Created by Psy.C on 2025/12/19.
//
/*
 *乘客信息结构体
 *id: 乘客ID, st: 到达楼层, ed: 离开时间, tag: 目标楼层
 *beg: 开始等待时间, kk: 原始索引
 *乘客信息结构体2（用于优先队列） 电梯内部的乘客管理
 *wd, wu;   // 等待下行/上行的乘客
 *pd, pu;  // 电梯内下行/上行的乘客
 *
*p[head-1].st 是刚刚处理过的乘客所在的楼层
p[head].st 是下一个待处理的乘客所在的楼层
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 110000
#define inf 1145141919
using namespace std;

struct node {
    int id, st, ed, tag, beg, kk;
    friend bool operator<(const node x, const node y) {
        return x.beg < y.beg;
    }
} p[N];
struct node2 {
    int id, st, ed, tag, beg, kk;
    friend bool operator<(const node2 x, const node2 y) {
        return x.tag < y.tag;
    }
};
priority_queue<node> wd, wu;
priority_queue<node2> pd, pu;

void st(const node& a, node2& b) {//复制node到node2
    b.id = a.id;
    b.st = a.st;
    b.ed = a.ed;
    b.tag = a.tag;
    b.beg = a.beg;
    b.kk = a.kk;
}

int cur = 1;//当前楼层
void pin(const node& x) {//pushin 将乘客放入电梯
    node2 t{}; st(x, t);//将node x的数据复制过去
    if (t.tag > cur) { t.tag *= -1; pu.push(t); }//上行 目标楼层取负数 放入上行乘客队列
    else pd.push(t);//下行
}

void pw(node x) {//pushwait 将乘客加入等待队列
    if (x.beg > cur) { x.beg *= -1; wu.push(x); }//上行等待 等待时间取负数 放入上行等待队列
    else { if (x.beg < cur) wd.push(x); else pin(x); }//下行等待或其他 等待时间等于当前楼层，直接放入电梯
}

int head, n;//head: 当前处理位置, n: 乘客总数
void piw() {//pushinwait 处理同一时间到达的乘客
    pw(p[head]); head++;//处理当前乘客 移动到下一个乘客
    while (p[head - 1].st == p[head].st && head <= n) {//继续处理所有在同一楼层同时到达的乘客
        pw(p[head]); head++;
    }
}

void gd(node& pl, node2& x, const int k) {//getdo 获取待处理的乘客
    if (k - 1) { if (!wd.empty()) pl = wd.top(); }//获取下行等待队列的第一个乘客
    else { if (!pd.empty()) x = pd.top(); }//获取电梯内下行乘客队列的第一个乘客
}

int getmin(const int x, const int y, const int z) {//获取三个数中的最小值
    if (x <= y && x <= z) return x;
    if (y <= x && y <= z) return y;
    if (z <= x && z <= y) return z;
    return x;//默认返回x
}

void dfs(const int x) {//pushoutwait 处理等待队列出队
    if (x == 1) {
        const node a = wd.top(); pin(a); wd.pop();//处理下行等待 获取队列顶部乘客 将其放入电梯 从等待队列中移除
        if (wd.top().beg == a.beg && !wd.empty()) dfs(1);//如果还有同样等待时间的乘客，递归处理
    } else {
        const node a = wu.top(); pin(a); wu.pop();//处理上行等待
        if (wu.top().beg == a.beg && !wu.empty()) dfs(2);
    }
}

int tim;//当前时间
void dfs2(const int x) {//pushoutin 处理电梯内乘客出电梯
    if (x == 1) {
        const node2 a = pd.top();//获取电梯内第一个下行乘客
        p[a.kk].ed = tim; pd.pop();//记录该乘客的离开时间为当前时间 从电梯内移除该乘客
        if (pd.top().tag == a.tag && !pd.empty()) dfs2(1);//如果还有同样目标楼层的乘客，递归处理
    } else {
        const node2 a = pu.top();
        p[a.kk].ed = tim; pu.pop();
        if (pu.top().tag == a.tag && !pu.empty()) dfs2(2);
    }
}

void gu(node& pl, node2& x, const int k) {//getup 获取等待队列顶部元素
    if (k - 1) { if (!wu.empty()) { pl = wu.top(); pl.beg *= -1; } }//获取上行等待队列顶部乘客 恢复原来的时间值（之前取了负数）
    else { if (!pu.empty()) { x = pu.top(); x.tag *= -1; } }//获取上行电梯内乘客 恢复原来的目标楼层值（之前取了负数）
}

void out() {
    sort(p + 1, p + n + 1, [](const node& a, const node& b) {
        return a.id < b.id;
    });
    for (int i = 1; i <= n; ++i) cout << p[i].ed << '\n';
}

signed main() {
    fast;
    int m, pudo, puup;//pudo: 下行乘客数, puup: 上行乘客数
    cin >> n >> m;
    for (int i = 1; i <= n;
        cin >> p[i].st >> p[i].beg >> p[i].tag,
        p[i].id = i, ++i) {}//读取乘客信息
    sort(p + 1, p + n + 1, [](const node& a, const node& b) {
        if (a.st == b.st) return a.beg < b.beg;
        return a.st < b.st;
    });
    for (int i = 1; i <= n; ++i) p[i].kk = i; head = cur = 1;
    while (true) {//所有乘客处理完毕且队列为空时退出
        if (head > n && pd.empty() && pu.empty() && wd.empty() && wu.empty()) break;
        //计算各方向乘客数量
        pudo = static_cast<int>(pd.size()) + static_cast<int>(wd.size()),//下行乘客总数
        puup = static_cast<int>(pu.size()) + static_cast<int>(wu.size());
        if (!pudo && !puup) { piw(); tim = p[head-1].st; }//没有乘客时处理新到达的 更新时间为最新到达乘客的时间
        else {
            if (pudo > puup) {//下行乘客较多，电梯向下运行
                node w1{}, w{}; node2 p1{};
                gd(w1, p1, 1); gd(w1, p1, 2);//获取待处理的乘客信息
                int t1, t2, t3;//计算三种操作的时间
                if (head <= n) w = p[head]; else w.st = w.beg = inf;//获取下一个待处理乘客 如果没有更多乘客，设为无穷大
                if (wd.empty()) t1 = inf; else t1 = cur - w1.beg;//计算到达下行等待乘客所在楼层所需时间
                if (pd.empty()) t2 = inf; else t2 = cur - p1.tag;//计算到达下行电梯内乘客目标楼层所需时间
                if (head > n) t3 = inf; else t3 = w.st - tim;//计算处理下一批到达乘客所需时间
                const int op = getmin(t1, t2, t3);//选择最小时间作为本次操作时间
                cur -= op, tim += op;//更新楼层和时间
                //执行相应操作
                if (t1 <= t2 && t1 <= t3) dfs(1);//处理下行等待乘客
                if (t2 <= t1 && t2 <= t3) dfs2(1);//处理下行电梯内乘客离开
                if (t3 <= t1 && t3 <= t2) piw();//处理新到达的乘客
            } else {//上行乘客较多，电梯向上运行
                node w2{}, w{}; node2 p2{};
                gu(w2, p2, 1); gu(w2, p2, 2);
                int t1, t2, t3;
                if (head <= n) w = p[head]; else w.st = w.beg = inf;
                if (wu.empty()) t1 = inf; else t1 = w2.beg - cur;
                if (pu.empty()) t2 = inf; else t2 = p2.tag - cur;
                if (head > n) t3 = inf; else t3 = w.st - tim;
                const int op = getmin(t1, t2, t3);
                cur += op, tim += op;
                if (t1 <= t2 && t1 <= t3) dfs(2);
                if (t2 <= t1 && t2 <= t3) dfs2(2);
                if (t3 <= t1 && t3 <= t2) piw();
            }
        }
    }
    out();
    return 0;
}