//
// Created by Psy.C on 2026/10/22.
//
/**
node 表示一个任务：s起始准备日、d考试截止日、c所需准备天数、k已准备天数、idx原始索引。
operator< 按截止日 d 排序，用于 set 中优先取截止日最早的任务。
set s 存放"当前可开始准备、尚未完成"的任务，按截止日排序
每天 i：
若存在截止日 d == i 的任务（当天要考试）：
从 set 中移除该任务（若在）。
校验：该任务已准备天数 k 必须 == 所需 c，否则说明来不及 → 输出 -1 终止。
当天标记为考试日 a[i] = m+1，flg=true。
若有起始日 s == i 的任务，把它们加入 set（表示今天起可开始准备）。
若非考试日：从 set 中取截止日最早的任务准备一天（k+1），若仍未备够则放回 set 继续排
输出每天安排：考试日输出 m+1，准备某任务输出其 idx，空闲输出 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i, n) for (i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 128;

struct node {
    int s, d, c, k, idx;
    bool operator<(const node &o) const& {
        return d < o.d;
    }
} e[N];
set<node> s;

int n, m, a[N], i, j;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) { cin >> e[i].s >> e[i].d >> e[i].c, e[i].k = 0, e[i].idx = i; }
    rep(i,n) {
        bool flg = false;
        rep(j,m) if (e[j].d == i) {//检查第 i 天是否有考试
            if (s.contains(e[j])) s.erase(e[j]);
            if (e[j].k != e[j].c) { cout << "-1\n"; return 0; }//考试当天发现准备天数不足
            a[i] = m + 1;//第 i 天标记为考试日
            flg = true;
        }
        rep(j,m) if (e[j].s == i) s.insert(e[j]);//第 i 天可以开始准备的任务入集合
        if (flg) continue;//考试日不安排准备
        if (s.empty()) { a[i] = 0; continue; }//无任务可准备 → 输出 0
        node top = *s.begin(); s.erase(s.begin());//取截止日最早任务
        a[i] = top.idx; top.k += 1; e[top.idx].k += 1;//今天为它准备，k+1
        if (top.k != top.c) s.insert(top);//若还没准备够，放回
    }
    rep(i,n) cout << a[i] << " \n"[i==n];
    return 0;
}